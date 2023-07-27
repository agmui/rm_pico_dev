//code from taproot

#ifndef  PICO_REFSERIAL_H_
#define  PICO_REFSERIAL_H_

#include <cstdint>
#include <unordered_map>

#include "../src/communications/RefSerialData.h"
#include "../src/communications/DJISerial.h"


namespace pico
{
    class Drivers;
}


namespace pico::communication::serial
{
/**
 * A class designed to communicate with the 2021 version of the RoboMaster
 * referee system. Supports decoding various referee serial message types. Also supports sending
 * custom UI messages to the referee serial and sending custom robot to robot communication.
 *
 * For information about the protocol that this serial parser/decoder uses,
 * view RoboMaster's ref serial website:
 * https://www.robomaster.com/en-US/products/components/referee (in the Document Download tab).
 *
 * @note use the instance stored in the `Drivers` to interact with this class
 *      (you shouldn't be declaring your own `RefSerial` object).
 *
 * Receive information from the referee serial by continuously calling `messageReceiveCallback`.
 * Access data sent by the referee serial by calling `getRobotData` or `getGameData`.
 */
class RefSerial : public DJISerial, public RefSerialData
{
private:
    /**
     * Time since last message is received before we deem the referee serial port offline
     */
    static constexpr uint32_t TIME_OFFLINE_REF_DATA_MS = 1000;

    // RX message constants
    /**
     * Size of the deque used to determine the current DPS taken by the robot as reported
     * by the referee system.
     */
    static constexpr uint16_t DPS_TRACKER_DEQUE_SIZE = 20;

public:
    /**
     * RX message type defines, referred to as "Command ID"s in the RoboMaster Ref System
     * Protocol Appendix. Ignored message types commented out because they are not handled by this
     * parser yet. They are values that are used in message headers to indicate the type of message
     * we have received.
     */
    enum MessageType
    {
        REF_MESSAGE_TYPE_GAME_STATUS = 0x1,
        REF_MESSAGE_TYPE_GAME_RESULT = 0x2,
        REF_MESSAGE_TYPE_ALL_ROBOT_HP = 0x3,
        // REF_MESSAGE_TYPE_DART_LAUNCHING_STATUS = 0x4,
        REF_MESSAGE_TYPE_SITE_EVENT_DATA = 0X101,
        // REF_MESSAGE_TYPE_PROJECTILE_SUPPPLIER_SITE_ACTION = 0x102,
        // REF_MESSAGE_TYPE_PROJECTILE_SUPPLY_REQUESTED = 0x103,
        REF_MESSAGE_TYPE_WARNING_DATA = 0x104,
        // REF_MESSAGE_TYPE_DART_LAUNCH_OPENING_COUNT = 0x105,
        REF_MESSAGE_TYPE_ROBOT_STATUS = 0x201,
        REF_MESSAGE_TYPE_POWER_AND_HEAT = 0x202,
        REF_MESSAGE_TYPE_ROBOT_POSITION = 0x203,
        REF_MESSAGE_TYPE_ROBOT_BUFF_STATUS = 0x204,
        REF_MESSAGE_TYPE_AERIAL_ENERGY_STATUS = 0x205,
        REF_MESSAGE_TYPE_RECEIVE_DAMAGE = 0x206,
        REF_MESSAGE_TYPE_PROJECTILE_LAUNCH = 0x207,
        REF_MESSAGE_TYPE_BULLETS_REMAIN = 0x208,
        REF_MESSAGE_TYPE_RFID_STATUS = 0x209,
        // REF_MESSAGE_TYPE_DART_INSTRUCTIONS = 0x20A,
        REF_MESSAGE_TYPE_CUSTOM_DATA = 0x301,
        // REF_MESSAGE_TYPE_CUSTOM_CONTROLLER = 0x302,
        // REF_MESSAGE_TYPE_SMALL_MAP = 0x303;
    };

    /**
     * Constructs a RefSerial class connected to `bound_ports::REF_SERIAL_UART_PORT` with
     * CRC enforcement enabled.
     *
     * @see `DjiSerial`
     */
    RefSerial(Drivers* drivers);
    ~RefSerial() = default;

    /**
     * Handles the types of messages defined above in the RX message handlers section.
     */
    void messageReceiveCallback(const ReceivedSerialMessage& completeMessage) override;

    bool getRefSerialReceivingData() const;

    /**
     * Returns a reference to the most up to date robot data struct.
     */
    const Rx::RobotData& getRobotData() const;

    /**
     * Returns a reference to the most up to date game data struct.
     */
    const Rx::GameData& getGameData() const;

    /**
     * Returns a robot id that is of the same color of this robot's
     * ID. This allows you to specify you want to send to one robot
     * and then based on your team it will be sent to the correct robot
     * (your team not the enemy team's robot).
     */
    RobotId getRobotIdBasedOnCurrentRobotTeam(RobotId id);

    void attachRobotToRobotMessageHandler(
        uint16_t msgId,
        RobotToRobotMessageHandler* handler);

    /**
     * Used by `RefSerialTransmitter`. It is necessary to acquire this lock to coordinate sending
     * ref serial data from different protothreads.
     */
    // void acquireTransmissionSemaphore() { transmissionSemaphore.acquire(); }

    // void releaseTransmissionSemaphore() { transmissionSemaphore.release(); }

    /**
     * @return True if the robot operator is blinded, false otherwise. Also return false if the
     * referee system is offline.
     */
    bool operatorBlinded() const;

private:
    Rx::RobotData robotData;
    Rx::GameData gameData;
    // modm::BoundedDeque<Rx::DamageEvent, DPS_TRACKER_DEQUE_SIZE> receivedDpsTracker; //TODO: find out if this is needed
    // arch::MilliTimeout refSerialOfflineTimeout; //TODO: find out if this is needed
    std::unordered_map<uint16_t, RobotToRobotMessageHandler*> msgIdToRobotToRobotHandlerMap;
    DJISerial *djiSerial;

    /**
     * Decodes ref serial message containing the game stage and time remaining
     * in the game.
     */
    bool decodeToGameStatus(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the postmatch result of a game.
     */
    bool decodeToGameResult(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the robot HP of all robots in the match.
     */
    bool decodeToAllRobotHP(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing occupation status of various field zones.
     */
    bool decodeToSiteEventData(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing warning information (if a robot on your team received a
     * yellow or red card).
     */
    bool decodeToWarningData(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the firing/driving heat limits and cooling
     * rates for the robot.
     */
    bool decodeToRobotStatus(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the actual power and heat data for the turret
     * and chassis.
     */
    bool decodeToPowerAndHeat(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the position of the robot on the field and
     * the robot heading.
     */
    bool decodeToRobotPosition(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the robot buff status of the robot.
     */
    bool decodeToRobotBuffs(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the energy status, a countdown timer from 30 seconds to
     * 0 seconds.
     */
    bool decodeToAerialEnergyStatus(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing containing the damaged armor and damage type
     * last taken by the robot.
     */
    bool decodeToDamageStatus(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the previously fired bullet type and firing
     * frequency.
     */
    bool decodeToProjectileLaunch(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing the number of bullets remaining in the robot
     * (only certain match types will send this information).
     */
    bool decodeToBulletsRemain(const ReceivedSerialMessage& message);
    /**
     * Decodes ref serial message containing which RFID buff zones are currently activated.
     */
    bool decodeToRFIDStatus(const ReceivedSerialMessage& message);
    bool handleRobotToRobotCommunication(const ReceivedSerialMessage& message);

    void updateReceivedDamage();
    void processReceivedDamage(uint32_t timestamp, int32_t damageTaken);
};

} // namespace pico::communication::serial


#endif //  PICO_REFSERIAL_H_