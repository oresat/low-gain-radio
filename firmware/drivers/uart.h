/*
	UART driver for the Freescale/NXP MKW01Z128.

	Programmed by William Harrington
 */
#ifndef _UART_H_
#define _UART_H_

#include <stdbool.h>
#include <stdint.h>
#include "port.h"

struct uart_config {
	struct pin TX;
	struct pin RX;
	uint32_t baud;
};

void uart0_init(volatile struct uart0 * UART, const struct uart_config * config);
void uart0_read(volatile struct uart0 * UART, size_t len, uint8_t * buffer);
void uart0_write(volatile struct uart0 * UART, size_t len, uint8_t * buffer);

void uart12_init(volatile struct uart * UART, const struct uart_config * config);
void uart12_read(volatile struct uart * UART, size_t len, uint8_t * buffer);
void uart12_write(volatile struct uart * UART, size_t len, uint8_t * buffer);

#define uart_init(UART, config) _Generic((UART), \
	volatile struct uart0 *: uart0_init, \
	volatile struct uart *: uart12_init  \
	)(UART, config)
#define uart_read(UART, len, buffer) _Generic((UART), \
	volatile struct uart0 *: uart0_read, \
	volatile struct uart *: uart12_read  \
	)(UART, len, buffer)
#define uart_write(UART, len, buffer) _Generic((UART), \
	volatile struct uart0 *: uart0_write, \
	volatile struct uart *: uart12_write  \
	)(UART, len, buffer)
//util function that shouldn't be here, but until we get a util module...
void toHex(uint8_t * dest, uint8_t byte);
#endif
