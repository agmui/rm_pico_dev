#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

int main()
{
    stdio_init_all();
    while (!stdio_usb_connected())
        ; // wait until USB connection
    char data[10];
    int chars_rxed = 0;
    while (1)
    {
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
            ch = getchar_timeout_us(0);
            data[chars_rxed] = (char)ch;
            chars_rxed++;
        } while (ch != PICO_ERROR_TIMEOUT);
        data[chars_rxed-1] = '\0';
        if (chars_rxed>1)
            printf("%s\n", data);
        chars_rxed = 0;

    }
    return 0;
}
