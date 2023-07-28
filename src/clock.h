#ifndef PICO_CLOCK_H_
#define PICO_CLOCK_H_

#include "pico/stdlib.h"

namespace pico::clock
{
    inline uint32_t getTimeMilliseconds() { return time_us_32(); }
} // namespace pico::clock

#endif //  PICO_CLOCK_H_