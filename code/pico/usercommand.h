#include "pico/stdlib.h"

extern void usercommand_init();
extern void usercommand_registerautocomplete(const char* szString);
extern void usercommand_add(const char* szCommand);
