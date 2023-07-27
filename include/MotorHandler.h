#ifndef PICO_MOTORHANDLER_H_
#define PICO_MOTORHANDLER_H_

#include "DjiMotor.h"

namespace pico
{
    class Drivers;
}

namespace pico::motor
{

    class MotorHandler
    {
    private:
        Drivers *drivers;
        DjiMotor *DjiMotors[8] = {0};

    public:
        MotorHandler(Drivers *drivers) : drivers(drivers) {}
        ~MotorHandler();
        void addMotorToManger(DjiMotor *motor);
        void pollCanData();
        void encodeAndSendCanData();
        void removeMotorFromManager(DjiMotor *motor);
    };

}

#endif //  PICO_MOTORHANDLER_H_