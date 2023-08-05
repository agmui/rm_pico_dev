#include "CLI.h"
#include "Command.h"
#include "pico/stdlib.h"
#include "board.h"

#include <iostream>
#include <stdio.h>
#include <string>

#include <stdlib.h>
#include <string.h>

using namespace std;

namespace debugtools
{
    // Todo: use irq
    bool CLI::readUSB()
    {
        // std::cout << "reading" << std::endl;
        int ch = PICO_ERROR_TIMEOUT;
        do
        {
            ch = getchar_timeout_us(0);
            buffer[chars_rxed] = (char)ch;
            chars_rxed++;
            // printf("ch:%c\n",ch);
        } while (ch != PICO_ERROR_TIMEOUT && chars_rxed < CLI_BUFFER_SIZE);
        buffer[chars_rxed - 1] = '\0';
        // std::cout << "read:"<< chars_rxed << std::endl;
        if (chars_rxed >= CLI_BUFFER_SIZE)
        {
            printf("> ERROR: %s is too long of a command\n", buffer);
            return false;
        }
        else if (chars_rxed > 1)
        {
            printf("> recived cmd: %s\n", buffer);
            chars_rxed = 0;
            return true;
        }
        chars_rxed = 0;
        return false;
    }

    bool CLI::findCommand()
    {
        // if (!isprint(ch) && !isspace(ch) && '\r' != ch &&
        //     '\b' != ch && ch != (char)127)
        //     return;
        // printf("%c", ch); // echo

        stdio_flush();
        // TODO make thread safe(strtok is not thread safe)
        unordered_map<string, pico::cmd_def_t>::const_iterator cmd = pico::command_map.find(string(strtok(buffer," ")));
        if (cmd == pico::command_map.end())
        {
            std::cout << "> \"" << buffer << "\" is an not a command" << std::endl;
            return false;
        }
        // std::cout << "> running: " << buffer << std::endl;
        queue.push(new pico::CLI_Cmd(drivers, cmd->second.function));
        return true;
    }

    pico::CLI_Cmd *CLI::getNextCommand()
    {
        // TODO: check if queue empty
        pico::CLI_Cmd *cmd = queue.front();
        queue.pop();
        return cmd;
    }

} // namespace pico
