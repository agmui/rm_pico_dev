#ifndef PICO_MOTORHANDLER_H_
#define PICO_MOTORHANDLER_H_

namespace pico
{
    class Drivers;
}

namespace motor
{

    class MotorHandler
    {
    private:
        DjiMotor[] DjiMotors;
    public:
        MotorHandler(Drivers *drivers) : drivers(drivers) {}
        ~MotorHandler();
        void addMotorToManger(DjiMotor* motor);
        void pollCanData();
        void encodeAndSendCanData();
        void removeMotorFromManager(DjiMotor* motor);
    };

}

#endif //  PICO_MOTORHANDLER_H_