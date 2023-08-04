#include <iostream>
#include <drivers.h>
#include <Debug.h>
#include "pico/stdlib.h"
#include "rm_pico_dev/src/algorithms/smooth_pid.hpp"

int main(int argc, char const *argv[])
{

    for (int i = 0; i < 6; i++)
    {
        sleep_ms(1000);
        printf("%d,", 8 - i);
    }

    pico::Drivers *drivers = new pico::Drivers();
    // pico::Drivers *drivers = pico::Drivers::getDrivers();

    stdio_init_all();
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    pico::motor::DjiMotor motor_one = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR1, pico::can::PioNum::CAN_BUS0, true, "ID1", 0, 0);
    static pico::algorithms::SmoothPidConfig pid_conf_dt = {20, 0, 0, 0, 8000, 1, 0, 1, 0, 0, 0};
    pico::algorithms::SmoothPid pidController = pico::algorithms::SmoothPid(pid_conf_dt);

    drivers->can.initialize();
    motor_one.initialize();

    while (1)
    {
        std::cout << "=============" << std::endl;
        sleep_ms(550);
        // Turn On LED
        gpio_put(25, 1); // Set pin 25 to high
        sleep_ms(250);
        printf("LED switched on!\n");
        // Turn Off LED
        gpio_put(25, 0); // Set pin 25 to high.
        sleep_ms(250);
        printf("LED switched off!\n");

        std::cout << "poll" << std::endl;
        drivers->motorHandler.pollCanData();
        std::cout << "pid" << std::endl;
        pidController.runControllerDerivateError(0 - motor_one.getShaftRPM(), 1);
        std::cout << "set output" << std::endl;
        motor_one.setDesiredOutput(static_cast<int32_t>(pidController.getOutput()));
        std::cout << "send data" << std::endl;
        drivers->motorHandler.encodeAndSendCanData(); // Processes these motor speed changes into can signal
    }
}