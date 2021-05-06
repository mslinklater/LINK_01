#include "pico/stdlib.h"

/*
	Need the shifter specs in here
*/

extern void shifter_init();
extern void shifter_enable_bus(bool enable);

extern void shifter_read(uint16_t *pAddress, uint8_t *pData);
