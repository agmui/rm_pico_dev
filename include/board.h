#ifndef PICO_BOARD_H_
#define PICO_BOARD_H_

//spi section just for hw_config.c
#define SD_CARD_MISO 16        // gpio
#define SD_CARD_MOSI 19        // gpio
#define SD_CARD_SCK 18         // gpio
#define SD_CARD_SS 17           // gpio
//#define SD_CARD_CARD_DETECT 13 // gpio

//TODO: fix
#ifdef __cplusplus

#include "hardware/uart.h"
#include "Uart.h"
#include <unordered_map>
#include <string>
#include "Command.h"

#define UART0_TX_GPIO 12//gpio
#define UART0_RX_GPIO 13//gpio

#define UART1_TX_GPIO 4//gpio
#define UART1_RX_GPIO 5//gpio

#define CAN0_RX_GPIO 4//gpio
#define CAN0_TX_GPIO 5//gpio

#define CAN1_RX_GPIO 4//gpio
#define CAN1_TX_GPIO 5//gpio

#define IMU_SDA_GPIO 2
#define IMU_SCL_GPIO 3

#define QUAD1_A_GPIO 8
#define QUAD1_B_GPIO 9

#define QUAD2_A_GPIO 10
#define QUAD2_B_GPIO 11

#define SERVO_GPIO 14

#define LED_R_GPIO 20
#define LED_G_GPIO 21
#define LED_B_GPIO 22


namespace Board {
    const pico::communication::serial::Uart::UartPort REMOTE_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart0;
    const pico::communication::serial::Uart::UartPort REF_SERIAL_UART_PORT = pico::communication::serial::Uart::UartPort::Uart1;


} // namespace Board
#endif

#endif // PICO_BOARD_H_