#ifndef PICO_COMMAND_H_
#define PICO_COMMAND_H_

// #include "drivers.h"
#include <string>
#include <iostream>

namespace pico
{
  class Drivers;
}

namespace pico
{
  class Command
  {
  private:
    Drivers *drivers;

  public:
    std::string name = "plzNameCmdLuL";
    // Command(Drivers *drivers);
    virtual ~Command(){};
    void passInDrivers(Drivers *drivers){this->drivers = drivers;};
    virtual void Execute() const = 0;
  };
}

namespace pico
{
  class TestCmd : public Command
  {
  public:
    // TestCmd(Drivers *drivers) : drivers(drivers){name="test";};
    // TestCmd() = default;
    void Execute() const override
    {
      std::cout << "ran test cmd" << std::endl;
    }
  };

  class ls : public Command
  {
  public:
    void Execute() const override
    {
      std::cout << "ls" << std::endl;
    }
  };
}

#endif // PICO_COMMAND_H_