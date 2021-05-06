#include "pico/stdlib.h"

extern void system_main();
extern void system_halt();
extern void system_continue();

extern void system_clock_tick();
extern void system_set_tick_rate(int rate);

extern uint8_t system_read_memory(uint16_t address);
extern void system_write_memory(uint16_t address, uint8_t data);
