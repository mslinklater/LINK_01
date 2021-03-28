#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "configuration.h"
#include "uart.h"

int main()
{
    stdio_init_all();

	// UART setup

    uart_init(UART_ID, 2400);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);    

	uart_baudRate = uart_set_baudrate(UART_ID, UART_BAUD_RATE);
	uart_set_hw_flow(UART_ID, false, false);
	uart_set_format(UART_ID, UART_DATA_BITS, UART_STOP_BITS, UART_PARITY);
	uart_set_fifo_enabled(UART_ID, false);	// TODO: probably want this on soon

	if(UART_ID == uart0)
	{
		uart_irq = UART0_IRQ;
	}
	else
	{
		uart_irq = UART1_IRQ;
	}

	irq_set_exclusive_handler(uart_irq, uart_on_rx);
	irq_set_enabled(uart_irq, true);
	uart_set_irq_enables(UART_ID, true, false);

	// exit
	uart_puts(UART_ID, "Quit\n");
	while(true)
	{
	}
}