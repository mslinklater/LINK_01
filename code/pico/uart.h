#include "hardware/uart.h"

extern int uart_baudRate;
extern int uart_irq;

extern void uart_on_rx();
extern void uart_puts_ln(const char* szString);
extern void uart_ready();
extern void uart_update();
