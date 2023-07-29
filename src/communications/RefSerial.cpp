#include "RefSerial.h"
#include "board.h"
#include "../endianness_wrappers.hpp"
#include "DJISerial.h"

#include "../clock.h"
#include "../endianness_wrappers.hpp"
// #include "drivers.h"

using namespace pico::arch;

namespace pico::communication::serial
{
RefSerial::RefSerial(Drivers* drivers)
    : DJISerial(drivers, Board::REF_SERIAL_UART_PORT)
    //   robotData(),
    //   gameData(),
    //   receivedDpsTracker()
{
    // refSerialOfflineTimeout.stop();
}

}  // namespace tap::communication::serial
