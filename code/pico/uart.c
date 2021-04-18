#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "uart.h"
#include "configuration.h"

#define MAX_READ_BUFFER 256

static uint8_t s_inputBuffer[MAX_READ_BUFFER];
static uint16_t s_inputBufferPos = 0;

int uart_baudRate;
int uart_irq;

/*
	13 RETURN
	27 91 68 LEFT
	27 91 67 RIGHT
	27 91 65 UP
	27 91 66 DOWN
	27 91 51 DELETE
	8 BACKSPCE
	27 ESC
*/

void uart_on_rx()
{
	while(uart_is_readable(UART_ID))
	{
		uint8_t ch = uart_getc(UART_ID);
//		uart_putc(UART_ID, ch);
//		char buffer[8];
//		sprintf(buffer, "%d ", ch);
//		uart_puts(UART_ID, buffer);
	}
}

void uart_ready()
{
	uart_puts(UART_ID, "\n\r");
	uart_puts(UART_ID, "> ");
}

void uart_puts_ln(const char* szString)
{
	uart_puts(UART_ID, szString);
	uart_puts(UART_ID, "\n\r");
}
