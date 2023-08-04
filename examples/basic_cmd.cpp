#include <iostream>
#include <drivers.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include <Command.h>


int main()
{
    stdio_init_all();

    for (int i = 0; i < 5; i++)
    {
        sleep_ms(1000);
        printf("%d,", 5 - i);
        if(getchar_timeout_us(100)!=-1) break;
    }

    pico::Drivers *drivers = new pico::Drivers();
    // pico::Drivers *drivers = pico::Drivers::getDrivers();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);


    while (1)
    {
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");


        // Turn On LED
        gpio_put(25, 1); // Set pin 25 to high
        sleep_ms(250);
        // printf("LED switched on!\n");
        // Turn Off LED
        gpio_put(25, 0); // Set pin 25 to high.
        sleep_ms(250);
        // printf("LED switched off!\n");

        drivers->debug.runNextCommand();
    }
}
