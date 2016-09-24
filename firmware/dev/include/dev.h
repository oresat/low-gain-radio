/* \file dev.h
 */

#ifndef _DEV_H_
	#define _DEV_H_

	void NMIVector(void)  __attribute__((interrupt("IRQ")));
	void isr_porta(void)  __attribute__((interrupt("IRQ")));
	void isr_portcd(void) __attribute__((interrupt("IRQ")));
#endif

#define USE_XCVR_TX_MODE false
#define USE_XCVR_RX_MODE false
#define USE_XCVR_LISTEN_MODE true
#define TEST_TPM false

#ifndef TEST_TPM
#define TEST_TPM false
#endif

#ifndef USE_XCVR_TX_MODE
#define USE_XCVR_TX_MODE false
#endif

#ifndef USE_XCVR_RX_MODE
#define USE_XCVR_TX_MODE false
#endif

#ifndef USE_XCVR_LISTEN_MODE
#define USE_XCVR_LISTEN_MODE false
#endif

#if USE_XCVR_TX_MODE && USE_XCVR_RX_MODE
#error "CANNOT USE TX AND RX AT SAME TIME!" 
#endif

#if USE_XCVR_LISTEN_MODE && USE_XCVR_RX_MODE
#error "CANNOT USE LISTEN AND RX AT SAME TIME!" 
#endif
