#include "system.h"
#include "ic6502.h"
#include "uart.h"

static uint64_t tickDelayMicroSeconds;
static bool fQuit = false;

static uint64_t tickDelay = 100000;
static uint64_t oldTickDelay = 0;

void system_main()
{
	uart_ready();
	while(!fQuit)
	{
		if(tickDelay > 0)
		{
			ic6502_tick(tickDelay);
		}
		uart_update();
	}
}

void system_halt()
{
	if(tickDelay > 0)
	{
		oldTickDelay = tickDelay;
		tickDelay = 0;
	}
}

void system_continue()
{
	tickDelay = oldTickDelay;
}

void system_clock_tick()
{

}

void system_set_tick_rate(int rate)
{
	tickDelay = 1000000 / rate;

	int bp=0;
	bp++;
}
