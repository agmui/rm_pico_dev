/*
 * Copyright (c) 2020-2021 Advanced Robotics at the University of Washington <robomstr@uw.edu>
 *
 * This file is part of Taproot.
 *
 * Taproot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Taproot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Taproot.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "can.hpp"

// #include "modm/architecture/interface/can_message.hpp"
// #include "modm/platform.hpp"

#include "pico/stdlib.h"
#include "board.h"
// #include "tap/util_macros.hpp"

extern "C"
{
#include "can2040.h"
}
#include "pico/stdlib.h"

#include "RP2040.h"
#include "hardware/pio.h"

#include "../../clock.h"

#include <stdio.h>
#include <iostream>


#ifndef PLATFORM_HOSTED
// using namespace modm::platform;
#endif
// using namespace modm::literals;

namespace pico::can
{

    void
    Can::can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
    {
        if (notify == CAN2040_NOTIFY_RX)
        {
            printf("msg read: ");
            printf("%s\n", msg->data);
            message.id = msg->id;
            message.dlc = msg->id;
            for (int i = 0; i < 8; i++)
                message.data[i] = msg->data[i];
            last_read = pico::clock::getTimeMilliseconds();
        }
    }

    void
    Can::PIOx_IRQHandler(void)
    {
        can2040_pio_irq_handler(&cbus);
    }

    void pico::can::Can::initialize()
    {

        last_read = pico::clock::getTimeMilliseconds();
        uint32_t pio_num = 0;
        uint32_t sys_clock = 125000000, bitrate = 1000000;
        uint32_t gpio_rx = CAN0_RX_PIN, gpio_tx = CAN0_TX_PIN;

        // Setup canbus
        can2040_setup(&cbus, pio_num);
        can2040_callback_config(&cbus, can2040_cb);

        // Enable irqs
        irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
        NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
        NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

        // Start canbus
        can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);


    }

    bool Can::isMessageAvailable(pico::can::PioNum bus) const
    {

        switch (bus)
        {
        case PioNum::CAN_BUS0:
            return pico::clock::getTimeMilliseconds() - last_read < LAST_READ_TIME;//Can1::isMessageAvailable();
        case PioNum::CAN_BUS1:
            return false;//Can2::isMessageAvailable();//TODO:
        default:
            return false;
        }
    }

    bool Can::getMessage(pico::can::PioNum bus, can2040_msg *message)
    {

        switch (bus)
        {
        case PioNum::CAN_BUS0:
            message = &this->message;
            return true; //Can1::getMessage(*message);
        case PioNum::CAN_BUS1:
            return false;//Can2::getMessage(*message);//TODO
        default:
            return false;
        }
    }

    bool Can::isReadyToSend(PioNum bus) const
    {
        bool s;
        switch (bus)
        {
        //FIXME: can2040_check_transmit returns false?
        case PioNum::CAN_BUS0:
            s = can2040_check_transmit(&cbus);
            printf("isReadyToSend cbus: %d\n", s);
            return true; //s;
            // return can2040_check_transmit(&cbus);//Can1::isReadyToSend();
        case PioNum::CAN_BUS1:
            return false;//Can2::isReadyToSend();//TODO
        default:
            return false;
        }
    }

    bool Can::sendMessage(PioNum bus, /*const*/ can2040_msg &message)
    {
        std::cout << "sendMessage" << std::endl;
        for (int i = 0; i < 8; i++)
            printf("data: %#x\n",message.data[i]);
        
        switch (bus)
        {
        case PioNum::CAN_BUS0:
            return can2040_transmit(&cbus, &message);//Can1::sendMessage(message);
        case PioNum::CAN_BUS1:
            return false;//Can2::sendMessage(message);//TODO
        default:
            return false;
        }
    }
}