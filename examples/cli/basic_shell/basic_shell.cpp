#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
// #include "pico/stdio.h"
#include "pico/stdio_usb.h"

int main()
{
    stdio_init_all();
    while (!stdio_usb_connected())
        ; // wait until USB connection
    char data[10]; // reading cmd buffer
    int chars_rxed = 0;
    while (1)
    {
        // emulates stuff happing
        printf("doing stuff");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".");
        sleep_ms(200);
        printf(".\n");

        int ch = PICO_ERROR_TIMEOUT;
        do
        {
            // waits and checks for char
            // if no char continue
            ch = getchar_timeout_us(0);// returns PICO_ERROR_TIMEOUT if no char

            // saves char to buffer
            data[chars_rxed] = (char)ch;
            chars_rxed++;
        } while (ch != PICO_ERROR_TIMEOUT);// loop till char no more chars to read 

        data[chars_rxed - 1] = '\0';// add null char
        if (chars_rxed > 1)
            printf("%s\n", data);// print cmd
        chars_rxed = 0; //reset
    }
    return 0;
}
