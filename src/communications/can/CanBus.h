#ifndef PICO_CANBUS_H_
#define PICO_CANBUS_H_

#include <cstdint>
#include "../../../lib/can2040/src/can2040.h"

namespace pico
{
    class Drivers;    
}
namespace pico::can
{
    enum PioNum
    {
        CAN_BUS0,
        CAN_BUS1
    };
    class CanBus
    {
    private:
        /* data */
    public:
        // CanBus(Drivers* drivers, uint32_t id, PioNum cB);
        // ~CanBus();
    };
    
} // namespace pico::can


#endif //  PICO_CANBUS_H_