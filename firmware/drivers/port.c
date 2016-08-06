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

/* Use with a pin assign structure to manage multiplexed pins */
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
// ***************port A pins *******************
	PORTA.PCR[1] &= PIN_CLEAR;
	PORTA.PCR[1] |= ALT2;           // UART0_rx, set as ALT1 for now
	PORTA.PCR[2] &= PIN_CLEAR;
	PORTA.PCR[2] |= ALT2;           // UART0_tx, set as ALT1 for now
	PORTA.PCR[1] |= 0b11;           // PE && PS, pullup enabled
	PORTA.PCR[2] |= 0b11;           // PE && PS, pullup enabled
	PORTA.PCR[1] &= PCR_ISF_Clr;    // no interrupt
	PORTA.PCR[2] &= PCR_ISF_Clr;    // no interrupt
// **********************************************

// ***************port B pins *******************
	PORTB.PCR[0] |= ALT1;
	PORTB.PCR[1] |= ALT1;
	PORTB.PCR[2] |= ALT1;
	PORTB.PCR[17] |= ALT1;
	PORTB.PCR[0] &= PCR_ISF_Clr;    // no interrupt
	PORTB.PCR[1] &= PCR_ISF_Clr;    // no interrupt
	PORTB.PCR[2] &= PCR_ISF_Clr;    // no interrupt
	PORTB.PCR[17] &= PCR_ISF_Clr;    // no interrupt

	/* set data direction as output */
	GPIOB.PDDR   |= PTB17 | PTB2 | PTB1;

	/* pull pins high */
	GPIOB.PTOR   =  PTB17 | PTB2 | PTB1;
// **********************************************

// ***************port C pins *******************
	PORTC.PCR[1] |= ALT1;
	PORTC.PCR[2] |= ALT1;
	PORTC.PCR[3] |= ALT1;
	PORTC.PCR[4] |= ALT1;
	PORTC.PCR[5] |= ALT1;
	PORTC.PCR[6] |= ALT1;
	PORTC.PCR[7] |= ALT1;
	PORTC.PCR[1] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[2] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[3] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[4] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[5] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[6] &= PCR_ISF_Clr;    // no interrupt
	PORTC.PCR[7] &= PCR_ISF_Clr;    // no interrupt
	/* LEDs 5, 6, 7, 8
	 * disable pulls and configure as pulldown
	 */
	//PORTC.PCR[1] &= ~(0b11);
	//PORTC.PCR[2] &= ~(0b11);
	//PORTC.PCR[3] &= ~(0b11);
	//PORTC.PCR[4] &= ~(0b11);
	//GPIOC.PDDR   |= PTC4 | PTC3 | PTC2 | PTC1;

	/* Turn off the LEDs */
	//GPIOC.PCOR   =  PTC4 | PTC3 | PTC2 | PTC1;
// **********************************************

// ***************port D pins *******************
	PORTD.PCR[0] |= ALT1;
	PORTD.PCR[4] |= ALT1;
	PORTD.PCR[5] |= ALT1;
	PORTD.PCR[6] |= ALT1;
	PORTD.PCR[7] |= ALT1;

	PORTD.PCR[0] |= 0b11;       // Enable pullup

	PORTD.PCR[0] &= PCR_ISF_Clr;    // no interrupt
	PORTD.PCR[4] &= PCR_ISF_Clr;    // no interrupt
	PORTD.PCR[5] &= PCR_ISF_Clr;    // no interrupt
	PORTD.PCR[6] &= PCR_ISF_Clr;    // no interrupt
	PORTD.PCR[7] &= PCR_ISF_Clr;    // no interrupt

	GPIOD.PDDR   |= PTD0;       // Set PTD0 payload direction to output
	GPIOD.PTOR   =  PTD0;       // Set the output signal to high

// **********************************************

// ***************port E pins *******************
	PORTE.PCR[2] |= ALT1;
	PORTE.PCR[3] |= ALT1;
	PORTE.PCR[2] &= PCR_ISF_Clr;    // no interrupt

	/* Transceiver  reset  is ACTIVE HIGH for min 100µs */
	/* Ref: 4.3.2.2 Transceiver Hardware Reset in Ref manual */
	/* enable pulls (PE=1)... */
	PORTE.PCR[2] |= 0b10;
	/* ... and set pulldown (PS=0)  */
	PORTE.PCR[2] &= ~(0b1);
	//GPIOE.PDDR |= PTE2;
	GPIOE.PDDR   &= ~(PTE2 | PTE3); // set to input

	/* Initialize to zero */
	//GPIOE.PCOR =  PTE2;
// **********************************************

	return;
}

/*! @} */

