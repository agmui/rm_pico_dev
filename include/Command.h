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
  protected:
    Drivers *drivers;

  public:
    std::string name = "plzNameCmdLuL";
    // Command(Drivers *drivers);
    virtual ~Command(){};
    void passInDrivers(Drivers *drivers) { this->drivers = drivers; };
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
      std::cout << "ran test cmd uwu" << std::endl;
    }
  };

  class ls : public Command
  {
  public:
    void Execute() const override
    {
      std::cout << "running ls" << std::endl;
      // std::vector<std::string> list = drivers->sdCard.getFileList()
      // for(auto f : list)
      // {
      //   std::cout << f << std::endl;
      // }
    }
  };
}

#endif // PICO_COMMAND_H_