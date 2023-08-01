#include "MotorHandler.h"
#include "drivers.h"
#include "communications/can/CanBus.h"

namespace pico::motor
{
    void MotorHandler::addMotorToManager(DjiMotor **canMotorStore, DjiMotor *const motor)
    {
        assert(motor != nullptr);
        uint32_t idIndex = DJI_MOTOR_TO_NORMALIZED_ID(motor->getMotorIdentifier());
        bool motorOverloaded = canMotorStore[idIndex] != nullptr;
        bool motorOutOfBounds = idIndex >= DJI_MOTORS_PER_CAN;
        // TODO
        //  modm_assert(!motorOverloaded && !motorOutOfBounds, "DjiMotorTxHandler", "overloading");
        canMotorStore[idIndex] = motor;
    }

    void MotorHandler::addMotorToManager(DjiMotor *motor)
    {
        // add new motor to either the can1 or can2 motor store
        // because we checked to see if the motor is overloaded, we will
        // never have to worry about overfilling the CanxMotorStore array
        if (motor->getCanBus() == pico::can::PioNum::CAN_BUS0)
        {
            addMotorToManager(can1MotorStore, motor);
        }
        else
        {
            addMotorToManager(can2MotorStore, motor);
        }
    }

    void MotorHandler::pollCanData()
    {
        can2040_msg rxMessage;

        // handle incoming CAN 1 messages
        if (drivers->can.getMessage(PioNum::CAN_BUS0, &rxMessage))
        {
            processReceivedCanData(rxMessage, messageHandlerStoreCan1);
        }

        // handle incoming CAN 2 messages
        if (drivers->can.getMessage(PioNum::CAN_BUS1, &rxMessage))
        {
            processReceivedCanData(rxMessage, messageHandlerStoreCan2);
        }
    }

    void MotorHandler::processReceivedCanData(
        const can2040_msg &rxMessage,
        CanRxListener *const *messageHandlerStore)
    {
        uint16_t id = lookupTableIndexForCanId(rxMessage.id);

        if (id >= NUM_CAN_IDS)
        {
            // RAISE_ERROR(drivers, "Invalid can id received");
            printf("Invalid can id received");
            return;
        }

        if (messageHandlerStore[id] != nullptr)
        {
            messageHandlerStore[id]->processMessage(rxMessage);
        }
    }

    void MotorHandler::encodeAndSendCanData()
    {
        // set up new can messages to be sent via CAN bus 1 and 2
        // TODO:
        can2040_msg can1MessageLow(
            CAN_DJI_LOW_IDENTIFIER,
            CAN_DJI_MESSAGE_SEND_LENGTH,
            0);
        can2040_msg can1MessageHigh(
            CAN_DJI_HIGH_IDENTIFIER,
            CAN_DJI_MESSAGE_SEND_LENGTH,
            0);
        can2040_msg can2MessageLow(
            CAN_DJI_LOW_IDENTIFIER,
            CAN_DJI_MESSAGE_SEND_LENGTH,
            0);
        can2040_msg can2MessageHigh(
            CAN_DJI_HIGH_IDENTIFIER,
            CAN_DJI_MESSAGE_SEND_LENGTH,
            0);

        bool can1ValidMotorMessageLow = false;
        bool can1ValidMotorMessageHigh = false;
        bool can2ValidMotorMessageLow = false;
        bool can2ValidMotorMessageHigh = false;

        serializeMotorStoreSendData(
            can1MotorStore,
            &can1MessageLow,
            &can1MessageHigh,
            &can1ValidMotorMessageLow,
            &can1ValidMotorMessageHigh);

        serializeMotorStoreSendData(
            can2MotorStore,
            &can2MessageLow,
            &can2MessageHigh,
            &can2ValidMotorMessageLow,
            &can2ValidMotorMessageHigh);

        bool messageSuccess = true;

        if (drivers->can.isReadyToSend(can::PioNum::CAN_BUS0))
        {
            if (can1ValidMotorMessageLow)
            {
                messageSuccess &= drivers->can.sendMessage(can::PioNum::CAN_BUS0, can1MessageLow);
            }
            if (can1ValidMotorMessageHigh)
            {
                messageSuccess &= drivers->can.sendMessage(can::PioNum::CAN_BUS0, can1MessageHigh);
            }
        }
        if (drivers->can.isReadyToSend(can::PioNum::CAN_BUS1))
        {
            if (can2ValidMotorMessageLow)
            {
                messageSuccess &= drivers->can.sendMessage(can::PioNum::CAN_BUS1, can2MessageLow);
            }
            if (can2ValidMotorMessageHigh)
            {
                messageSuccess &= drivers->can.sendMessage(can::PioNum::CAN_BUS1, can2MessageHigh);
            }
        }

        if (!messageSuccess)
        {
            // RAISE_ERROR(drivers, "sendMessage failure");
            printf("sendMessage failure");
        }
    }

    void MotorHandler::serializeMotorStoreSendData(
        DjiMotor **canMotorStore,
        can2040_msg *messageLow,
        can2040_msg *messageHigh,
        bool *validMotorMessageLow,
        bool *validMotorMessageHigh)
    {
        for (int i = 0; i < DJI_MOTORS_PER_CAN; i++)
        {
            const DjiMotor *const motor = canMotorStore[i];
            if (motor != nullptr)
            {
                if (DJI_MOTOR_TO_NORMALIZED_ID(motor->getMotorIdentifier()) <=
                    DJI_MOTOR_TO_NORMALIZED_ID(pico::motor::MOTOR4))
                {
                    motor->serializeCanSendData(messageLow);
                    *validMotorMessageLow = true;
                }
                else
                {
                    motor->serializeCanSendData(messageHigh);
                    *validMotorMessageHigh = true;
                }
            }
        }
    }

    void MotorHandler::removeFromMotorManager(const DjiMotor &motor)
    {
        if (motor.getCanBus() == pico::can::PioNum::CAN_BUS0)
        {
            removeFromMotorManager(motor, can1MotorStore);
        }
        else
        {
            removeFromMotorManager(motor, can2MotorStore);
        }
    }

    void MotorHandler::removeFromMotorManager(const DjiMotor &motor, DjiMotor **motorStore)
    {
        uint32_t id = DJI_MOTOR_TO_NORMALIZED_ID(motor.getMotorIdentifier());
        if (id > DJI_MOTOR_TO_NORMALIZED_ID(tap::motor::MOTOR8) || motorStore[id] == nullptr)
        {
            // RAISE_ERROR(drivers, "invalid motor id");
            printf("invalid motor id");
            return;
        }
        motorStore[id] = nullptr;
    }

    DjiMotor const *MotorHandler::getCan1Motor(MotorId motorId)
    {
        uint32_t index = DJI_MOTOR_TO_NORMALIZED_ID(motorId);
        return index > DJI_MOTOR_TO_NORMALIZED_ID(tap::motor::MOTOR8) ? nullptr : can1MotorStore[index];
    }

    DjiMotor const *MotorHandler::getCan2Motor(MotorId motorId)
    {
        uint32_t index = DJI_MOTOR_TO_NORMALIZED_ID(motorId);
        return index > DJI_MOTOR_TO_NORMALIZED_ID(tap::motor::MOTOR8) ? nullptr : can2MotorStore[index];
    }
} // namespace pico::motor
