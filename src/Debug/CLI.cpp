#include "CLI.h"
#include "Command.h"
#include "pico/stdlib.h"
#include "board.h"
#include "CliFunctions.h"

#include <iostream>
#include <stdio.h>
#include <string>

#include <stdlib.h>
#include <string.h>

using namespace std;

namespace debugtools
{
    std::unordered_map<std::string, cmd_def_t> CLI::command_map = {
        {"setrtc", {run_setrtc, "setrtc <DD> <MM> <YY> <hh> <mm> <ss>:\n"
                                "  Set Real Time Clock\n"
                                "  Parameters: new date (DD MM YY) new time in 24-hour format "
                                "(hh mm ss)\n"
                                "\te.g.:setrtc 16 3 21 0 4 0"}},
        {"date", {run_date, "date:\n Print current date and time"}},
        //   {"lliot", {run_lliot, "lliot <drive#>:\n !DESTRUCTIVE! Low Level I/O Driver Test\n"
        //                         "\te.g.: lliot 1"}},
        {"format", {run_format, "format [<drive#:>]:\n"
                                "  Creates an FAT/exFAT volume on the logical drive.\n"
                                "\te.g.: format 0:"}},
        {"mount", {run_mount, "mount [<drive#:>]:\n"
                              "  Register the work area of the volume\n"
                              "\te.g.: mount 0:"}},
        {"unmount", {run_unmount, "unmount <drive#:>:\n"
                                  "  Unregister the work area of the volume"}},
        {"chdrive", {run_chdrive, "chdrive <drive#:>:\n"
                                  "  Changes the current directory of the logical drive.\n"
                                  "  <path> Specifies the directory to be set as current directory.\n"
                                  "\te.g.: chdrive 1:"}},
        {"getfree", {run_getfree, "getfree [<drive#:>]:\n"
                                  "  Print the free space on drive"}},
        {"cd", {run_cd, "cd <path>:\n"
                        "  Changes the current directory of the logical drive.\n"
                        "  <path> Specifies the directory to be set as current directory.\n"
                        "\te.g.: cd /dir1"}},
        {"mkdir", {run_mkdir, "mkdir <path>:\n"
                              "  Make a new directory.\n"
                              "  <path> Specifies the name of the directory to be created.\n"
                              "\te.g.: mkdir /dir1"}},
        {"del_node", {run_del_node, "del_node <path>:\n"
                                    "  Remove directory and all of its contents. (kinda like rm -rf)\n"
                                    "  <path> Specifies the name of the directory to be deleted.\n"
                                    "\te.g.: del_node /dir1"}},
        {"ls", {run_ls, "ls:\n  List directory"}},
        {"cat", {run_cat, "cat <filename>:\n  Type file contents"}},
        {"start_logger", {run_start_logger, "start_logger:\n" // TODO
                                            "  Start Data Log Demo"}},
        {"stop_logger", {run_stop_logger, "stop_logger:\n"
                                          "  Stop Data Log Demo"}},
        //   {"help", {run_help, "help:\n"
        //                       "  Shows this command help."}}
    };

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
        unordered_map<string, cmd_def_t>::const_iterator cmd = command_map.find(string(strtok(buffer, " ")));
        if (cmd == command_map.end())
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
