#include "Remote.h"
#include "pico/stdlib.h"
#include "board.h"
#include "drivers.h"
#include "../clock.h"

#ifdef DEBUG
#include <stdio.h>
#endif // DEBUG
#include <iostream>

namespace pico::communication::serial
{
    void Remote::initialize()
    {
        drivers->uart.init<Board::REMOTE_SERIAL_UART_PORT, 100000, Uart::Parity::Even>();
    }

    void Remote::read() // TODO: check if remote init before read?
    {
        if (pico::clock::getTimeMilliseconds() - last_read > REMOTE_DISCONNECT_TIMEOUT)
        {
            // std::cout << time_us_32() - last_read << std::endl;
            connected = false;
            // clearRxBuffer();
        }
        uint8_t data;
        while (drivers->uart.read(Board::REMOTE_SERIAL_UART_PORT, &data) && chars_rxed < 18)
        {
            // std::cout << "read:" << std::endl;
            // drivers->uart.read(Board::REMOTE_SERIAL_UART_PORT, &data);
            // data = uart_getc(uart0);

            last_read = pico::clock::getTimeMilliseconds();
            // printf("data: %#x\n", data);
            rxBuffer[chars_rxed] = data; // ch;
            chars_rxed++;

            if (chars_rxed >= 18)
            {
                connected = true;
                parseBuffer();
                clearRxBuffer();
            }
        }
    }

    bool Remote::isConnected() const { return connected; }

    float Remote::getChannel(Channel ch) const
    {
        switch (ch)
        {
        case Channel::RIGHT_HORIZONTAL:
            return remote.rightHorizontal / STICK_MAX_VALUE;
        case Channel::RIGHT_VERTICAL:
            return remote.rightVertical / STICK_MAX_VALUE;
        case Channel::LEFT_HORIZONTAL:
            return remote.leftHorizontal / STICK_MAX_VALUE;
        case Channel::LEFT_VERTICAL:
            return remote.leftVertical / STICK_MAX_VALUE;
        }
        return 0;
    }

    Remote::SwitchState Remote::getSwitch(Switch sw) const
    {
        switch (sw)
        {
        case Switch::LEFT_SWITCH:
            return remote.leftSwitch;
        case Switch::RIGHT_SWITCH:
            return remote.rightSwitch;
        }
        return SwitchState::UNKNOWN;
    }

    void Remote::parseBuffer()
    {

// #ifdef DEBUG
// /*
        printf("\nrxBuffer: ");
        for (int i = 0; i < 18; i++)
        {
            printf("%x,", rxBuffer[i]);
            // save_data[i] = data[i];
            // data[i] = 0;
        }
        printf("\n");
// */
// #endif // DEBUG

        // this is a wonky encoding implemented by our "good pal Li Qingzhi" as stated by a chinese
        // translated document our team acquired a while back; refer to this document for the protocol
        // encoding: https://drive.google.com/file/d/1a5kaTsDvG89KQwy3fkLVkxKaQJfJCsnu/view?usp=sharing

        // remote joystick information
        remote.rightHorizontal = (rxBuffer[0] | rxBuffer[1] << 8) & 0x07FF;
        remote.rightHorizontal -= 1024;
        remote.rightVertical = (rxBuffer[1] >> 3 | rxBuffer[2] << 5) & 0x07FF;
        remote.rightVertical -= 1024;
        remote.leftHorizontal = (rxBuffer[2] >> 6 | rxBuffer[3] << 2 | rxBuffer[4] << 10) & 0x07FF;
        remote.leftHorizontal -= 1024;
        remote.leftVertical = (rxBuffer[4] >> 1 | rxBuffer[5] << 7) & 0x07FF;
        remote.leftVertical -= 1024;

        remote.leftSwitch = static_cast<Remote::SwitchState>((rxBuffer[5] >> 6) & 0x03);
        remote.rightSwitch = static_cast<Remote::SwitchState>((rxBuffer[5] >> 4) & 0x03);

        // mouse input
        remote.mouse.x = rxBuffer[6] | (rxBuffer[7] << 8);   // x axis
        remote.mouse.y = rxBuffer[8] | (rxBuffer[9] << 8);   // y axis
        remote.mouse.z = rxBuffer[10] | (rxBuffer[11] << 8); // z axis
        remote.mouse.l = static_cast<bool>(rxBuffer[12]);    // left button click
        remote.mouse.r = static_cast<bool>(rxBuffer[13]);    // right button click

        // keyboard capture
        remote.key = rxBuffer[14] | rxBuffer[15] << 8;
        // remote wheel
        remote.wheel = (rxBuffer[16] | rxBuffer[17] << 8) - 1024;

        // the remote joystick and wheel values must be <= abs(660)
        if ((abs(remote.rightHorizontal) > STICK_MAX_VALUE) ||
            (abs(remote.rightVertical) > STICK_MAX_VALUE) ||
            (abs(remote.leftHorizontal) > STICK_MAX_VALUE) ||
            (abs(remote.leftVertical) > STICK_MAX_VALUE) || (abs(remote.wheel) > STICK_MAX_VALUE))
        {
            // RAISE_ERROR(drivers, "invalid remote joystick values");
            printf("ERROR: invalid remote joystick values\n");
            printf("checks: rightH %d, rightV %d, leftH %d, leftV %d, wheel %d\n",
                (abs(remote.rightHorizontal) > STICK_MAX_VALUE),
                (abs(remote.rightVertical) > STICK_MAX_VALUE),
                (abs(remote.leftHorizontal) > STICK_MAX_VALUE),
                (abs(remote.leftVertical) > STICK_MAX_VALUE),
                (abs(remote.wheel) > STICK_MAX_VALUE)
            );
            printf("vals: %d, %d, %d, %d, %d\n",
                remote.rightHorizontal,
                remote.rightVertical,
                remote.leftHorizontal,
                remote.leftVertical,
                remote.wheel
            );
        }

        //TODO:
        // drivers->commandMapper.handleKeyStateChange(
        //     remote.key,
        //     remote.leftSwitch,
        //     remote.rightSwitch,
        //     remote.mouse.l,
        //     remote.mouse.r);

        remote.updateCounter++;
    }

    void Remote::clearRxBuffer()
    {
        chars_rxed = 0;
        for (int i = 0; i < REMOTE_BUF_LEN; i++)
        {
            rxBuffer[i] = 0;
        }
        // Clear Uart0 rxBuffer
        drivers->uart.discardReceiveBuffer(Board::REMOTE_SERIAL_UART_PORT);
    }

    void Remote::reset()
    {
        remote.rightHorizontal = 0;
        remote.rightVertical = 0;
        remote.leftHorizontal = 0;
        remote.leftVertical = 0;
        remote.leftSwitch = SwitchState::UNKNOWN;
        remote.rightSwitch = SwitchState::UNKNOWN;
        remote.mouse.x = 0;
        remote.mouse.y = 0;
        remote.mouse.z = 0;
        remote.mouse.l = 0;
        remote.mouse.r = 0;
        remote.key = 0;
        remote.wheel = 0;
        clearRxBuffer();

        // Refresh command mapper with all keys deactivated. This prevents bug where
        // command states enter defaults when remote reconnects even if key/switch
        // state should do otherwise
        //TODO:
        // drivers->commandMapper
        //     .handleKeyStateChange(0, SwitchState::UNKNOWN, SwitchState::UNKNOWN, false, false);
    }

    uint32_t Remote::getUpdateCounter() const { return remote.updateCounter; }
} // namespace pico::communication::serial
