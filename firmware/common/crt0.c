/* \file crt0.c
 */
#include <stdint.h>
#include "kw0x.h"

struct flash_config_t {
	uint64_t backdoor;
	uint32_t protection;
	uint8_t  fsec;
	uint8_t  fopt;
	uint8_t  reserved1;
	uint8_t  reserved2;
} __attribute__((packed));

typedef struct flash_config_t flash_config_t;
__attribute__((section("flashconfig")))  flash_config_t _flash_config = {
	.backdoor = 0xFFFFFFFFFFFFFFFF,
	.protection = 0xFFFFFFFF,
	.fsec = 0xFE,
	.fopt = 0xFF,
	.reserved1 = 0xFF,
	.reserved2 = 0xFF,
} ;



typedef void (*funcp_t)(void);
typedef funcp_t * funcpp_t;

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
	/* Disable interrupts */
	asm volatile ("cpsid   i");

	/* CPU mode initialization.*/
	uint32_t reg = 0x0;
	asm volatile ("msr     CONTROL, %0" : : "r" (reg));
	asm volatile ("isb");

	SIM.COPC = 0;

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

