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

    typedef void (*fn_ptr_t)(pico::Drivers *drivers);
    typedef struct
    {
        fn_ptr_t function;
        const char *help;//todo
    } cmd_def_t;

    class CLI // TODO: add cmd history
    {
    private:
        pico::Drivers *drivers;
        std::queue<pico::CLI_Cmd *> queue;
        char buffer[CLI_BUFFER_SIZE];
        int chars_rxed = 0;

    public:
        static std::unordered_map<std::string, cmd_def_t> command_map;
        CLI(pico::Drivers *drivers) : drivers(drivers) {}
        ~CLI(); // TODO
        bool readUSB();
        bool findCommand();
        bool hasNextComand();
        pico::CLI_Cmd *getNextCommand();
    };
}

#endif // PICO_CLI_H_