#ifndef PICO_BOARD_H_
#define PICO_BOARD_H_

#include "hardware/uart.h"
#include "Uart.h"

#define UART0_TX_PIN 0
#define UART0_RX_PIN 1

#define UART1_TX_PIN 0
#define UART1_RX_PIN 1

#define CAN0_RX_PIN 4
#define CAN0_TX_PIN 5

#define CAN1_RX_PIN 4
#define CAN1_TX_PIN 5

namespace Board
{
    const pico::communication::serial::Uart::UartPort REMOTE_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart0;
    const pico::communication::serial::Uart::UartPort REF_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart1;
    

} // namespace Board

#endif // PICO_BOARD_H_