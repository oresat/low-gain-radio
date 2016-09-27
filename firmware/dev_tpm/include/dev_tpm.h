/* \file dev_tpm.h
 */

#ifndef _DEV_TPM_H_
	#define _DEV_TPM_H_

	void NMIVector(void)  __attribute__((interrupt("IRQ")));
	void isr_porta(void)  __attribute__((interrupt("IRQ")));
	void isr_portcd(void) __attribute__((interrupt("IRQ")));

#endif

