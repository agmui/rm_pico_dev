
#include <stdio.h>
#include "pico/stdlib.h"
#include <drivers.h>

int main()
{
    stdio_init_all();


    // lets Serial Monitor time to connect
    for (int i = 0; i < 3; i++)
    {
        sleep_ms(1000);
        printf("%d,", 3 - i);
        if(getchar_timeout_us(100)!=-1) break;
    }
    puts("");


    pico::Drivers *drivers = new pico::Drivers();

    std::cout << "mounting..." << std::endl;
    drivers->sdCard.init();// init sd card obj
    drivers->sdCard.mount();// mount sd card
    std::cout << "sdcard mounted" << std::endl;
    while (1)
    {

        // emulates stuff running on pico
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");

        //waits for cmd. If no cmd goes on
        drivers->debug.runNextCommand();
    }
}