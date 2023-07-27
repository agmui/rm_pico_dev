
#ifndef PICO_DJISERIAL_H_
#define PICO_DJISERIAL_H_

#include <cstdint>
#include "Uart.h"

namespace pico
{
    class Drivers;
}

namespace pico::communication::serial
{
    /**
     * A serial handler that implements a specific protocol to be used for
     * communicating with the referee system. Also used for our personal
     * communication with the xavier.
     *
     * Extend this class and implement messageReceiveCallback if you
     * want to use this serial protocol on a serial line.
     *
     * Structure of a Serial Message:
     * \rst
     * +-----------------+------------------------------------------------------------+
     * | Byte Number     | Byte Description                                           |
     * +=================+============================================================+
     * | Frame Header                                                                 |
     * +-----------------+------------------------------------------------------------+
     * | 0               | Frame Head Byte (0xA5)                                     |
     * +-----------------+------------------------------------------------------------+
     * | 1               | Frame Data Length, LSB                                     |
     * +-----------------+------------------------------------------------------------+
     * | 2               | Frame Data Length, MSB                                     |
     * +-----------------+------------------------------------------------------------+
     * | 3               | Frame Sequence Number                                      |
     * +-----------------+------------------------------------------------------------+
     * | 4               | CRC8 of the frame, (bytes 0 - 3)                           |
     * +-----------------+------------------------------------------------------------+
     * | 5               | Message Type, LSB                                          |
     * +-----------------+------------------------------------------------------------+
     * | 6               | Message Type, MSB                                          |
     * +-----------------+------------------------------------------------------------+
     * | Body - Data Length bytes                                                     |
     * +-----------------+------------------------------------------------------------+
     * | Message CRC                                                                  |
     * +-----------------+------------------------------------------------------------+
     * | 7 + Data Length | CRC16 of header and frame, LSB (bytes 0 - 6 + Data Length) |
     * +-----------------+------------------------------------------------------------+
     * | 8 + Data Length | CRC16 of header and frame, MSB                             |
     * +-----------------+------------------------------------------------------------+
     * \endrst
     */
    class DJISerial
    {
    public:
        /**
         * The serial message's frame header.
         */
        struct FrameHeader
        {
            uint8_t headByte;
            uint16_t dataLength;
            uint8_t seq;
            uint8_t CRC8;
        } modm_packed;

        /**
         * A container for storing and sending message over serial.
         */
        template <int DATA_SIZE>
        struct SerialMessage
        {
            /**
             * Constructs a SerialMessage. In doing so this constructor configures the message header.
             *
             * @param[in] seq Message sequence number, an optional parameter.
             */
            explicit SerialMessage(uint8_t seq = 0)
            {
                header.headByte = 0xa5;
                header.dataLength = sizeof(data);
                header.seq = seq;
                header.CRC8 = 0;/*tap::algorithms::calculateCRC8(
                    reinterpret_cast<uint8_t *>(&header),
                    sizeof(header) - 1);*/  //FIXME:
            }

            /**
             * Sets the CRC16 value in the struct. This should be called after writing data to the
             * message struct.
             */
            void setCRC16()
            {
                CRC16 = 0; /*tap::algorithms::calculateCRC16(
                    reinterpret_cast<uint8_t *>(this),
                    sizeof(*this) - 2);*/ //FIXME:
            }

            FrameHeader header;
            uint16_t messageType;
            uint8_t data[DATA_SIZE];
            uint16_t CRC16;
        };

        static const uint16_t SERIAL_RX_BUFF_SIZE = 256;
        static const uint16_t SERIAL_HEAD_BYTE = 0xA5;

        using ReceivedSerialMessage = SerialMessage<SERIAL_RX_BUFF_SIZE>;

        /**
         * Construct a Serial object.
         *
         * @param[in] port serial port to work on.
         * @param[in] isRxCRCEnforcementEnabled `true` to enable Rx CRC Enforcement.
         */
        DJISerial(Drivers *drivers, Uart *port, bool isRxCRCEnforcementEnabled = true);
        // DISALLOW_COPY_AND_ASSIGN(DJISerial) //TODO:
        ~DJISerial() = default;

        /**
         * Initialize serial. In particular, initializes the hardware serial
         * specified upon construction.
         *
         * @note currently, only uart ports 1, 2, and 6 are enabled. Be sure
         *      to add a serial port to `uart.hpp` if you want to use the serial.
         *      Also, if you add a new uart port to be generated in the `project.xml`
         *      file, you should add it to both the `Uart` class and this function.
         * @see `Uart`
         */
        void initialize();

        /**
         * Receive messages. Call periodically in order to receive all
         * incoming messages.
         *
         * @note tested with a delay of 10 microseconds with referee system. The
         *      longer the timeout the more likely a message failure may occur.
         */
        void updateSerial();

        /**
         * Called when a complete message is received. A derived class must
         * implement this in order to handle incoming messages properly.
         *
         * @param[in] completeMessage a reference to the full message that has
         *      just been received by this class.
         */
        virtual void messageReceiveCallback(const ReceivedSerialMessage &completeMessage) = 0;

    private:
        enum SerialRxState
        {
            SERIAL_HEADER_SEARCH, /// A header byte has not yet been received.
            PROCESS_FRAME_HEADER, /// A header is received and the frame header is being processed.
            PROCESS_FRAME_DATA    /// The data is being processed.
        };

        /// The serial port you are connected to.
        // Uart::UartPort port;
        Uart *port;

        /// stuff for RX, buffers to store parts of the header, state machine.
        SerialRxState djiSerialRxState;

        /// Message in middle of being constructed.
        ReceivedSerialMessage newMessage;

        /// Most recent complete message.
        ReceivedSerialMessage mostRecentMessage;

        /**
         * The current zero indexed byte that is being read from the `Uart` class. An absolute index
         * into the `newMessage` object. `newMessage` reinterpreted as a uint8_t array and elements read
         * from serial are placed into the message.
         */
        uint16_t frameCurrReadByte;

        bool rxCrcEnabled;

        /**
         * Calculate CRC8 of given array and compare against expectedCRC8.
         *
         * @param[in] data array to calculate CRC8.
         * @param[in] length length of array to check.
         * @param[in] expectedCRC8 expected CRC8.
         * @return if the calculated CRC8 matches CRC8 given.
         */
        inline bool verifyCRC8(uint8_t *message, uint32_t messageLength, uint8_t expectedCRC8)
        {
            return false; //tap::algorithms::calculateCRC8(message, messageLength) == expectedCRC8; //FIXME:
        }

    protected:
        Drivers *drivers;
    };

} // namespace pico::communication::serial
#endif //  PICO_DJISERIAL_H_