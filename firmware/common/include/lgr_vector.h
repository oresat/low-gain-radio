/*! \file lgr_vector.h
 */

#ifndef _LGR_VECTOR_H_
#define _LGR_VECTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum IRQn
{
    /*
     * Cortex-M0+ Processor Exceptions Numbers
     */
    NonMaskableInt_IRQn           = -14,      /*  2 Non Maskable Interrupt */
    HardFault_IRQn                = -13,      /*  3 HardFault Interrupt */



    SVCall_IRQn                   =  -5,      /* 11 SV Call Interrupt */

    PendSV_IRQn                   =  -2,      /* 14 Pend SV Interrupt */
    SysTick_IRQn                  =  -1,      /* 15 System Tick Interrupt */

    /*
     * MKW01Z128 Specific Interrupt Numbers
     */
    DMA0_IRQn                   =   0,
    DMA1_IRQn                   =   1,
    DMA2_IRQn                   =   2,
    DMA3_IRQn                   =   3,
    VECTOR20_IRQn               =   4,
    FTFA_IRQn                   =   5,
    PMC_IRQn                    =   6,
    LLWU_IRQn                   =   7,
    I2C0_IRQn                   =   8,
    I2C1_IRQn                   =   9,
    SPI0_IRQn                   =   10,
    SPI1_IRQn                   =   11,
    UART0_IRQn                  =   12,
    UART1_IRQn                  =   13,
    UART2_IRQn                  =   14,
    ADC0_IRQn                   =   15,
    CMP0_IRQn                   =   16,
    TPM0_IRQn                   =   17,
    TPM1_IRQn                   =   18,
    TPM2_IRQn                   =   19,
    RTC_ALARM_IRQn              =   20,
    RTC_SECONDS_IRQn            =   21,
    PIT_IRQn                    =   22,
    VECTOR39_IRQn               =   23,
    VECTOR40_IRQn               =   24,
    DAC0_IRQn                   =   25,
    TSI0_IRQn                   =   26,
    MCG_IRQn                    =   27,
    LPTMR0_IRQn                 =   28,
    VECTOR45_IRQn               =   29,
    PORTA_IRQn                  =   30,
    PORTCD_IRQn                 =   31
} IRQn_Type;


#ifdef __cplusplus
}
#endif


#endif
