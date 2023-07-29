#ifndef PICO_UART_H_
#define PICO_UART_H_

#define DATA_BITS 8
#define STOP_BITS 1

#include <cstdint>
#include <cstdlib>

#include "hardware/uart.h"

namespace pico::communication::serial
{

    class Uart
    {
    public:
        enum UartPort
        {
            Uart0,
            Uart1
        };
        uart_inst_t *uartPortToId[2] = {uart0, uart1};// to convert between UartPort and uart id

        enum Parity
        {
            Disabled,
            Even,
            Odd
        };
        // using Parity = uart_parity_t;

        Uart() = default;
        ~Uart() = default;

        template <UartPort port, uint baudrate, Parity parity = Parity::Disabled>
        void init()
        {
            // can evaluate the if at compile time
            if constexpr (port == UartPort::Uart0)
                init(uart0, baudrate, (uart_parity_t)parity);
            else if constexpr (port == UartPort::Uart1)
                init(uart1, baudrate, (uart_parity_t)parity);
        }

        void init(uart_inst_t *id, uint baudrate, uart_parity_t parity);

        /**
         * Read a single byte.
         *
         * @param[in] port the port to read from.
         * @param[out] data Byte read, if any.
         *
         * @return `true` if a byte was received, `false` otherwise.
         */
        bool read(UartPort port, uint8_t *data);

        /**
         * Read a block of bytes.
         *
         * @param[in] port the port to read from.
         * @param[out] data pointer to a buffer big enough to store `length` bytes
         * @param[in] length number of bytes to be read.
         *
         * @return number of bytes which could be read, maximal `length`.
         */
        std::size_t read(UartPort port, uint8_t *data, std::size_t length);

        /**
         * Empty the receive FIFO queue and hardware buffer.
         *
         * @param[in] port the port's buffer to discard.
         * @return the size of the deleted FIFO queue.
         */
        std::size_t discardReceiveBuffer(UartPort port);

        /**
         * Pushes a single byte into the buffer.
         *
         * @param[in] port the port to write to.
         * @return `true` if data has been successfully sent, `false` if buffer is full.
         * @note this writing is buffered.
         */
        bool write(UartPort port, uint8_t data);

        /**
         * Pushes a block of bytes into the buffer.
         *
         * @param[in] port the port to write to.
         * @param[in] data pointer to a buffer big enough to store `length` bytes.
         * @param[in] length number of bytes to be written.
         * @return the number of bytes that have been written.
         * @note this writing may be buffered.
         */
        std::size_t write(UartPort port, const uint8_t *data, std::size_t length);

        /**
         * Because the data is buffered, check here to see if the buffer is empty
         * (implying everything has been written).
         *
         * @param[in] port the port to see if writing is finished.
         * @return `true` if the buffer is empty and the last byte has been sent.
         */
        bool isWriteFinished(UartPort port) const;

        void flushWriteBuffer(UartPort port);


        /**
         * returns the pico uart id
         * 
         * @return uart_inst_t 
         */
        uart_inst_t *getUartID(UartPort port);

        bool isReadable(UartPort port);

    };
} // namespace pico::communication::serial

#endif //  PICO_UART_H_