#include <iostream>
#include "pico/stdlib.h" // the pico-sdk lib
#include <stdio.h>


int main(int argc, char const *argv[])
{
    stdio_init_all();// allows printing to terminal

    gpio_init(25);// init pin 25(the led)
    gpio_set_dir(25, GPIO_OUT);//set pin 25 to output

    while (1)
    {
        //print hello world
        std::cout << "hello world" << std::endl;

        // Turn On LED
        gpio_put(25, 1); // Set pin 25 to high
        sleep_ms(250);//wait for 250 ms
        printf("LED switched on!\n");// print 
        // Turn Off LED
        gpio_put(25, 0); // Set pin 25 to high.
        sleep_ms(250);
        printf("LED switched off!\n");

    }
}