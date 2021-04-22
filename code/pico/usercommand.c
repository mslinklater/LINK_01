#include "usercommand.h"
#include "uart.h"

void usercommand_init()
{

}

void usercommand_add(const char* szCommand)
{
//	uart_puts_ln(szCommand);
	if(strcmp(szCommand, "help") == 0)
	{
		// print help
		uart_puts_ln("");
		uart_puts_ln("HELP:");
		uart_puts_ln("");
		uart_puts_ln("ts <x> : Tick speed in Hz.");
		uart_ready();
	}
}

void usercommand_registerautocomplete(const char* szString)
{

}
