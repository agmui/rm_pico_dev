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
    /**
     * @brief A debugging class that has active cli to talk to the pico or change settings on the fly
     * 
     */
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
        /**
         * @brief Construct a new Debug object
         * 
         * @note creates CLI object
         * 
         * @param drivers 
         */
        Debug(pico::Drivers *drivers) : drivers(drivers), cli(new CLI(drivers)) {}
        ~Debug() = default;
        //==widget manager stuff==
        // void initUI();
        // void updateUI();
        // void houseKeeping();
        //========================
        void changeSetting();
        bool getSetting() {return false;};//todo

        /**
         * @brief runs next command from the queue
         * 
         */
        void runNextCommand();
    };

} // namespace debugTools

#endif // PICO_DEBUG_H_