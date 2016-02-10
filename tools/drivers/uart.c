#include "uart.h"

void uart_init(volatile struct uart * UART, const struct uart_config * config){
	uint32_t busClock = 24000000;
	uint32_t baudRate = 115200;
	uint32_t divisor = busClock/(16*baudRate);
	UART.BDH = (divisor & 0x1F00) >> 8;
	UART.BDL = (divisor & 0xFF);
	UART.C1 = 0x0;
	UART.C2 = 0xC;
	UART.C3 = 0x0;
	UART.C4 = 0x0;
}


