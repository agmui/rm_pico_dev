#ifndef PICO_CLI_H_
#define PICO_CLI_H_

#include "Command.h"

#include <queue>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
#include <string>

#define CLI_BUFFER_SIZE 30

namespace pico
{
    class Drivers;
}

namespace debugtools
{

    /**
     * @brief function pointer definition
     * 
     */
    typedef void (*fn_ptr_t)(pico::Drivers *drivers);

    /**
     * @brief command struct
     * 
     */
    typedef struct
    {
        fn_ptr_t function; // function to be run
        const char *help; // the help message that is displayed
    } cmd_def_t;

    class CLI // TODO: add cmd history
    {
    private:
        pico::Drivers *drivers;
        std::queue<pico::CLI_Cmd *> queue;
        char buffer[CLI_BUFFER_SIZE];
        int chars_rxed = 0;

    public:
        /**
         * @brief 
         * map of command names to the command definition
         * 
         */
        static std::unordered_map<std::string, cmd_def_t> command_map;

        /**
         * @brief Construct a new CLI object
         * 
         * @param drivers 
         */
        CLI(pico::Drivers *drivers) : drivers(drivers) {}
        ~CLI(); // TODO

        /**
         * @brief 
         * reads usb RX FIFO into internal buffer
         * 
         * @note commands have a max length of \p CLI_BUFFER_SIZE
         * @return true if reading was successful false if
         *  command was too long or there was nothing in the fifo
         */
        bool readUSB();

        /**
         * @brief 
         * reads internal buffer and checks if its in \p command_map 
         * then it adds it to the queue
         * 
         * @return If command was found
         */
        bool findCommand();

        /**
         * @brief If there is a command in the queue
         * @return true if a command is waiting 
         */
        bool hasNextComand();

        /**
         * @brief Get the Next Command object in queue
         * 
         * @return pico::CLI_Cmd* 
         */
        pico::CLI_Cmd *getNextCommand();
    };
}

#endif // PICO_CLI_H_