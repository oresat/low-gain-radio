/*! \file    uart.h
 * \brief   UART driver for the Freescale/NXP MKW01Z128.
 *
 * \addtogroup uart
 * @{
 */
/*
 *     Original Programmed by William Harrington
 */

#ifndef _UART_H_
#define _UART_H_

#include <stdbool.h>
#include <stdint.h>

#include "v1_1.h"
#include "lgr_vector.h"
#include "core_cm0plus.h"
#include "cmsis_gcc.h"
#include "ringbuffer.h"
#include "port.h"

extern bool  		uart0_intr_flag_g;

extern uint32_t     uart_clock_input;

#define     OSR_MASK            0x1F
#define     OSRVAL              16

#define     UART_TIE_SR1_TDRE   (1 << 7)
#define     UART_RIE_SR1_RDRF   (1 << 5)

#define     UART_CR1_LOOPS      (1 << 7)
#define     UART_CR1_RSRC       (1 << 5)

#define     UART_CR2_TCIE       (1 << 6)
#define     UART_CR2_TE         (1 << 3)
#define     UART_CR2_RE         (1 << 2)

#define     UART_CR3_TXDIR      (1 << 5)


struct uart_config
{
	struct pin TX;
	struct pin RX;
	uint32_t baud;
};

void isr_uart0(void)   __attribute__((interrupt("IRQ")));
// void isr_uart0(void)   __attribute__((interrupt("IRQ")));
// void isr_uart0(void)   __attribute__((interrupt("IRQ")));

//! \todo This seems clumsy, but I don't want to expose uart*_rx_buff outside API, I think.
uint16_t num_uart0_rx_chars_avail(void);

void uart0_init_intr(const struct uart_config * config);
bool uart0_getchar_intr(char *);
bool uart0_writestr_intr(char *);
bool uart0_writechar_intr(char c);

void uart0_init_poll(volatile struct uart0 * UART, const struct uart_config * config);
void uart0_read_poll(volatile struct uart0 * UART, size_t len, uint8_t * buffer);
bool uart0_char_poll(volatile struct uart0 * UART, uint8_t * buffer);
void uart0_write_poll(volatile struct uart0 * UART, size_t len, uint8_t * buffer);

void uart12_init_poll(volatile struct uart * UART, const struct uart_config * config);
void uart12_read_poll(volatile struct uart * UART, size_t len, uint8_t * buffer);
bool uart12_char_poll(volatile struct uart * UART, uint8_t * buffer);
void uart12_write_poll(volatile struct uart * UART, size_t len, uint8_t * buffer);

#define uart_init_poll(UART, config) _Generic((UART), \
        volatile struct uart0 *: uart0_init_poll, \
        volatile struct uart *: uart12_init_poll  \
                                             )(UART, config)
#define uart_read_poll(UART, len, buffer) _Generic((UART), \
        volatile struct uart0 *: uart0_read_poll, \
        volatile struct uart *: uart12_read_poll  \
                                                  )(UART, len, buffer)
#define uart_char_poll(UART, buffer) _Generic((UART), \
        volatile struct uart0 *: uart0_char_poll, \
        volatile struct uart *: uart12_char_poll  \
                                             )(UART, buffer)

#define uart_write_poll(UART, len, buffer) _Generic((UART), \
        volatile struct uart0 *: uart0_write_poll, \
        volatile struct uart *: uart12_write_poll  \
                                                   )(UART, len, buffer)

#endif

/*! @} */
