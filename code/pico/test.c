#include "pico/stdlib.h"
#include "test.h"
#include "configuration.h"
#include "ic6502.h"

void runTest()
{
    while (true) {
//		ic6502_enable_busses();
		for(int i=0 ; i<20 ; i++)
		{
			ic6502_tick();
	        sleep_ms(250);
		}
//		ic6502_disable_busses();
		for(int i=0 ; i<20 ; i++)
		{
			ic6502_tick();
	        sleep_ms(250);
		}
	}
}
