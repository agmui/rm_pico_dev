
#include <stdio.h>
#include "pico/stdlib.h"
#include <drivers.h>


#include <string>

void pilk(pico::Drivers *drivers)
{
    char pilk[] =
        "$$$$$$$\\ $$$$$$\\ $$\\       $$\\   $$\\ \n"
        "$$  __$$\\\\_$$  _|$$ |      $$ | $$  |\n"
        "$$ |  $$ | $$ |  $$ |      $$ |$$  / \n"
        "$$$$$$$  | $$ |  $$ |      $$$$$  /  \n"
        "$$  ____/  $$ |  $$ |      $$  $$<   \n"
        "$$ |       $$ |  $$ |      $$ |\\$$\\  \n"
        "$$ |     $$$$$$\\ $$$$$$$$\\ $$ | \\$$\\ \n"
        "\\__|     \\______|\\________|\\__|  \\__|\n\n";
    puts(pilk);
    printf("setting: %d\n", drivers->debug.getSetting());
}
int main()
{
    stdio_init_all();
    sleep_ms(1000);

    for (int i = 0; i < 4; i++)
    {
        sleep_ms(1000);
        printf("%d,", 4 - i);
        if (getchar_timeout_us(100) != -1)
            break;
    }
    puts("");

    pico::Drivers *drivers = new pico::Drivers();
    // adding new cmd
    debugtools::cmd_def_t cmd = {pilk, // sample command
                                 "pilk\n"
                                 "this is a sample cmd"};
    // debugtools::CLI::command_map.insert(std::make_pair("pilk", cmd));
    debugtools::CLI::command_map["pilk"] = cmd;


    while (1)
    {
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");

        drivers->debug.runNextCommand();
    }
}