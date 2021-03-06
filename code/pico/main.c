#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/irq.h"

#include "configuration.h"
#include "uart.h"
#include "ic6502.h"
#include "system.h"
#include "busmaster.h"
#include "usercommand.h"

#include "test.h"

static void initUART()
{
	// UART setup
    uart_init(UART_ID, UART_BAUD_RATE);
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
}

int main()
{
    stdio_init_all();

	initUART();
	uart_puts_ln("======================");
	uart_puts_ln("Welcome to the LINK_01");
	uart_puts_ln("======================");
	uart_puts_ln("");

	sleep_ms(1000);	// just in case we power up first, let the rest of the board catch up...

	// initialise all the things
	ic6502_init();
	shifter_init();

	busmaster_set_control(BUSMASTER_CONTROL_OFF);

	ic6502_reset();

	usercommand_init();

	system_main();

	uart_puts_ln("Exiting main() - this should never happen !");
}