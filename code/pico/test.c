#include "pico/stdlib.h"
#include "test.h"
#include "configuration.h"
#include "ic6502.h"
#include "shifter.h"
#include "busmaster.h"

void do6502Test(int iter)
{
    while (iter-- > 0) 
	{
		for(int i=0 ; i<20 ; i++)
		{
			ic6502_tick();
	        sleep_ms(10);
		}
		for(int i=0 ; i<20 ; i++)
		{
			ic6502_tick();
	        sleep_ms(10);
		}
	}
}

void doShifterTest(int iter)
{
	shifter_init();

	while(true)
	{
		gpio_put(SHIFTER_IN_PIN, 1);
		for(int i=0 ; i<8 ; i++)
		{
			ic6502_tick();
	        sleep_ms(10);
			ic6502_tick();
	        sleep_ms(10);
		}
		gpio_put(SHIFTER_IN_PIN, 0);
		for(int i=0 ; i<8 ; i++)
		{
			ic6502_tick();
	        sleep_ms(10);
			ic6502_tick();
	        sleep_ms(10);
		}
	}
}

void runTest()
{
	busmaster_set_control(BUSMASTER_CONTROL_OFF);
	sleep_ms(1000);
	busmaster_set_control(BUSMASTER_CONTROL_SHIFTER);
	sleep_ms(1000);
	busmaster_set_control(BUSMASTER_CONTROL_6502);
	sleep_ms(1000);

	busmaster_set_control(BUSMASTER_CONTROL_6502);
	do6502Test(1);
	busmaster_set_control(BUSMASTER_CONTROL_SHIFTER);
	doShifterTest(10);
}
