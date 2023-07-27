#include <stdio.h>
#include <iostream>

#include "pico/stdlib.h"

#include "drivers.h"

// #include "can2040.h"

// #include "f_util.h"
// #include "ff.h"
// #include "pico/stdlib.h"
// #include "rtc.h"

// namespace driver
// {
//     void hi()
//     {
//         stdio_init_all();

//         gpio_init(25);
//         gpio_set_dir(25, GPIO_OUT);

//         while (1)
//         {
//             std::cout << "hello world" << std::endl;

//             // Turn On LED
//             gpio_put(25, 1); // Set pin 25 to high
//             printf("LED switched on!\n");
//             sleep_ms(250);
//             // Turn Off LED
//             gpio_put(25, 0); // Set pin 25 to high.
//             printf("LED switched off!\n");
//             sleep_ms(250);
//         }
//     }
// }