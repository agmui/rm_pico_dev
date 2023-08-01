#ifndef PICO_MOTORHANDLER_H_
#define PICO_MOTORHANDLER_H_

#include "DjiMotor.h"
#include "../lib/can2040/src/can2040.h"
namespace pico
{
    class Drivers;
}

namespace pico::motor
{

/**
 * Converts the dji MotorId to a uint32_t.
 * @param[in] id Some CAN MotorId
 * @return id normalized to be around [0, DJI_MOTORS_PER_CAN), or some value >= DJI_MOTORS_PER_CAN
 * if the id is out of bounds
 */
#define DJI_MOTOR_TO_NORMALIZED_ID(id)                                               \
    static_cast<uint32_t>(                                                           \
        (id < pico::motor::MOTOR1) ? (pico::motor::MotorHandler::DJI_MOTORS_PER_CAN) \
                                   : (id - pico::motor::MOTOR1))

    class MotorHandler
    {
    public:
        /** Number of motors on each CAN bus. */
        static constexpr int DJI_MOTORS_PER_CAN = 8;
        /** CAN message length of each motor control message. */
        static constexpr int CAN_DJI_MESSAGE_SEND_LENGTH = 8;
        /** CAN message identifier for "low" segment (low 4 CAN motor IDs) of control message. */
        static constexpr uint32_t CAN_DJI_LOW_IDENTIFIER = 0X200;
        /** CAN message identifier for "high" segment (high 4 CAN motor IDs) of control message. */
        static constexpr uint32_t CAN_DJI_HIGH_IDENTIFIER = 0X1FF;

        static constexpr uint16_t MIN_CAN_ID = 0x1E4;
        static constexpr uint16_t NUM_CAN_IDS = 64;
        static constexpr uint16_t MAX_CAN_ID = MIN_CAN_ID + NUM_CAN_IDS;

        MotorHandler(Drivers *drivers) : drivers(drivers) {}
        ~MotorHandler() = default;

        /**
         * Given a CAN identifier, returns the "normalized" id between [0, NUM_CAN_IDS), or a
         * value >= NUM_CAN_IDS if the canId is outside the range specified.
         */
        static inline uint16_t lookupTableIndexForCanId(uint16_t canId)
        {
            if (canId < MIN_CAN_ID)
            {
                return NUM_CAN_IDS;
            }

            return canId - MIN_CAN_ID;
        }

        /**
         * Adds the motor to the manager so that it can receive motor messages from the CAN bus. If
         * there is already a motor with the same ID in the manager, the program will abort
         */
        void addMotorToManager(DjiMotor *motor);

        /**
         * Function handles receiving messages and calling the appropriate
         * processMessage function given the CAN bus and can identifier.
         *
         * @attention you should call this function as frequently as you receive
         *      messages if you want to receive the most up to date messages.
         *      modm's IQR puts CAN messages in a queue, and this function
         *      clears out the queue once it is called.
         */
        void pollCanData();

        /**
         * Sends motor commands across the CAN bus. Sends up to 4 messages (2 per CAN bus), though it
         * may send less depending on which motors have been registered with the motor manager. Each
         * messages encodes motor controller command information for up to 4 motors.
         */
        void encodeAndSendCanData();

        /**
         * Removes the motor from the motor manager.
         */
        void removeFromMotorManager(const DjiMotor &motor);

        DjiMotor const *getCan1Motor(MotorId motorId);

        DjiMotor const *getCan2Motor(MotorId motorId);

    private:
        Drivers *drivers;
        DjiMotor *DjiMotors[8] = {0};

        DjiMotor *can1MotorStore[DJI_MOTORS_PER_CAN] = {0};
        DjiMotor *can2MotorStore[DJI_MOTORS_PER_CAN] = {0};

        void addMotorToManager(DjiMotor **canMotorStore, DjiMotor *const motor);

        void serializeMotorStoreSendData(
            DjiMotor **canMotorStore,
            can2040_msg *messageLow,
            can2040_msg *messageHigh,
            bool *validMotorMessageLow,
            bool *validMotorMessageHigh);

        void processReceivedCanData(const can2040_msg &rxMessage, DjiMotor **canMotorStore);

        void removeFromMotorManager(const DjiMotor &motor, DjiMotor **motorStore);
    };
}

#endif //  PICO_MOTORHANDLER_H_