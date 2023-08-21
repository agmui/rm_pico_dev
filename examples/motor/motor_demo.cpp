#include <iostream>
#include <drivers.h>
#include <Debug.h>
#include "pico/stdlib.h"
#include "rm_pico_dev/src/algorithms/smooth_pid.hpp"

int main(int argc, char const *argv[])
{

    //sleep for a bit to let serial monitor connect
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

    //init motor object
    pico::motor::DjiMotor motor_one = pico::motor::DjiMotor(drivers, pico::motor::MotorId::MOTOR1, pico::can::PioNum::CAN_BUS0, true, "ID1", 0, 0);

    // init PID algorithm
    // PID explained: https://www.youtube.com/watch?v=wkfEZmsQqiA
    static pico::algorithms::SmoothPidConfig pid_conf_dt = {20, 0, 0, 0, 8000, 1, 0, 1, 0, 0, 0};
    pico::algorithms::SmoothPid pidController = pico::algorithms::SmoothPid(pid_conf_dt);

    // init CanBus to send motor information
    drivers->can.initialize();

    //init motor
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
        // checks to see if a msg is waiting
        drivers->motorHandler.pollCanData(); 

        std::cout << "pid" << std::endl;
        // do the pid algorithm 
        // PID explained: https://www.youtube.com/watch?v=wkfEZmsQqiA
        pidController.runControllerDerivateError(0 - motor_one.getShaftRPM(), 1);

        std::cout << "set output" << std::endl;
        // set up msg so its ready to be sent
        motor_one.setDesiredOutput(static_cast<int32_t>(pidController.getOutput()));

        std::cout << "send data" << std::endl;
        // send all msg to the motors
        drivers->motorHandler.encodeAndSendCanData();
    }
}