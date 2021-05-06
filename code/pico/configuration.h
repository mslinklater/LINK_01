#define UART_ID uart0
#define UART_BAUD_RATE 115200
#define UART_DATA_BITS 8
#define UART_STOP_BITS 1
#define UART_PARITY UART_PARITY_NONE

// serial comms
#define UART_TX_PIN 0
#define UART_RX_PIN 1

// 8-bit bus
#define IC6502_PHI2_PIN 28
#define IC6502_RESB_PIN 27

/// Bus Enable
///
/// LOW - high impedance
/// HIGH - bus enabled
#define IC6502_BE_PIN 26
#define IC6502_IRQB_PIN 22
#define IC6502_NMIB_PIN 21
#define IC6502_RWB_PIN 10

// Shifter complex
#define SHIFTER_OE_PIN 20
#define SHIFTER_S0_PIN 19
#define SHIFTER_S1_PIN 18
#define SHIFTER_IN_PIN 12
#define SHIFTER_OUT_PIN 11
#define SHIFTER_CLK_PIN 9

// 3V3 bus

#define VGA_VSYNC 17
#define VGA_HSYNC 16
#define VGA_R 15
#define VGA_G 14
#define VGA_B 13
#define UNASSIGNED_1 8
#define UNASSIGNED_2 7
#define UNASSIGNED_3 6
#define UNASSIGNED_4 5
#define UNASSIGNED_5 4
#define UNASSIGNED_6 3
#define UNASSIGNED_7 2
