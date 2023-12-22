#ifndef PICO_DRIVERS_H_
#define PICO_DRIVERS_H_

#include "Debug.h"
#include "MotorHandler.h"
#include "BNO055.h"
#include "RefSerial.h"
#include "Remote.h"
#include "SDCard.h"
#include "Uart.h"
#include "../src/communications/can/can.hpp"

namespace pico
{
    class Drivers
    {
    protected:
    public: // TODO: make thread safe?
        Drivers() //only use in mock
            : debug(this),
              motorHandler(this),
              bmo055(this),
              refSerial(this),
              remote(this),
              uart(),
              sdCard(this),
              can()// TODO: maybe not needed
        {
        }

        static Drivers *drivers;


        debugtools::Debug debug;
        motor::MotorHandler motorHandler;
        communication::sensors::imu::bno055::BNO055 bmo055;
        communication::serial::RefSerial refSerial;
        communication::serial::Remote remote;
        debugtools::SDCard sdCard;
        communication::serial::Uart uart;
        can::Can can;

        // shoud now be cloneable
        Drivers(Drivers &other) = delete;

        void operator=(const Drivers &) = delete;

        // static Drivers *getDrivers();
        static Drivers *getDrivers()
        {
            if (drivers == nullptr)
                drivers = new Drivers();
            return drivers;
        }
    };

} // namespace driver

#endif //  PICO_DRIVERS_H_