#ifndef PICO_CLOCK_H_
#define PICO_CLOCK_H_

#include <cstdint>

#include "pico/stdlib.h"

namespace pico::clock {

#if defined(PLATFORM_HOSTED) && defined(ENV_UNIT_TESTS)
    /**
     * Object that allows you to control the global time returned by the `getTime*()` functions. Only a
     * single ClockStub may be constructed in the same scope. This is a stub designed for testing. To
     * use, declare a `ClockStub` in your test and set the `time` variable during the test when you
     * would like. The `ClockStub` you constructed will add itself as the global instance of the clock
     * stub upon construction and remove itself as the global instance when it is destructed.
     *
     * If multiple `ClockStub` instances are declared in the same scope, the program will assert and
     * crash.
     *
     * If no `ClockStub` is declared in the test's scope, the `getTime*()` functions will return 0.
     */
    class ClockStub final
    {
    public:
        ClockStub();
        ~ClockStub();
        uint32_t time = 0;
    };

    uint32_t getTimeMilliseconds();
    uint32_t getTimeMicroseconds();
#else

    inline uint32_t getTimeMilliseconds() { return time_us_32()/1000; }

/**
 * @warning This clock time will wrap every 72 minutes. Do not use unless absolutely necessary.
 */
    inline uint32_t getTimeMicroseconds() {
        return time_us_32();
    }

#endif


} // namespace pico::clock

#endif //  PICO_CLOCK_H_