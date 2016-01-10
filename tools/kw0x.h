/*
  Register definitions for the MKW01Z128 Freescale MCU

  Programmed by Theo Hill (mostly) & William Harrington
 */
#ifndef _KW0X_H_
#define _KW0X_H_
#include <stdint.h>
#include <stddef.h>

/* macros for padding */
#define  PASTE(a, b) _PASTE(a, b)
#define _PASTE(a, b) a ## b

#define PAD_BYTES(bytes)  const uint8_t PASTE(__PAD, __COUNTER__)[bytes] \
  __attribute__((deprecated("Padding must never be accessed")))

#define PACKED __attribute__((packed))

/* macros for denoting R/W, Read-Only, and Write-Only registers */
#define _RW
#define _RO const
#define _WO

/* Port control and interrupts module registers */
struct PORT {
	_RW uint32_t PCR[32];
	_WO uint32_t GPCLR;
	_WO uint32_t GPCHR;
	PAD_BYTES(24);
	_RW uint32_t ISFR;  // W1C?
} PACKED;

/* define ports A-E */
#define PORTA (*((volatile struct PORT *) 0x40049000))
#define PORTB (*((volatile struct PORT *) 0x4004A000))
#define PORTC (*((volatile struct PORT *) 0x4004B000))
#define PORTD (*((volatile struct PORT *) 0x4004C000))
#define PORTE (*((volatile struct PORT *) 0x4004D000))

/* GPIO Module registers */
struct GPIO_t {
	_RW uint32_t PDOR;
	_WO uint32_t PSOR;
	_WO uint32_t PCOR;
	_WO uint32_t PTOR;
	_RO uint32_t PDIR;
	_RW uint32_t PDDR;
} PACKED;

/* define GPIO on ports A-E */
#define GPIOA (*((volatile struct GPIO_t *) 0x400FF000))
#define GPIOB (*((volatile struct GPIO_t *) 0x400FF040))
#define GPIOC (*((volatile struct GPIO_t *) 0x400FF080))
#define GPIOD (*((volatile struct GPIO_t *) 0x400FF0C0))
#define GPIOE (*((volatile struct GPIO_t *) 0x400FF100))

/* Fast GPIO module */
#define FGPIOA (*((volatile struct GPIO_t *) 0xF8000000))
#define FGPIOB (*((volatile struct GPIO_t *) 0xF8000040))
#define FGPIOC (*((volatile struct GPIO_t *) 0xF8000080))
#define FGPIOD (*((volatile struct GPIO_t *) 0xF80000C0))
#define FGPIOE (*((volatile struct GPIO_t *) 0xF8000100))

/* Oscillator Module registers */
struct OSC {
	_RW uint8_t CR;
} PACKED;

/* define OSC0 */
#define OSC0 (*((volatile struct OSC *) 0x40065000))

/* System Integration Module registers */
struct SIM_t {
	_RW uint32_t SOPT1;
	PAD_BYTES(4096);
	_RW uint32_t SOPT2;
	PAD_BYTES(4);
	_RW uint32_t SOPT4;
	_RW uint32_t SOPT5;
	PAD_BYTES(4);
	_RW uint32_t SOPT7;
	PAD_BYTES(8);
	_RO uint32_t SDID;
	PAD_BYTES(12);
	_RW uint32_t SCGC4;
	_RW uint32_t SCGC5;
	_RW uint32_t SCGC6;
	_RW uint32_t SCGC7;
	_RW uint32_t CLKDIV1;
	PAD_BYTES(4);
	_RW uint32_t FCFG1;
	_RO uint32_t FCFG2;
	PAD_BYTES(4);
	_RO uint32_t UIDMH;
	_RO uint32_t UIDML;
	_RO uint32_t UIDL;
	PAD_BYTES(156);
	_RW uint32_t COPC;
	_WO uint32_t SRVCOP;
} PACKED;

/* define SIM */
#define SIM (*((volatile struct SIM_t *) 0x40047000))

/* Multi-purpose clock generator registers */
struct MCG_t {
	_RW uint8_t C1;
	_RW uint8_t C2;
	_RW uint8_t C3;
	_RW uint8_t C4;
	_RW uint8_t C5;
	_RW uint8_t C6;
	_RO uint8_t S;
	PAD_BYTES(1);
	_RW uint8_t SC;
	PAD_BYTES(1);
	_RW uint8_t ATCVH;
	_RW uint8_t ATCVL;
	_RW uint8_t C7;
	_RW uint8_t C8;
	PAD_BYTES(1);
	_RW uint8_t C10;
} PACKED;

/* define MCG */
#define MCG (*((volatile struct MCG_t *) 0x40064000))

/* SPI Module registers */
struct SPI_t {
	_RO uint8_t S; /* status register */
	_RW uint8_t BR; /* baud rate register */
	_RW uint8_t C2; /* control register 2 */
	_RW uint8_t C1; /* control register 1 */
	_RW uint8_t ML; /* match low */
	_RW uint8_t MH; /* match high */
	_RW uint8_t DL; /* data low */
	_RW uint8_t DH; /* data high */
	PAD_BYTES(2); /* padding for excess gap between DH & CI */
	_RW uint8_t CI; /* clear interrupt */
	_RW uint8_t C3; /* control register 3 */
} PACKED;

/* define SPI modules */
#define SPI0 (*((volatile struct SPI_t *) 0x40076000))
#define SPI1 (*((volatile struct SPI_t *) 0x40077000))

/* real-time clock module registers */
struct RTC_t {
	_RW uint32_t TSR; /* time seconds register */
	_RW uint32_t TPR; /* time prescaler register */
	_RW uint32_t TAR; /* time alarm register */
	_RW uint32_t TCR; /* time compensation register */
	_RW uint32_t CR; /* control register */
	_RW uint32_t SR; /* status register */
	_RW uint32_t LR; /* lock register */
	_RW uint32_t IER; /* interrupt enable register */
} PACKED;

/* define RTC */
#define RTC (*((volatile struct RTC_t *) 0x4003D000))

/* Timer/PWM Module registers */
struct TPM_t {
	_RW uint32_t SC; /* status and control register */
	_RW uint32_t CNT; /* counter register */
	_RW uint32_t MOD; /* modulo register */
	_RW uint32_t C0SC; /* channel n status and control register 0 */
	_RW uint32_t C0V; /* channel n value register 0 */
	_RW uint32_t C1SC; /* channel n status and control register 1 */
	_RW uint32_t C1V; /* channel n value register 1 */
	_RW uint32_t C2SC; /* channel n status and control register 2 */
	_RW uint32_t C2V; /* channel n value register 2 */
	_RW uint32_t C3SC; /* channel n status and control register 3 */
	_RW uint32_t C3V; /* channel n value register 3 */
	_RW uint32_t C4SC; /* channel n status and control register 4 */
	_RW uint32_t C4V; /* channel n value register 4 */
	_RW uint32_t C5SC; /* channel n status and control register 5 */
	_RW uint32_t C5V; /* channel n value register 5 */
	PAD_BYTES(20);
	_RW uint32_t STATUS; /* capture and compare status register */
	PAD_BYTES(48);
	_RW uint32_t CONF; /* configuration register */
} PACKED;

/* define TPM modules */
#define TPM0 (*((volatile struct TPM_t *) 0x40038000))
#define TPM1 (*((volatile struct TPM_t *) 0x40039000))
#define TPM2 (*((volatile struct TPM_t *) 0x4003A000))

/* System Mode Controller registers */
struct SMC_t {
	_RW uint8_t PMPROT; /* Power Mode Protection register */
	_RW uint8_t PMCTRL; /* Power Mode Control register */
	_RW uint8_t STOPCTRL; /* Stop Control Register */
	_RO uint8_t PMSTAT; /* Power Mode Status register */
} PACKED;

/* define SMC */
#define SMC (*((volatile struct SMC_t *) 0x4007E000))

/* Power Management Controller registers */
struct PMC_t {
	_RW uint8_t LVDSC1; /* Low Voltage Detect Status and Control 1 register */
	_RW uint8_t LVDSC2; /* Low Voltage Detect Status and Control 2 register */
	_RW uint8_t REGSC; /* Regulator Status and Control register */
} PACKED;

/* define PMC */
#define PMC (*((volatile struct PMC_t *) 0x4007D000))

/* Low-Leakage Wakeup Unit */
struct LLWU_t {
	_RW uint8_t PE1; /* Pin Enable 1 register */
	_RW uint8_t PE2; /* Pin Enable 2 register */
	_RW uint8_t PE3; /* Pin Enable 3 register */
	_RW uint8_t PE4; /* Pin Enable 4 register */
	_RW uint8_t ME; /* Module Enable register */
	_RW uint8_t F1; /* Flag 1 register */
	_RW uint8_t F2; /* Flag 2 register */
	_RO uint8_t F3; /* Flag 3 register */
	_RW uint8_t FILT1; /* Pin Filter 1 register */
	_RW uint8_t FILT2; /* Pin Filter 2 register */
} PACKED;

/* define LLWU */
#define LLWU (*((volatile struct LLWU_t *) 0x4007C000))

/* Reset Control Module registers */
struct RCM_t {
	_RO uint8_t SRS0; /* System Reset Status Register 0 */
	_RO uint8_t SRS1; /* System Reset Status Register 1 */
	PAD_BYTES(2);
	_RW uint8_t RPFC; /* Reset Pin Filter Control register */
	_RW uint8_t RPFW; /* Reset Pin Filter Width register */
} PACKED;

/* define RCM */
#define RCM (*((volatile struct RCM_t *) 0x4007F000))

/* Miscellaneous Control Module */
struct MCM_t {
	PAD_BYTES(2);
	_RO uint16_t PLASC; /* Crossbat switch (AXBS) slave configuration */
	_RO uint16_t PLAMC; /* Crossbar switch (AXBS) master configuration */
	_RW uint32_t PLACR; /* Platform Control register */
	PAD_BYTES(48);
	_RW uint32_t CPO; /* Compute Operation control register */
} PACKED;

/* define MCM */
#define MCM (*((volatile struct MCM_t *) 0xF0003000))

/* Micro Trace Buffer registers */
struct MTB_t {
	_RW uint32_t POSITION; /* Position register */
	_RW uint32_t MASTER; /* Master register */
	_RW uint32_t FLOW; /* Flow register */
	_RO uint32_t BASE; /* Base register */
	PAD_BYTES(3824);
	_RO uint32_t MODECTRL; /* Integration Mode Control Register */
	PAD_BYTES(156);
	_RO uint32_t TAGSET; /* Claim TAG Set Register */
	_RO uint32_t TAGCLEAR; /* Claim TAG Clear Register */
	PAD_BYTES(8);
	_RO uint32_t LOCKACCESS; /* Lock Access Register */
	_RO uint32_t LOCKSTAT; /* Lock Status Register */
	_RO uint32_t AUTHSTAT; /* Authentication Status Register */
	_RO uint32_t DEVICEARCH; /* Device Architecture Register */
	PAD_BYTES(8);
	_RO uint32_t DEVICECFG; /* Device Configuration Register */
	_RO uint32_t DEVICETYPID; /* Device Type Identifier Register */
	_RO uint32_t PERIPHID4; /* Peripheral ID register */
	_RO uint32_t PERIPHID5; /* Peripheral ID register */
	_RO uint32_t PERIPHID6; /* Peripheral ID register */
	_RO uint32_t PERIPHID7; /* Peripheral ID register */
	_RO uint32_t PERIPHID0; /* Peripheral ID register */
	_RO uint32_t PERIPHID1; /* Peripheral ID register */
	_RO uint32_t PERIPHID2; /* Peripheral ID register */
	_RO uint32_t PERIPHID3; /* Peripheral ID register */
	_RO uint32_t COMPID0; /* Component ID register */
	_RO uint32_t COMPID1; /* Component ID register */
	_RO uint32_t COMPID2; /* Component ID register */
	_RO uint32_t COMPID3; /* Component ID register */
} PACKED;

/* define MTB */
#define MTB (*((volatile struct MTB_t *) 0xF0000000))

/* Direct Memory Access Multiplexer */
struct DMAMUX_t {
	_RW uint8_t CHCFG0; /* Channel Configuration register */
	_RW uint8_t CHCFG1; /* Channel Configuration register */
	_RW uint8_t CHCFG2; /* Channel Configuration register */
	_RW uint8_t CHCFG3; /* Channel Configuration register */
} PACKED;

/* define DMAMUX0 */
#define DMAMUX0 (*((volatile struct DMAMUX_t *) 0x40021000))

/* Direct Memory Access Controller Module */
struct DMA_t {
	_RW uint32_t SAR; /* Source Address register */
	_RW uint32_t DAR; /* Destination Address register */
	_RW uint32_t DSR_BCR; /* DMA Status register / Byte count register */
	_RW uint32_t DCR; /* DMA control register */
} PACKED;

/* define DMA0 - DMA3 */
#define DMA0 (*((volatile struct DMA_t *) 0x40008100))
#define DMA1 (*((volatile struct DMA_t *) 0x40008110))
#define DMA2 (*((volatile struct DMA_t *) 0x40008120))
#define DMA3 (*((volatile struct DMA_t *) 0x40008130))

/* Analog to Digital Converters module */
struct ADC_t {
	_RW uint32_t SC1A; /* ADC status and control registers 1 */
	_RW uint32_t SC1B; /* ADC status and control registers 1 */
	_RW uint32_t CFG1; /* ADC configuration register 1 */
	_RW uint32_t CFG2; /* ADC configuration register 2 */
	_RO uint32_t RA; /* ADC Data result register */
	_RO uint32_t RB; /* ADC data result register */
	_RW uint32_t CV1; /* Compare Value registers */
	_RW uint32_t CV2; /* Compare Value registers */
	_RW uint32_t SC2; /* Status and Control register 2 */
	_RW uint32_t SC3; /* Status and Control register 3 */
	_RW uint32_t OFS; /* ADC Offset Correction register */
	_RW uint32_t PG; /* ADC Plus-Side Gain register */
	_RW uint32_t MG; /* ADC Minus-Side Gain register */
	_RW uint32_t CLPD; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLPS; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLP4; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLP3; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLP2; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLP1; /* ADC Plus-Side General Calibration Value register */
	_RW uint32_t CLP0; /* ADC Plus-Side General Calibration Value register */
	PAD_BYTES(4);
	_RW uint32_t CLMD; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLMS; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLM4; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLM3; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLM2; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLM1; /* ADC Minus-Side General Calibration Value register */
	_RW uint32_t CLM0; /* ADC Minus-Side General Calibration Value register */
} PACKED;

/* define ADC */
#define ADC (*((volatile struct ADC_t *) 0x4003B000))

/* Comparator module */
struct CMP_t {
	uint8_t CR0; /* Control register 0 */
	uint8_t CR1; /* Control register 1 */
	uint8_t FPR; /* Filter period register */
	uint8_t SCR; /* Status and control register */
	uint8_t DACCR; /* DAC control register */
	uint8_t MUXCR; /* MUX control register */
} PACKED;

/* define CMP */
#define CMP (*((volatile struct CMP_t *) 0x40073000))

/* 12 bit digital to analog converter (DAC) module */
struct DAC_t {
	uint8_t DAT0L; /* DAC data low register */
	uint8_t DAT0H; /* DAC data high register */
	uint8_t DAT1L; /* DAC data low register */
	uint8_t DAT1H; /* DAC data high register */
	PAD_BYTES(28);
	uint8_t SR; /* DAC status register */
	uint8_t C0; /* DAC control register */
	uint8_t C1; /* DAC control register 1 */
	uint8_t C2; /* DAC control register 2 */
} PACKED;

/* define DAC */
#define DAC (*((volatile struct DAC_t *) 0x4003F000))

/* Periodic Interrupt Timer module */
struct PIT_t {
	_RW uint32_t MCR; /* Module Control register */
	PAD_BYTES(220);
	_RO uint32_t LTMR64H; /* PIT Upper Lifetime timer register */
	_RO uint32_t LTMR64L; /* PIT Lower Lifetime timer register */
	PAD_BYTES(24);
	_RW uint32_t LDVAL0; /* Timer Load Value register */
	_RO uint32_t CVAL0; /* Current Timer Value register */
	_RW uint32_t TCTRL0; /* Timer Control register */
	_RW uint32_t TFLG0; /* Timer Flag register */
	_RW uint32_t LDVAL1; /* Timer Load Value register */
	_RO uint32_t CVAL1; /* Current timer value register */
	_RW uint32_t TCTRL1; /* Timer Control register */
	_RW uint32_t TFLG1; /* Timer Flag register */
} PACKED;

/* define PIT */
#define PIT (*((volatile struct PIT_t *) 0x40037000))

/* Low-Power Timer module */
struct LPTMR_t {
	_RW uint32_t CSR; /* Low Power Timer Control status register */
	_RW uint32_t PSR; /* Low Power Timer prescale register */
	_RW uint32_t CMR; /* Low Power Timer compare register */
	_RO uint32_t CNR; /* Low Power Timer counter register */
} PACKED;

/* define LPTMR */
#define LPTMR (*((volatile struct LPTMR_t *) 0x40040000))

/* Universal asynchronous receiver/transmitter module 0 */
struct UART0_t {
	_RW uint8_t BDH; /* UART Baud Rate Register High */
	_RW uint8_t BDL; /* UART Baud Rate Register Low */
	_RW uint8_t C1; /* UART Control Register 1 */
	_RW uint8_t C2; /* UART Control Register 2 */
	_RW uint8_t S1; /* UART Status Register 1 */
	_RW uint8_t S2; /* UART Status Register 2 */
	_RW uint8_t C3; /* UART Control Register 3 */
	_RW uint8_t D; /* UART Data Register */
	_RW uint8_t MA1; /* UART Match Address Registers 1 */
	_RW uint8_t MA2; /* UART Match Address Registers 2 */
	_RW uint8_t C4; /* UART Control Register 4 */
	_RW uint8_t C5; /* UART Control Register 5 */
} PACKED;

/* define UART0 */
#define UART0 (*((volatile struct UART0_t *) 0x4006A000))

/* Universal Asynchronous Receiver/Transmitter Modules 1 & 2 */
struct UART_t {
	_RW uint8_t BDH; /* UART Baud Rate Register High */
	_RW uint8_t BDL; /* UART Baud Rate Register Low */
	_RW uint8_t C1; /* UART Control Register 1 */
	_RW uint8_t C2; /* UART Control Register 2 */
	_RO uint8_t S1; /* UART Status Register 1 */
	_RW uint8_t S2; /* UART Status Register 2 */
	_RW uint8_t C3; /* UART Control Register 3 */
	_RW uint8_t D; /* UART Data Register */
	_RW uint8_t C4; /* UART Control Register 4 */
} PACKED;

/* define UART1 & 2 */
#define UART1 (*((volatile struct UART_t *) 0x4006B000))
#define UART2 (*((volatile struct UART_t *) 0x4006C000))

/* Touch Sensing Input Module */
struct TSI_t {
	_RW uint32_t GENCS; /* TSI General Control and Status Register */
	_RW uint32_t DATA; /* TSI DATA Register */
	_RW uint32_t TSHD; /* TSI Threshold Register */
} PACKED;

/* define TSI */
#define TSI0 (*((volatile struct TSI_t *) 0x40045000))

/* Definition unit tests */
#define IS_LAST_MEMBER(block, reg) \
	_Static_assert(sizeof(block) == offsetof(typeof(block),reg) + sizeof(block.reg), \
		#reg " Is not the last member in " #block)
#define IS_AT_ADDRESS(block, reg, addr) \
	_Static_assert(&(block.reg) == (typeof(&(block.reg)))(addr), \
		#block " struct improperly defined")
#define CHECK_DEFINITION(block, reg, addr) \
	IS_LAST_MEMBER(block, reg); \
	IS_AT_ADDRESS(block, reg, addr)

CHECK_DEFINITION(PORTA,ISFR, 0x400490A0);
CHECK_DEFINITION(PORTB,ISFR, 0x4004A0A0);
CHECK_DEFINITION(PORTC,ISFR, 0x4004B0A0);
CHECK_DEFINITION(PORTD,ISFR, 0x4004C0A0);
CHECK_DEFINITION(PORTE,ISFR, 0x4004D0A0);
CHECK_DEFINITION(SIM,SRVCOP, 0x40048104);
CHECK_DEFINITION(SMC,PMSTAT, 0x4007E003);
CHECK_DEFINITION(PMC,REGSC,  0x4007D002);
CHECK_DEFINITION(LLWU,FILT2, 0x4007C009);
CHECK_DEFINITION(RCM,RPFW,   0x4007F005);
CHECK_DEFINITION(MCM,CPO,    0xF0003040);
CHECK_DEFINITION(MTB,COMPID3,0xF0000FFC);
CHECK_DEFINITION(DMAMUX0,CHCFG3,0x40021003);
CHECK_DEFINITION(DMA0,DCR,   0x4000810C);
CHECK_DEFINITION(DMA1,DCR,   0x4000811C);
CHECK_DEFINITION(DMA2,DCR,   0x4000812C);
CHECK_DEFINITION(DMA3,DCR,   0x4000813C);
CHECK_DEFINITION(MCG,C10,    0x4006400F);
CHECK_DEFINITION(OSC0,CR,    0x40065000);
CHECK_DEFINITION(ADC,CLM0,   0x4003B06C);
CHECK_DEFINITION(CMP,MUXCR,  0x40073005);
CHECK_DEFINITION(DAC,C2,     0x4003F023);
CHECK_DEFINITION(TPM0,CONF,  0x40038084);
CHECK_DEFINITION(TPM1,CONF,  0x40039084);
CHECK_DEFINITION(TPM2,CONF,  0x4003A084);
CHECK_DEFINITION(PIT,TFLG1,  0x4003711C);
CHECK_DEFINITION(LPTMR,CNR,  0x4004000C);
CHECK_DEFINITION(RTC,IER,    0x4003D01C);
CHECK_DEFINITION(SPI0,C3,    0x4007600B);
CHECK_DEFINITION(SPI1,C3,    0x4007700B);
CHECK_DEFINITION(UART0,C5,   0x4006A00B);
CHECK_DEFINITION(UART1,C4,   0x4006B008);
CHECK_DEFINITION(UART2,C4,   0x4006C008);
CHECK_DEFINITION(GPIOA,PDDR, 0x400FF014);
CHECK_DEFINITION(GPIOB,PDDR, 0x400FF054);
CHECK_DEFINITION(GPIOC,PDDR, 0x400FF094);
CHECK_DEFINITION(GPIOD,PDDR, 0x400FF0D4);
CHECK_DEFINITION(GPIOE,PDDR, 0x400FF114);
CHECK_DEFINITION(FGPIOA,PDDR,0xF8000014);
CHECK_DEFINITION(FGPIOB,PDDR,0xF8000054);
CHECK_DEFINITION(FGPIOC,PDDR,0xF8000094);
CHECK_DEFINITION(FGPIOD,PDDR,0xF80000D4);
CHECK_DEFINITION(FGPIOE,PDDR,0xF8000114);
CHECK_DEFINITION(TSI0,TSHD,  0x40045008);

/* Cleanup */
#undef CHECK_DEFINITION
#undef IS_AT_ADDRESS
#undef IS_LAST_MEMBER
#undef PASTE
#undef _PASTE
#undef PAD_BYTES
#undef PACKED
#undef _RW
#undef _RO
#undef _WO
#endif
