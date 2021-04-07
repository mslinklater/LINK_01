#include "pico/stdlib.h"
#include "shifter.h"
#include "configuration.h"

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
}

void shifter_enable_bus(bool enable)
{
	gpio_put(SHIFTER_OE_PIN, enable ? 0 : 1);
}
