#include <stdio.h>
#include "usercommand.h"
#include "uart.h"
#include "system.h"
#include "ic6502.h"

void usercommand_init()
{

}

void usercommand_add(const char* szCommand)
{
	if(strcmp(szCommand, "help") == 0)
	{
		// print help
		uart_puts_ln("");
		uart_puts_ln("HELP:");
		uart_puts_ln("");
		uart_puts_ln("NO ts <x> : Tick speed in Hz.");
		uart_puts_ln("h : halt");
		uart_puts_ln("c : continue");
		uart_puts_ln("reset : reset");
		uart_puts_ln("t : single tick");
		uart_puts_ln("rb : read busses");
		uart_ready();
	}
	else if(strcmp(szCommand, "h") == 0)
	{
		system_halt();
	}
	else if(strcmp(szCommand, "c") == 0)
	{
		system_continue();
	}
	else if(strcmp(szCommand, "reset") == 0)
	{
		ic6502_reset();
	}
	else if(strcmp(szCommand, "t") == 0)
	{
		ic6502_tick(100000);
	}
	else if(strncmp(szCommand, "tr ", 3) == 0)
	{
		int count;
		sscanf(szCommand, "tr %d", &count);
		system_set_tick_rate(count);
	}
	else if(strcmp(szCommand, "rb") == 0)
	{
		uint16_t address;
		uint8_t data;
		shifter_readbus(&address, &data);
	}
}

void usercommand_registerautocomplete(const char* szString)
{

}
