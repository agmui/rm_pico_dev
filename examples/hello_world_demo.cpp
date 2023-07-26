#include <iostream>
#include "pico/stdlib.h"

int main(int argc, char const *argv[])
{
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    while (1)
    {
        std::cout << "hello world" << std::endl;

        // Turn On LED
        gpio_put(25, 1); // Set pin 25 to high
        printf("LED switched on!\n");
        // Turn Off LED
        gpio_put(25, 0); // Set pin 25 to high.
        printf("LED switched off!\n");
    }
}