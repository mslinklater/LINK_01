#include "busmaster.h"
#include "ic6502.h"
#include "shifter.h"

static int s_currentControl;

void busmaster_set_control(int busControl)
{
	switch(busControl)
	{
		case BUSMASTER_CONTROL_OFF:
			shifter_enable_bus(false);
			ic6502_enable_bus(false);
			break;
		case BUSMASTER_CONTROL_6502:
			shifter_enable_bus(false);
			ic6502_enable_bus(true);
			break;
		case BUSMASTER_CONTROL_SHIFTER:
			ic6502_enable_bus(false);
			shifter_enable_bus(true);
			break;
		default:
			break;
	}
	s_currentControl = busControl;
}

int busmaster_get_control()
{
	return s_currentControl;
}