#include "hardware/uart.h"
#include "uart.h"
#include "configuration.h"

int uart_baudRate;
int uart_irq;

void uart_on_rx()
{
	while(uart_is_readable(UART_ID))
	{
		uint8_t ch = uart_getc(UART_ID);
	}
}
