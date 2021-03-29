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
}

void ic6502_reset()
{
	uart_puts(UART_ID, "Reset\n");
    gpio_put(IC6502_RESB_PIN, 0);
	ic6502_enable_busses();
	for(int i=0 ; i<10 ; i++)
	{
		ic6502_tick();
		sleep_ms(1);
	}
    gpio_put(IC6502_RESB_PIN, 1);
}

void ic6502_tick()
{
    gpio_put(IC6502_PHI2_PIN, s_tickState ? 1 : 0);
	s_tickState = !s_tickState;
}

void ic6502_enable_busses()
{
    gpio_put(IC6502_BE_PIN, 1);
}

void ic6502_disable_busses()
{
    gpio_put(IC6502_BE_PIN, 0);
}
