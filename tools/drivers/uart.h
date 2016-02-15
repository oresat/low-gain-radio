/*
	UART driver for the Freescale/NXP MKW01Z128 UART module.

	Programmed by William Harrington, Theo Hill
 */
#include <stdbool.h>
#include <stdint.h>
#include "port.h"

#ifndef _UART_H_
#define _UART_H_
struct uart_config {
	struct pin TX;
	struct pin RX;
	uint32_t baud;
};

/* but UART0 has to be special so it has its own */
void uart0_init(volatile struct uart0 * UART, const struct uart_config * config);
void uart0_read(volatile struct uart0 * UART, size_t len, uint8_t * buffer);
void uart0_write(volatile struct uart0 * UART, size_t len, uint8_t * buffer);
void uart0_transaction(volatile struct uart0 * UART, size_t len, uint8_t * sendBuff, uint8_t * recvBuff);

/* function for initializing UART */
void uart_init(volatile struct uart * UART, const struct uart_config * config);

/* function for receiving characters from FIFO buffer */
void uart_read(volatile struct uart * UART, size_t len, uint8_t * buffer);

/* function for placing characters into FIFO buffer */
void uart_write(volatile struct uart * UART, size_t len, uint8_t * buffer);

void uart_transaction(volatile struct uart * UART, size_t len, uint8_t * sendBuff, uint8_t * recvBuff);

#endif
