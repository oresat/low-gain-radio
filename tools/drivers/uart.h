/*
	UART driver for the Freescale/NXP MKW01Z128 UART module.

	Programmed by William Harrington, Theo Hill
 */
#include <stdbool.h>
#include <stdint.h>
#include "kw0x.h"
#include "port.h"

struct uart_config {
	// stuff will go here at some point
	struct pin TX;
	struct pin RX;
	uint16_t baud;
};

/* function for initializing UART */
void uart_init(volatile struct uart * UART, const struct uart_config * config);

/* function for receiving characters from FIFO buffer */
void uart_read(volatile struct uart * UART, size_t len, uint8_t * buffer);

/* function for placing characters into FIFO buffer */
void uart_write(volatile struct uart * UART, size_t len, uint8_t * buffer);
