
#include <stdio.h>
#include "pico/stdlib.h"
#include <drivers.h>

int main()
{
    stdio_init_all();


    for (int i = 0; i < 3; i++)
    {
        sleep_ms(1000);
        printf("%d,", 3 - i);
        if(getchar_timeout_us(100)!=-1) break;
    }
    puts("");


    pico::Drivers *drivers = new pico::Drivers();

    std::cout << "mounting..." << std::endl;
    drivers->sdCard.init();
    drivers->sdCard.mount();
    std::cout << "sdcard mounted" << std::endl;
    while (1)
    {

        // printf("doing stuff");
        // sleep_ms(200);
        // printf(".");
        // sleep_ms(200);
        // printf(".");
        // sleep_ms(200);
        // printf(".\n");

        drivers->debug.runNextCommand();
    }
}