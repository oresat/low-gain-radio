#include <stdint.h>

typedef void (*funcp_t)(void);
typedef funcp_t * funcpp_t;

#define SYMVAL(sym) (uint32_t)(((uint8_t *)&(sym)) - ((uint8_t *)0))

/*
 * Area fill code, it is a macro because here functions cannot be called
 * until stacks are initialized.
 */
#define fill32(start, end, filler) { \
	uint32_t *p1 = start; \
	uint32_t *p2 = end; \
	while (p1 < p2) \
	*p1++ = filler; \
}

extern uint32_t __main_stack_base__;
extern uint32_t __main_stack_end__;
extern uint32_t __process_stack_base__;
extern uint32_t __process_stack_end__;
extern uint32_t _textdata;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern funcp_t __init_array_start;
extern funcp_t __init_array_end;
extern funcp_t __fini_array_start;
extern funcp_t __fini_array_end;
extern void main(void);

__attribute__((naked)) void ResetHandler(void) {
	uint32_t psp, reg;

	/* Process Stack initialization, it is allocated starting from the
	   symbol __process_stack_end__ and its lower limit is the symbol
	   __process_stack_base__.*/
	asm volatile ("cpsid   i");
	psp = SYMVAL(__process_stack_end__);
	asm volatile ("msr     PSP, %0" : : "r" (psp));

	/* CPU mode initialization.*/
	reg = 0x2;

	asm volatile ("msr     CONTROL, %0" : : "r" (reg));
	asm volatile ("isb");

	/* DATA segment initialization.*/
	{
		uint32_t *tp, *dp;

		tp = &_textdata;
		dp = &_data;
		while (dp < &_edata)
			*dp++ = *tp++;
	}

	/* BSS segment initialization.*/
	fill32(&__bss_start__, &__bss_end__, 0);


	/* Constructors invocation.*/
	{
		funcpp_t fpp = &__init_array_start;
		while (fpp < &__init_array_end) {
			(*fpp)();
			fpp++;
		}
	}

	/* Invoking application main() function.*/
	main();

	/* Destructors invocation.*/
	{
		funcpp_t fpp = &__fini_array_start;
		while (fpp < &__fini_array_end) {
			(*fpp)();
			fpp++;
		}
	}

	while(1);
}

