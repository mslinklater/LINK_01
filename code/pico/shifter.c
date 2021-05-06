#include <stdio.h>
#include "pico/stdlib.h"
#include "shifter.h"
#include "configuration.h"
#include "busmaster.h"
#include "ic6502.h"
#include "uart.h"

void shifter_init()
{
	// OE
    gpio_init(SHIFTER_OE_PIN);
    gpio_set_dir(SHIFTER_OE_PIN, GPIO_OUT);
	gpio_put(SHIFTER_OE_PIN, 0);

	// S0
	gpio_init(SHIFTER_S0_PIN);
	gpio_set_dir(SHIFTER_S0_PIN, GPIO_OUT);
	gpio_put(SHIFTER_S0_PIN, 0);

	// S1
	gpio_init(SHIFTER_S1_PIN);
	gpio_set_dir(SHIFTER_S1_PIN, GPIO_OUT);
	gpio_put(SHIFTER_S1_PIN, 1);

	// IN
	gpio_init(SHIFTER_IN_PIN);
	gpio_set_dir(SHIFTER_IN_PIN, GPIO_OUT);
	gpio_put(SHIFTER_IN_PIN, 1);

	// OUT
	gpio_init(SHIFTER_OUT_PIN);
	gpio_set_dir(SHIFTER_OUT_PIN, GPIO_IN);

	// CLK
	gpio_init(SHIFTER_CLK_PIN);
	gpio_set_dir(SHIFTER_CLK_PIN, GPIO_OUT);
	gpio_put(SHIFTER_CLK_PIN, 1);
}

void shifter_enable_bus(bool enable)
{
	gpio_put(SHIFTER_OE_PIN, enable ? 0 : 1);
}

void shifter_tick()
{
	gpio_put(SHIFTER_CLK_PIN, 0);
	gpio_put(SHIFTER_CLK_PIN, 1);
}

void shifter_readbus(uint16_t *pAddress, uint8_t *pData)
{
	*pAddress = 0;
	*pData = 0;

	// load

	gpio_put(SHIFTER_S0_PIN, 1);
	gpio_put(SHIFTER_S1_PIN, 1);
	gpio_put(SHIFTER_OE_PIN, 0);
	shifter_tick();

	// hold
	gpio_put(SHIFTER_S0_PIN, 0);
	gpio_put(SHIFTER_S1_PIN, 0);
	ic6502_enable_bus(false);

	// store bus master and set to shifter

//	int oldBus = busmaster_get_control();
//	busmaster_set_control(BUSMASTER_CONTROL_SHIFTER);

	// shift out

	uint32_t val = 0;

	// set left shift
	gpio_put(SHIFTER_S0_PIN, 0);
	gpio_put(SHIFTER_S1_PIN, 1);

	for(int i=0 ; i<24 ; i++)
	{
		val <<= 1;
		val += (gpio_get(SHIFTER_IN_PIN) == 0 ? 0 : 1);
		shifter_tick();
	}

	// restore bus master
//	busmaster_set_control(oldBus);

	gpio_put(SHIFTER_OE_PIN, 1);
	ic6502_enable_bus(true);

	char buffer[32];
	sprintf(buffer, "%08x", val);
	uart_puts_ln(buffer);
}

