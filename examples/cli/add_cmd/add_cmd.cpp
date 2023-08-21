
#include <stdio.h>
#include "pico/stdlib.h"
// #include <drivers.h>
#include <string>

/*
// function to run when pilk is called
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
    puts(pilk);// basically printf()

    // drivers is passed in so you can print out whatever you want
    printf("setting: %d\n", drivers->debug.getSetting());
}*/
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
    puts("");// basically printf()
    while (1)
    {
        printf("hi");
        tight_loop_contents();
    }
    
/*
    pico::Drivers *drivers = new pico::Drivers();
    // setting up new cmd
    debugtools::cmd_def_t cmd = {pilk, 
                                 "pilk\n"
                                 "this is a sample cmd"};
    // debugtools::CLI::command_map.insert(std::make_pair("pilk", cmd));

    // adding new cmd to command_map
    debugtools::CLI::command_map["pilk"] = cmd;


    while (1)
    {
        // emulate stuff happening
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");

        // type in pilk to see output
        drivers->debug.runNextCommand();
    }
*/
}