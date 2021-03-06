#include "pico/stdlib.h"
#include "uart.h"
#include "configuration.h"
#include "ic6502.h"

static bool s_tickState = false;

void ic6502_init()
{
	// clock pin
    gpio_init(IC6502_PHI2_PIN);
    gpio_set_dir(IC6502_PHI2_PIN, GPIO_OUT);

	// reset
    gpio_init(IC6502_RESB_PIN);
    gpio_set_dir(IC6502_RESB_PIN, GPIO_OUT);

	// bus enable
    gpio_init(IC6502_BE_PIN);
    gpio_set_dir(IC6502_BE_PIN, GPIO_OUT);

	// IRQB
    gpio_init(IC6502_IRQB_PIN);
    gpio_set_dir(IC6502_IRQB_PIN, GPIO_OUT);

	// NMIB
    gpio_init(IC6502_NMIB_PIN);
    gpio_set_dir(IC6502_NMIB_PIN, GPIO_OUT);

	// RWB - input... is driven by 6502
//    gpio_init(IC6502_RWB_PIN);
//    gpio_set_dir(IC6502_NMIB_PIN, GPIO_IN);
}

void ic6502_reset()
{
	uart_puts_ln("6502: Begin Reset");
    gpio_put(IC6502_RESB_PIN, 0);
    gpio_put(IC6502_IRQB_PIN, 1);
    gpio_put(IC6502_NMIB_PIN, 1);
	ic6502_enable_bus(true);
	for(int i=0 ; i<10 ; i++)
	{
		ic6502_tick(1000);
	}
    gpio_put(IC6502_RESB_PIN, 1);
	uart_puts_ln("6502: End Reset");
}

void ic6502_tick(uint64_t microSeconds)
{
    gpio_put(IC6502_PHI2_PIN, 0);
    if(microSeconds > 0)
        sleep_us(microSeconds/2);

    gpio_put(IC6502_PHI2_PIN, 1);
    if(microSeconds > 0)
        sleep_us(microSeconds/2);
}

void ic6502_enable_bus(bool enable)
{
    gpio_put(IC6502_BE_PIN, enable ? 1 : 0);
}

