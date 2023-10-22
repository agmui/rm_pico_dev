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
        uart_set_fifo_enabled(id, false);

        // Set up a RX interrupt
        // We need to set up the handler first
        // Select correct interrupt for the UART we are using
        int UART_IRQ = id == uart0 ? UART0_IRQ : UART1_IRQ;

        // And set up and enable the interrupt handlers
        irq_set_exclusive_handler(UART_IRQ, on_uart_rx0);
        irq_set_enabled(UART_IRQ, true);

        // Now enable the UART to send interrupts - RX only
        uart_set_irq_enables(id, true, false);
    }


    /**
     * @brief
     * uart RX interrupt handler
     */
    void Uart::on_uart_rx0()
    {
        // while stuff is in rx fifo
        while (uart_is_readable(uart0))
        {
            // read one byte(blocking)
            //API: https://www.raspberrypi.com/documentation/pico-sdk/hardware.html#rpipbf59a4c19126a5547408
            uint8_t ch; 
            uart_read_blocking(uart0, &ch, 1);
            rxBuffer0.push(ch);
        }
    }

    bool Uart::read(UartPort port, uint8_t *data)
    {
        if(rxBuffer0.empty()) return false;
        else if(port==UartPort::Uart0){
            *data = rxBuffer0.front();
            rxBuffer0.pop();
        }
        // uart_read_blocking(getUartID(port), data, 1);
        // uint8_t ch = uart_getc(getUartID(port));
        // data = &ch;
        return true;
    }

    std::size_t Uart::discardReceiveBuffer(UartPort port)
    {
        uint8_t rx_drained_chars = 0;
        // while (uart_is_readable(uart_id))
        // {
        //     uart_getc(uart_id);
        //     rx_drained_chars++;
        // }
        // return rx_drained_chars;
        if(port==Uart0){
            while(!rxBuffer0.empty()){
                rx_drained_chars++;
                rxBuffer0.pop();
            } 
        }
        return rx_drained_chars;
    }

    uart_inst_t *Uart::getUartID(UartPort port)
    {
        return uartPortToId[port];
        // return (port == UartPort::Uart0) ? uart0 : uart1;
    }

    bool Uart::isReadable(UartPort port)
    {
        return uart_is_readable(getUartID(port));
    }

} // namespace pico::communication::serial
