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

#ifndef PICO_CAN_HPP_
#define PICO_CAN_HPP_

// #include "tap/util_macros.hpp"

extern "C"
{
// #include "can2040.h"
#include "../../../lib/can2040/src/can2040.h"
}
#include "CanBus.h"

#define LAST_READ_TIME 100

// namespace modm::can
// {
// class Message;
// }

namespace pico
{
namespace can
{
/**
 * A simple CAN wrapper class that handles I/O from both CAN bus 1 and 2.
 */
class Can
{
private:
    // the pico uses irq for can
    inline static struct can2040 cbus;
    inline static can2040_msg message;
    static void can2040_cb(struct can2040 * cd, uint32_t notify, struct can2040_msg * msg);
    static void PIOx_IRQHandler(void);
    static int last_read;
public:
    Can() = default;
    // DISALLOW_COPY_AND_ASSIGN(Can)
    ~Can() = default;

    /**
     * Initializes CAN 1 and CAN 2 hardware to pins specific to the development
     * board and sets up the CAN bus filters necessary for reading
     * from the CAN bus.
     *
     * @note CAN 1 is connected to pins D0 (RX) and D1 (TX) and
     *      CAN 2 is connected to pins B12 (RX) and B12 (TX).
     * @note The CAN filters are set up to receive NOT extended identifier IDs.
     */
    void initialize();

    /**
     * Checks the passed in CanBus to see if there is a message waiting
     * and available.
     *
     * @param[in] bus the CanBus to check for a message.
     * @return true if a message is available, false otherwise.
     */
    bool isMessageAvailable(PioNum bus) const;

    /**
     * Checks the CanBus for a message and if a message is successfully
     * acquired, returns true and places the message in the return parameter
     * message.
     *
     * @param[in] bus the CanBus to acquire a message from.
     * @param[out] message a return parameter which the message is
     *      placed in.
     * @return true if a valid message was placed in the parameter
     *      message. False otherwise.
     */
    bool getMessage(PioNum bus, can2040_msg *message);

    /**
     * Checks the given CanBus to see if the CanBus is idle.
     *
     * @param[in] bus the CanBus to check.
     * @return true if the bus is not busy, false otherwise.
     */
    bool isReadyToSend(PioNum bus) const;

    /**
     * Sends the passed in message over the CanBus. Returns whether or
     * not the message succeeded.
     *
     * @attention `modm::can::Message` defaults to an extended
     * message identifier. For all RoboMaster products we have, we do not
     * want our messages to be extended. Be sure to be explicit
     * when instantiating a message object and setting extended to
     * false.
     *
     * @param[in] bus the `CanBus` for which the message should be sent across.
     * @param[in] message the message to send
     * @return true if the message was successfully sent, false otherwise.
     */
    bool sendMessage(PioNum bus, /*const*/ can2040_msg &message);
};  // class Can

}  // namespace can
}  // namespace pico

#endif  // PICO_CAN_HPP_
