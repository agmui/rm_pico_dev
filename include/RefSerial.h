#ifndef  PICO_REFSERIAL_H_
#define  PICO_REFSERIAL_H_

// #include <cstdint>
// #include <unordered_map>

#include "../src/communications/DJISerial.h"

// #include "../src/communications/RefSerialData.h"
// #include "../src/timeout.hpp"
// #include "../src/modm/deque.hpp"


// #include <cstdint>
// #include <unordered_map>

namespace pico
{
    class Drivers;
}

namespace pico::communication::serial
{

class RefSerial : public DJISerial //, public RefSerialData
{

public:

    RefSerial(Drivers* drivers);
    ~RefSerial() = default;

};

}  // namespace tap::communication::serial

#endif  // PICO_REF_SERIAL_H_
