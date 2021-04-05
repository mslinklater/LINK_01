#include "pico/stdlib.h"

extern void ic6502_init();
extern void ic6502_reset();
extern void ic6502_tick();
extern void ic6502_enable_bus(bool enable);
