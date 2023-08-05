#ifndef PICO_BOARD_H_
#define PICO_BOARD_H_

//spi section just for hw_config.c
#define SD_CARD_MISO 12        // gpio
#define SD_CARD_MOSI 15        // gpio
#define SD_CARD_SCK 14         // gpio
#define SD_CARD_SS 9           // gpio
#define SD_CARD_CARD_DETECT 13 // gpio

//TODO: fix
#ifdef __cplusplus

#include "hardware/uart.h"
#include "Uart.h"
#include <unordered_map>
#include <string>
#include "Command.h"

//TODO: rename from PIN to GPIO
#define UART0_TX_PIN 0//gpio
#define UART0_RX_PIN 1//gpio

#define UART1_TX_PIN 0//gpio
#define UART1_RX_PIN 1//gpio

#define CAN0_RX_PIN 4//gpio
#define CAN0_TX_PIN 5//gpio

#define CAN1_RX_PIN 4//gpio
#define CAN1_TX_PIN 5//gpio

namespace Board
{
    const pico::communication::serial::Uart::UartPort REMOTE_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart0;
    const pico::communication::serial::Uart::UartPort REF_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart1;


} // namespace Board
#endif

#endif // PICO_BOARD_H_