#ifndef PICO_DEBUG_H_
#define PICO_DEBUG_H_

#include <cstdint>
#include <unordered_map>
#include "../src/Debug/CLI.h"
// #include <retroTerm.h> //Include terminal library

// typedef void (*f_ptr)(retroTerm); // function pointer type
namespace pico
{
    class Drivers;
}

namespace debugtools
{
    class Debug
    {
    private:
        pico::Drivers *drivers;
        CLI *cli;

        //==widget manager stuff== TODO: make retroTerm work
        // retroTerm terminal; // Create a terminal instance
        // std::unordered_map<uint8_t, f_ptr> widgetIds;

        // void widgetSetup();
        //========================
    public:
        Debug(pico::Drivers *drivers) : drivers(drivers), cli(new CLI(drivers)) {}
        ~Debug() = default;
        //==widget manager stuff==
        // void initUI();
        // void updateUI();
        // void houseKeeping();
        //========================
        void changeSetting();
        void runNextCommand();
    };

} // namespace debugTools

#endif // PICO_DEBUG_H_