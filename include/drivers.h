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
            : Debug(this),
              MotorHandler(this),
              MPU6050(this),
              RefSerial(this),
              Remote(this),
              SDCard(this),
              Uart()
        {
        }

    public:
        Debug::Debug debug;
        MotorHandler motorHandler;
        MPU6050 mpu6050;
        RefSerial refSerial;
        Remote remote;
        SDCard sdCard;
        Uart uart;
    };

} // namespace driver

#endif //  PICO_DRIVERS_H_