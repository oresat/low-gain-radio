/*!
 * \file    port.h
 * \brief   PORT helper functiosn for ports A->E
 *
 * \addtogroup ports
 * @{
 */

/*
 *     Utility for dealing with pins on associated KW0x port
 * 
 *     Programmed by William Harrington, Theo Hill
 */
#include "kw0x.h"

#ifndef _PORT_H_
#define _PORT_H_

/* alternative function number */
/* Ref:  MKW01xxRM.pdf: Table 3-3 Pin Assignments and Signal Multiplexing */
#define PIN_DISABLE (0 << 8)
#define PIN_CLEAR  (~(0b111 << 8))
#define ALT1        (1 << 8)
#define ALT2        (2 << 8)
#define ALT3        (3 << 8)
#define ALT4        (4 << 8)
#define ALT5        (5 << 8)
#define ALT6        (6 << 8)
#define ALT7        (7 << 8)

/* Pin location in port */
#define PTA0        (1 << 0)
#define PTA1        (1 << 1)
#define PTA2        (1 << 2)
#define PTA3        (1 << 3)
#define PTA4        (1 << 4)
#define PTA4        (1 << 4)
#define PTA4        (1 << 4)

#define PTB0        (1 << 0)
#define PTB1        (1 << 1)
#define PTB2	    (1 << 2)
#define PTB17       (1 << 17)

#define PTC1        (1 << 1)
#define PTC2        (1 << 2)
#define PTC3        (1 << 3)
#define PTC4        (1 << 4)
#define PTC5        (1 << 5)
#define PTC6        (1 << 6)
#define PTC7        (1 << 7)

#define PTD0        (1 << 0)
#define PTD4        (1 << 4)
#define PTD5        (1 << 5)
#define PTD6        (1 << 6)
#define PTD7        (1 << 7)

#define PTE0        (1 << 0)
#define PTE1        (1 << 1)
#define PTE2        (1 << 2)
#define PTE3        (1 << 3)
#define PTE16       (1 << 16)
#define PTE17       (1 << 17)
#define PTE18       (1 << 18)
#define PTE19       (1 << 19)
#define PTE30       (1 << 30)

#define xIRQC_Pos                   16U
#define PCR_ISF_Clr                 (~(0b1111 << xIRQC_Pos))
#define PCR_ISF_DISABLED_Msk        (0b0000U << xIRQC_Pos)
#define PCR_ISF_DMA_RISING_Msk      (0b0001U << xIRQC_Pos)
#define PCR_ISF_DMA_FALLING_Msk     (0b0010U << xIRQC_Pos)
#define PCR_ISF_DMA_EITHER_Msk      (0b0011U << xIRQC_Pos)
#define PCR_ISF_INT_LZERO_Msk       (0b1000U << xIRQC_Pos)
#define PCR_ISF_INT_RISING_Msk      (0b1001U << xIRQC_Pos)
#define PCR_ISF_INT_FALLING_Msk     (0b1010U << xIRQC_Pos)
#define PCR_ISF_INT_EITHER_Msk      (0b1011U << xIRQC_Pos)
#define PCR_ISF_INT_LONE_Msk        (0b1100U << xIRQC_Pos)

typedef enum gpio_ports {IOPORTA, IOPORTB, IOPORTC, IOPORTD, IOPORTE } IO_Port;

/* struct for pin selection */
struct pin
{
	volatile struct port * port; /* port module */
	uint8_t pin; /* pin on port module */
};

/* struct for pin assignment */
/* Ref:  MKW01xxRM.pdf: Table 3-3 Pin Assignments and Signal Multiplexing */
struct pin_assign
{
	volatile void * module;
	struct pin pin;
	uint8_t alt;
};


void set_pin_alt(const struct pin_assign list[], volatile void * module, const struct pin * pin);
void initialize_gpio(void) ;

#endif

/*! @} */
