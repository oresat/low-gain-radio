#include "port.h"

void set_pin_alt(const struct pin_assign list[], volatile void * module, const struct pin * pin){
	for(int i = 0; list[i].module != NULL; ++i){
		if(module != list[i].module) continue;
		if(pin->port != list[i].pin.port) continue;
		if(pin->pin != list[i].pin.pin) continue;

		pin->port->PCR[pin->pin] |= list[i].alt << 8;
		return;
	}
	//assert(0);
}
