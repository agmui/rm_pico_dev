#ifndef PICO_COMMAND_H_
#define PICO_COMMAND_H_

// #include "drivers.h"
#include <string>
#include <iostream>
// #include "../src/Debug/CliFunctions.h"
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
  typedef void (*fn_ptr_t)(Drivers* drivers);//todo move whole class to CLI.h

  class CLI_Cmd : public Command
  {
  private:
    fn_ptr_t function;

  public:
    CLI_Cmd(Drivers *drivers, fn_ptr_t function) : function(function) { this->drivers = drivers; }
    void Execute() const override
    {
      function(drivers);
    }
  };
}

#endif // PICO_COMMAND_H_