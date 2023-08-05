#ifndef PICO_COMMAND_H_
#define PICO_COMMAND_H_

// #include "drivers.h"
#include <string>
#include <iostream>
#include "../src/Debug/CliFunctions.cpp"
#include <unordered_map>

namespace pico
{
  class Drivers;
}

// TODO: delete command after use
namespace pico
{
  class Command
  {
  protected:
    Drivers *drivers;

  public:
    // Command(Drivers *drivers);
    virtual ~Command(){};
    // void passInDrivers(Drivers *drivers) { this->drivers = drivers; };
    virtual void Execute() const = 0;
  };
}

namespace pico
{
  typedef void (*fn_ptr_t)();
  typedef struct
  {
    // char const *const command;
    fn_ptr_t const function;
    char const *const help;
  } cmd_def_t;
  const std::unordered_map<std::string, cmd_def_t> command_map = {
      {"setrtc", {run_setrtc,
        "setrtc <DD> <MM> <YY> <hh> <mm> <ss>:\n"
        "  Set Real Time Clock\n"
        "  Parameters: new date (DD MM YY) new time in 24-hour format "
        "(hh mm ss)\n"
        "\te.g.:setrtc 16 3 21 0 4 0"}},
      {"date", {run_date, "date:\n Print current date and time"}},
      /*{"lliot", {run_lliot, "lliot <drive#>:\n !DESTRUCTIVE! Low Level I/O Driver Test\n"
                            "\te.g.: lliot 1"}},*/
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
                                  "  Remove directory and all of its contents.\n"
                                  "  <path> Specifies the name of the directory to be deleted.\n"
                                  "\te.g.: del_node /dir1"}},
      {"ls", {run_ls, "ls:\n  List directory"}},
      {"cat", {run_cat, "cat <filename>:\n  Type file contents"}},
      // {"simple", {simple, "simple:\n  run simple FS tests"}},
      /*{"big_file_test", {run_big_file_test, "big_file_test <pathname> <size in bytes> <seed>:\n"
                                            " Writes random data to file <pathname>.\n"
                                            " <size in bytes> must be multiple of 512.\n"
                                            "\te.g.: big_file_test bf 1048576 1\n"
                                            "\tor: big_file_test big3G-3 0xC0000000 3"}},
      {"cdef", {run_cdef, "cdef:\n  Create Disk and Example Files\n"
                          "  Expects card to be already formatted and mounted"}},
      {"swcwdt", {run_swcwdt, "\nswcwdt:\n Stdio With CWD Test\n"
                              "Expects card to be already formatted and mounted.\n"
                              "Note: {run cdef first!"}},
      {"loop_swcwdt", {run_loop_swcwdt, "\nloop_swcwdt:\n {run Create Disk and Example Files and Stdio With CWD "
                                        "Test in a loop.\n"
                                        "Expects card to be already formatted and mounted.\n"
                                        "Note: Type any key to quit."}},*/
      {"start_logger", {run_start_logger, "start_logger:\n"//TODO
                                          "  Start Data Log Demo"}},
      {"stop_logger", {run_stop_logger, "stop_logger:\n"
                                        "  Stop Data Log Demo"}},
      /*{"help", {run_help, "help:\n"
                          "  Shows this command help."}}*/};

  class CLI_Cmd : public Command
  {
  private:
    fn_ptr_t function;

  public:
    CLI_Cmd(Drivers *drivers, fn_ptr_t function) : function(function) { this->drivers = drivers; }
    void Execute() const override
    {
      function();
    }
  };
}

#endif // PICO_COMMAND_H_