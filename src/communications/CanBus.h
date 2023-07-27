#ifndef PICO_CANBUS_H_
#define PICO_CANBUS_H_

#include "../../lib/can2040/src/can2040.h"

namespace pico::can
{
    class CanBus
    {
    private:
        /* data */
    public:
        CanBus(/* args */);
        ~CanBus();
    };
    
} // namespace pico::can


#endif //  PICO_CANBUS_H_