#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "uart.h"
#include "configuration.h"
#include "usercommand.h"

#define MAX_READ_BUFFER 256

// TODO - Need a history buffer here too.
static uint8_t s_inputBuffer[MAX_READ_BUFFER];
static uint16_t s_inputBufferPos = 0;
static bool s_inputBufferReady = false;

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
	static uint8_t keyCodeCache[3];
	static int iKeyCodeCache = 0;

	// check for command ready to be submitted...
	if(s_inputBufferReady)
		return;

	while(uart_is_readable(UART_ID))
	{
		keyCodeCache[iKeyCodeCache++] = uart_getc(UART_ID);
//		uart_putc(UART_ID, ch);
//		char buffer[8];
//		sprintf(buffer, "%d ", keyCodeCache[iKeyCodeCache-1]);
//		uart_puts(UART_ID, buffer);
	}
	// key has been read - filter out special cases

	switch(iKeyCodeCache)
	{
		case 1:
			if(keyCodeCache[0] == 27)	// esc
			{

			}
			else if(keyCodeCache[0] == 13)
			{
				// RETURN
				// terminate the current command
				s_inputBuffer[s_inputBufferPos] = 0;
				// process the command
				s_inputBufferReady = true;
				uart_ready();
				iKeyCodeCache = 0;
			}
			else if(keyCodeCache[0] == 8)
			{
				// BACKSPACE
				uart_putc(UART_ID, 0x08);
				uart_putc(UART_ID, ' ');
				uart_putc(UART_ID, 0x08);
				iKeyCodeCache = 0;
			}
			else
			{
				// normal characters
				if(s_inputBufferPos < MAX_READ_BUFFER-1)
				{
					s_inputBuffer[s_inputBufferPos++] = keyCodeCache[0];
					uart_putc(UART_ID, keyCodeCache[0]);
					iKeyCodeCache = 0;
				}
			}
			break;
		case 2:
			break;
		case 3:
			if((keyCodeCache[0] == 27) && (keyCodeCache[1] == 91))
			{
				// special
				if(keyCodeCache[2] == 68)
				{
					// LEFT
					uart_puts(UART_ID, "[LEFT]");
				}
				else if(keyCodeCache[2] == 67)
				{
					// RIGHT
					uart_puts(UART_ID, "[RIGHT]");
				}
				else if(keyCodeCache[2] == 65)
				{
					// UP
					uart_puts(UART_ID, "[UP]");
				}
				else if(keyCodeCache[2] == 66)
				{
					// DOWN
					uart_puts(UART_ID, "[DOWN]");
				}
				else if(keyCodeCache[2] == 51)
				{
					// DELETE
					uart_puts(UART_ID, "[DELETE]");
				}
				iKeyCodeCache = 0;
			}
			break;
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

void uart_update()
{
	if(s_inputBufferReady)
	{
		// submit command
		usercommand_add(s_inputBuffer);
		s_inputBufferPos = 0;
		s_inputBufferReady = false;
	}
}