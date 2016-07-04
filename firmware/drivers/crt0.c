#include <stdint.h>
#include "kw0x.h"

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
extern void Vector1C(void);
extern void Vector20(void);
extern void Vector24(void);
extern void Vector28(void);
extern void SVCallVector(void);
extern void DebugMonitorVector(void);
extern void Vector34(void);
extern void PendSVVector(void);
extern void SysTickVector(void);
extern void Vector40(void);
extern void Vector44(void);
extern void Vector48(void);
extern void Vector4C(void);
extern void Vector50(void);
extern void Vector54(void);
extern void Vector58(void);
extern void Vector5C(void);
extern void Vector60(void);
extern void Vector64(void);
extern void Vector68(void);
extern void Vector6C(void);
extern void Vector70(void);
extern void Vector74(void);
extern void Vector78(void);
extern void Vector7C(void);
extern void Vector80(void);
extern void Vector84(void);
extern void Vector88(void);
extern void Vector8C(void);
extern void Vector90(void);
extern void Vector94(void);
extern void Vector98(void);
extern void Vector9C(void);
extern void VectorA0(void);
extern void VectorA4(void);
extern void VectorA8(void);
extern void VectorAC(void);
extern void VectorB0(void);
extern void VectorB4(void);
extern void VectorB8(void);
extern void VectorBC(void);

__attribute__ ((section("vectors"))) vectors_t _vectors = {
	&__main_stack_end__,ResetHandler,       NMIVector,          HardFaultVector,
	MemManageVector,    BusFaultVector,     UsageFaultVector,   Vector1C,
	Vector20,           Vector24,           Vector28,           SVCallVector,
	DebugMonitorVector, Vector34,           PendSVVector,       SysTickVector,
	{
	Vector40,           Vector44,           Vector48,           Vector4C,
	Vector50,           Vector54,           Vector58,           Vector5C,
	Vector60,           Vector64,           Vector68,           Vector6C,
	Vector70,           Vector74,           Vector78,           Vector7C,
	Vector80,           Vector84,           Vector88,           Vector8C,
	Vector90,           Vector94,           Vector98,           Vector9C,
	VectorA0,           VectorA4,           VectorA8,           VectorAC,
	VectorB0,           VectorB4,           VectorB8,           VectorBC
	}
};

__attribute__ ((naked)) void _unhandled_exception(void) {
	while(1);
}

void NMIVector(void) __attribute__((weak, alias("_unhandled_exception")));
void HardFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void MemManageVector(void) __attribute__((weak, alias("_unhandled_exception")));
void BusFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void UsageFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector1C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector20(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector24(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector28(void) __attribute__((weak, alias("_unhandled_exception")));
void SVCallVector(void) __attribute__((weak, alias("_unhandled_exception")));
void DebugMonitorVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector34(void) __attribute__((weak, alias("_unhandled_exception")));
void PendSVVector(void) __attribute__((weak, alias("_unhandled_exception")));
void SysTickVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector40(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector44(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector48(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector4C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector50(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector54(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector58(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector5C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector60(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector64(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector68(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector6C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector70(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector74(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector78(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector7C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector80(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector84(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector88(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector8C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector90(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector94(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector98(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector9C(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorAC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorBC(void) __attribute__((weak, alias("_unhandled_exception")));

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

