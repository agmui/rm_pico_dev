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
        Drivers()
            : debug(this),
              motorHandler(this),
              mpu6050(this),
              refSerial(this),
              remote(this),
              sdCard(this),
              uart()
        {
        }

    public:
        debugtools::Debug debug;
        motor::MotorHandler motorHandler;
        communication::sensors::imu::mpu6050::MPU6050 mpu6050;
        communication::serial::RefSerial refSerial;
        communication::serial::Remote remote;
        debugtools::SDCard sdCard;
        pico::communication::serial::Uart uart;
    };

} // namespace driver

#endif //  PICO_DRIVERS_H_