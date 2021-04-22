#include "system.h"
#include "ic6502.h"
#include "uart.h"

static uint64_t tickDelayMicroSeconds;
static bool fQuit = false;

void system_main()
{
	uart_ready();
	while(!fQuit)
	{
		ic6502_tick(100000);
		uart_update();
	}
}

void system_halt()
{
	
}

void system_clock_tick()
{

}
