#include "Uart.h"
#include "board.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

namespace pico::communication::serial
{
    void Uart::init(uart_inst_t *id, uint baudrate, uart_parity_t parity)
    {
        // Set up our UART with a basic baud rate.
        uart_init(id, baudrate);

        // Set the TX and RX pins by using the function select on the GPIO
        // Set datasheet for more information on function select
        if (id == uart0)
        {
            gpio_set_function(UART0_TX_PIN, GPIO_FUNC_UART);
            gpio_set_function(UART0_RX_PIN, GPIO_FUNC_UART);
        }
        else
        {
            gpio_set_function(UART1_TX_PIN, GPIO_FUNC_UART);
            gpio_set_function(UART1_RX_PIN, GPIO_FUNC_UART);
        }

        // Set UART flow control CTS/RTS, we don't want these, so turn them off
        uart_set_hw_flow(id, false, false);

        // Set our data format
        uart_set_format(id, DATA_BITS, STOP_BITS, parity);

        // Turn off FIFO's - we want to do this character by character
        // uart_set_fifo_enabled(id, false);

        // Set up a RX interrupt
        // We need to set up the handler first
        // Select correct interrupt for the UART we are using
        int UART_IRQ = id == uart0 ? UART0_IRQ : UART1_IRQ;
    }

    bool Uart::read(UartPort port, uint8_t *data)
    {
        uart_read_blocking(getUartID(port), data, 1);
        // uint8_t ch = uart_getc(getUartID(port));
        // data = &ch;
        return false;
    }

    uart_inst_t *Uart::getUartID(UartPort port)
    {
        return (port == UartPort::Uart0) ? uart0 : uart1;
        // return uart0;
    }

    bool Uart::isReadable(UartPort port)
    {
        return uart_is_readable(getUartID(port));
    }

} // namespace pico::communication::serial
