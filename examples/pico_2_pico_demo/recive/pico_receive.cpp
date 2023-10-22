#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
extern "C"
{
#include "rm_pico_dev/lib/can2040/src/can2040.h"
}
#include "RP2040.h"

typedef struct can2040_msg CANMsg;
static struct can2040 cbus;

static void
can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    if (notify == CAN2040_NOTIFY_RX)
    {
        printf("msg read: ");
        printf("%s\n", msg->data);
    }
}

static void
PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

void canbus_setup(void)
{
    uint32_t pio_num = 0;
    uint32_t sys_clock = 125000000, bitrate = 1000000;
    uint32_t gpio_rx = 4, gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIOx_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

int main()
{
    stdio_init_all();
    canbus_setup();

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        printf("waiting...\n");

        // printf("LED ON!\n");
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        // printf("LED OFF!\n");
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        // sleep_ms(1000);
    }

    return 0;
}
