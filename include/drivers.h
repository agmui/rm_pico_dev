#ifndef PICO_DRIVERS_H_
#define PICO_DRIVERS_H_

#include "Debug.h"
#include "MotorHandler.h"
#include "MPU6050.h"
#include "RefSerial.h"
#include "Remote.h"
#include "SDCard.h"
#include "Uart.h"

namespace pico
{
    class Drivers
    {
    protected:
        // Drivers()
        //     : debug(this),
        //       //   motorHandler(this),
        //       //   mpu6050(this),
        //       //   refSerial(this),
        //       remote(this),
        //       //   sdCard(this),
        //       uart()
        // {
        // }

        // static Drivers *drivers;

    public: // TODO: make thread safe?
        Drivers()
            : debug(this),
              //   motorHandler(this),
              //   mpu6050(this),
              //   refSerial(this),
              remote(this),
              //   sdCard(this),
              uart()
        {
        }

        debugtools::Debug debug;
        // motor::MotorHandler motorHandler;
        // communication::sensors::imu::mpu6050::MPU6050 mpu6050;
        // communication::serial::RefSerial refSerial;
        communication::serial::Remote remote;
        // debugtools::SDCard sdCard;
        pico::communication::serial::Uart uart;

        // shoud now be cloneable
        // Drivers(Drivers &other) = delete;

        // void operator=(const Drivers &) = delete;

        // static Drivers *getDrivers();
        /*static Drivers *getDrivers()
        {
            if (drivers == nullptr)
                drivers = new Drivers();
            return drivers;
        }*/
    };

} // namespace driver

#endif //  PICO_DRIVERS_H_