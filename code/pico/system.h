#include "pico/stdlib.h"

extern void system_main();
extern void system_halt();
extern void system_continue();

extern void system_clock_tick();
extern void system_set_tick_rate(int rate);
