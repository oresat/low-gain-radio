/*!
 * \file    clocks.h
 * \brief   Clocks helper functions
 *
 * \addtogroup clocks
 * @{
 */

#ifndef _LGR_CLOCKS_H_
#define _LGR_CLOCKS_H_

#include "port.h"

/*
 * MCU S_ystem C_lock G_ating C_ontrol
 * Ref Section 8.2.x
 */
#define     SOPT2_PLL_DIV_2     (0b1 << 16)
#define     SOPT2_UART0SRC_PLL  (0b01 << 26)
#define     SCGC_UART0_CLK      (0b1 << 10)
#define     SCGC_UART1_CLK      (0b1 << 11)
#define     SCGC_UART2_CLK      (0b1 << 12)

#define     SCGC_SPI0_CLK       (1  <<  22)
#define     SCGC_SPI1_CLK       (1  <<  23)
#define     SCGC_SPI_CLK_OFF    (~(0b11 << 22))

#define     SCGC_PORTA_CLK      (1  <<  9)
#define     SCGC_PORTB_CLK      (1  << 10)
#define     SCGC_PORTC_CLK      (1  << 11)
#define     SCGC_PORTD_CLK      (1  << 12)
#define     SCGC_PORTE_CLK      (1  << 13)
#define     SCGC_PORTAE_CLK     (31 <<  9)

/* XCVR Clock */
#define XCVR_REF_CLK_DIVIDE_0   (0x0)
#define XCVR_REF_CLK_DIVIDE_16  (1  << 2)

/* UARTs */
void enable_uart0_clock(void);
void enable_uart1_clock(void);
void enable_uart2_clock(void);
void disable_uart0_clock(void);
void disable_uart1_clock(void);
void disable_uart2_clock(void);

/* SPI */
void enable_spi0_clock(void);
void disable_spi0_clock(void);
void enable_spi1_clock(void);
void disable_spi1_clock(void);
void disable_all_spi_clocks(void);

/* Port */
void enable_all_port_clocks(void) ;
void disable_all_port_clocks(void) ;
void enable_port_clock_x(IO_Port port) ;
void disable_port_clock_x(IO_Port port) ;

/* PLL */
void enable_pll_48(void);

#endif

/*! @} */
