#ifndef PICO_CLI_H_
#define PICO_CLI_H_

#include "Command.h"
#include <queue>

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

#define CLI_BUFFER_SIZE 30

namespace debugtools
{
    class CLI//TODO: add cmd history
    {
    private:
        std::queue<pico::Command *> queue;
        char buffer[CLI_BUFFER_SIZE];
        int chars_rxed = 0;

    public:
        CLI() = default;
        ~CLI(); //TODO
        bool readUSB();
        bool findCommand();
        bool hasNextComand();
        pico::Command* getNextCommand();

    };
}

#endif // PICO_CLI_H_