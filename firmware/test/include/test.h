/* \file test.h
 */

#ifndef _TEST_H
	#define _TEST_H

	void NMIVector(void)  __attribute__((interrupt("IRQ")));
	void isr_porta(void)  __attribute__((interrupt("IRQ")));
	void isr_portcd(void) __attribute__((interrupt("IRQ")));
#endif

