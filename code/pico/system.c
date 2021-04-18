#include "system.h"
#include "ic6502.h"

static uint64_t tickDelayMicroSeconds;
static bool fQuit = false;

void system_main()
{
	uart_ready();
	while(!fQuit)
	{

	}
}

void system_halt()
{
	
}

void system_clock_tick()
{

}
