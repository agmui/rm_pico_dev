#ifndef PICO_BOARD_H_
#define PICO_BOARD_H_

#include "hardware/uart.h"
#include "Uart.h"

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1

#define UART1_TX_PIN 0
#define UART1_RX_PIN 1

namespace Board
{
    const pico::communication::serial::Uart::UartPort REMOTE_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart0;
} // namespace Board

#endif // PICO_BOARD_H_