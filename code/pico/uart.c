#include "hardware/uart.h"
#include "uart.h"
#include "configuration.h"

#define MAX_READ_BUFFER 256

static uint8_t s_inputBuffer[MAX_READ_BUFFER];
static uint16_t s_inputBufferPos = 0;

int uart_baudRate;
int uart_irq;

void uart_on_rx()
{
	while(uart_is_readable(UART_ID))
	{
		uint8_t ch = uart_getc(UART_ID);
		
	}
}
