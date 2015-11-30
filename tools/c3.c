#include "kw0x.h"

int main(void) {
	int i;
	while(1) {
		PORTB.GPCLR = 0xFFFFFFFF;
		for(i = 0; i < 1000000; ++i);
		PORTB.GPCLR = 0xFFFF0000;
		for(i = 0; i < 1000000; ++i);
	}
	return 0;
}
