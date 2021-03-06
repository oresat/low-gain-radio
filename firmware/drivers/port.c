/*!
 * \file    port.c
 * \brief   PORT API
 *
 * \defgroup ports
 * @{
 */

/*
 * \file port.c
 */

#include <assert.h>
#include "port.h"
#include "clocks.h"

/* Use with a pin assign structure to manage multiplexed pins
 * Ref: Table 3-3. MKW01 Pin Assignments and Signal Multiplexing
 */
void set_pin_alt(const struct pin_assign list[], volatile void * module, const struct pin * pin)
{
	for(int i = 0; list[i].module != NULL; ++i)
	{
		if(module != list[i].module)
		{
			continue;
		}
		if(pin->port != list[i].pin.port)
		{
			continue;
		}
		if(pin->pin != list[i].pin.pin)
		{
			continue;
		}
		pin->port->PCR[pin->pin] &= PIN_CLEAR;
		pin->port->PCR[pin->pin] |= list[i].alt << 8;
		return;
	}
	assert(0);
}

/* Input pullups as default for low power?
 *    At reset - pullup by default (generally)
 *    At reset - pullup not enabled (generally)
 *
 * PTA0 and PTA2 are special cases for PE and PS
 * PTA0 PS=0 (pulldown), PE = 1   (default function is SWD Clk)
 * PTA2 PS=1 (pullup)  , PE = 1
 * See table 3-2 for PE and PS bits at reset
 */
/* \warning Not safe to assume the POR state of pins, this can be called anytime
   e.g. Software exception handling may call this. Just sayin. */
/* \todo Tue 12 July 2016 12:50:31 (PDT) More signals need to be reviewed for initialization */
void initialize_gpio(void)
{
	/* port A pins */
	PORTA.PCR[1] &= PIN_CLEAR;
	PORTA.PCR[1] |= ALT2;           // UART0_rx, set as ALT1 for now
	PORTA.PCR[2] &= PIN_CLEAR;
	PORTA.PCR[2] |= ALT2;           // UART0_tx, set as ALT1 for now
	PORTA.PCR[1] |= 0b11;           // PE && PS, pullup enabled
	PORTA.PCR[2] |= 0b11;           // PE && PS, pullup enabled
	PORTA.PCR[1] &= PCR_ISF_Clr;    // no interrupt
	PORTA.PCR[2] &= PCR_ISF_Clr;    // no interrupt

	/* port B pins */
	PORTB.PCR[0] |= ALT1;
	PORTB.PCR[1] |= ALT1;
	PORTB.PCR[0] &= PCR_ISF_Clr;    // no interrupt
	PORTB.PCR[1] &= PCR_ISF_Clr;    // no interrupt

	/* port C pins */
	PORTC.PCR[1] |= ALT1;
	PORTC.PCR[2] |= ALT1;
	PORTC.PCR[3] |= ALT1;
	PORTC.PCR[4] |= ALT1;
	PORTC.PCR[1] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[2] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[3] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[4] &= PCR_ISF_Clr;    // no interrupt


	/* PORT D pins */
	// Port D 4 should be high
	// turns off U3, spi flash chip.
	// #CS

	/* port E pins */
	PORTE.PCR[2]  |= ALT1;
	PORTE.PCR[2]  &= PCR_ISF_Clr;    // no interrupt
	PORTE.PCR[30] |= ALT1;
	PORTE.PCR[30] &= PCR_ISF_Clr;

	/* set data direction as output */
	/* PA_EN & LNA_EN */
	GPIOB.PDDR   |= PTB1 | PTB0;

	/* Turn off the Amplifiers */
	GPIOB.PCOR   =  PTB1 | PTB0;

	/* LEDs 5, 6, 7, 8
	 * disable pulls and configure as pulldown
	 */
	PORTC.PCR[1] &= ~(0b11);
	PORTC.PCR[2] &= ~(0b11);
	PORTC.PCR[3] &= ~(0b11);
	PORTC.PCR[4] &= ~(0b11);
	GPIOC.PDDR   |= PTC4 | PTC3 | PTC2 | PTC1;

	/* Turn off the LEDs */
	GPIOC.PCOR   =  PTC4 | PTC3 | PTC2 | PTC1;

	/* \todo Thu 21 July 2016 17:15:42 (PDT): PTE2 is DIO0 and shouldn't have been connected to xvcr-reset! */

	/* Transceiver  reset  is ACTIVE HIGH for min 100µs */
	/* Ref: 4.3.2.2 Transceiver Hardware Reset in Ref manual */
	/* enable pulls (PE=1)... */
	PORTE.PCR[2] |= 0b10;
	/* ... and set pulldown (PS=0)  */
	PORTE.PCR[2] &= ~(0b1);
	GPIOE.PDDR   |= PTE2;

	/* enable pulls (PE=1)... */
	PORTE.PCR[30] |= 0b10;
	/* ... and set pulldown (PS=0)  */
	PORTE.PCR[30] &= ~(0b1);
	GPIOE.PDDR    |= PTE30; // configure as output


	/* Initialize to zero */
	GPIOE.PCOR =  PTE2;
	GPIOE.PCOR =  PTE30;

	return;
}

/*! @} */

