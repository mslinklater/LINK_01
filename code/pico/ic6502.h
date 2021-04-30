#include "pico/stdlib.h"

extern void ic6502_init();
extern void ic6502_reset();

extern void ic6502_enable_bus(bool enable);

// Ideally only call this from system.c
extern void ic6502_tick(uint64_t microSeconds);

