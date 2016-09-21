/* \file lgr_vector.c
 */
#include <stdint.h>
#include "lgr_vector.h"
#include "led.h"

typedef void  (*irq_vector_t)(void);

typedef struct {
	uint32_t      *init_stack;
	irq_vector_t  reset_vector;
	irq_vector_t  nmi_vector;
	irq_vector_t  hardfault_vector;
	irq_vector_t  memmanage_vector;
	irq_vector_t  busfault_vector;
	irq_vector_t  usagefault_vector;
	irq_vector_t  vector1c;
	irq_vector_t  vector20;
	irq_vector_t  vector24;
	irq_vector_t  vector28;
	irq_vector_t  svcall_vector;
	irq_vector_t  debugmonitor_vector;
	irq_vector_t  vector34;
	irq_vector_t  pendsv_vector;
	irq_vector_t  systick_vector;
	irq_vector_t  vectors[32];
} vectors_t;

extern uint32_t __main_stack_end__;
extern void ResetHandler(void);
extern void NMIVector(void);
extern void HardFaultVector(void);
extern void MemManageVector(void);
extern void BusFaultVector(void);
extern void UsageFaultVector(void);
extern void Vector7(void);
extern void Vector8(void);
extern void Vector9(void);
extern void Vector10(void);
extern void SVCallVector(void);
extern void DebugMonitorVector(void);
extern void Vector13(void);
extern void PendSVVector(void);
extern void SysTickVector(void);
extern void isr_dma0(void);
extern void isr_dma1(void);
extern void isr_dma2(void);
extern void isr_dma3(void);
extern void Vector20(void);
extern void isr_ftfa(void);
extern void isr_pmc(void);
extern void isr_llwu(void);
extern void isr_i2c0(void);
extern void isr_i2c1(void);
extern void isr_spi0(void);
extern void isr_spi1(void);
extern void isr_uart0(void);
extern void isr_uart1(void);
extern void isr_uart2(void);
extern void isr_adc0(void);
extern void isr_cmp0(void);
extern void isr_tpm0(void);
extern void isr_tmp1(void);
extern void isr_tmp2(void);
extern void isr_rtc_alarm(void);
extern void isr_rtc_seconds(void);
extern void isr_pit(void);
extern void Vector39(void);
extern void Vector40(void);
extern void isr_dac0(void);
extern void isr_tsi0(void);
extern void isr_mcg(void);
extern void isr_lptmr0(void);
extern void Vector45(void);
extern void isr_porta(void);
extern void isr_portcd(void);

__attribute__ ((used, section("vectors"))) vectors_t _vectors = {
	&__main_stack_end__,ResetHandler,       NMIVector,          HardFaultVector,
	MemManageVector,    BusFaultVector,     UsageFaultVector,   Vector7,
	Vector8,            Vector9,            Vector10,           SVCallVector,
	DebugMonitorVector, Vector13,           PendSVVector,       SysTickVector,
	{
	isr_dma0, 			isr_dma1, 			isr_dma2, 		isr_dma3,
	Vector20, 			isr_ftfa, 			isr_pmc, 		isr_llwu,
   	isr_i2c0, 			isr_i2c1, 			isr_spi0, 		isr_spi1,
	isr_uart0, 			isr_uart1, 			isr_uart2, 		isr_adc0,
	isr_cmp0, 			isr_tpm0, 			isr_tmp1, 		isr_tmp2,
	isr_rtc_alarm, 		isr_rtc_seconds,	isr_pit, 		Vector39,
	Vector40, 			isr_dac0, 			isr_tsi0, 		isr_mcg,
	isr_lptmr0, 		Vector45, 			isr_porta, 		isr_portcd
	}
};

__attribute__ ((naked)) void _hard_fault_exception(void) {
	while(1){ 
		led_action(TOGGLE, green);
		for(int i = 0; i<1000000; i++) ;
	};
}

__attribute__ ((naked)) void _unhandled_exception(void) {
	while(1);
}

void NMIVector(void) __attribute__((weak, alias("_unhandled_exception")));
void HardFaultVector(void) __attribute__((weak, alias("_hard_fault_exception")));
void MemManageVector(void) __attribute__((weak, alias("_unhandled_exception")));
void BusFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void UsageFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector7(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector8(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector9(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector10(void) __attribute__((weak, alias("_unhandled_exception")));
void SVCallVector(void) __attribute__((weak, alias("_unhandled_exception")));
void DebugMonitorVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector13(void) __attribute__((weak, alias("_unhandled_exception")));
void PendSVVector(void) __attribute__((weak, alias("_unhandled_exception")));
void SysTickVector(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_dma0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_dma1(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_dma2(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_dma3(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector20(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_ftfa(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_pmc(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_llwu(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_i2c0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_i2c1(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_spi0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_spi1(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_uart0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_uart1(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_uart2(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_adc0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_cmp0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_tpm0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_tmp1(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_tmp2(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_rtc_alarm(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_rtc_seconds(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_pit(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector39(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector40(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_dac0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_tsi0(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_mcg(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_lptmr0(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector45(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_porta(void) __attribute__((weak, alias("_unhandled_exception")));
void isr_portcd(void) __attribute__((weak, alias("_unhandled_exception")));

