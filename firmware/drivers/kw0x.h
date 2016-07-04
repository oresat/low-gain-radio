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

/* Chapter 7: Port control and interrupts module registers */
struct port {
	_RW uint32_t PCR[32];
	_WO uint32_t GPCLR;
	_WO uint32_t GPCHR;
	PAD_BYTES(24);
	_RW uint32_t ISFR;
} PACKED;

/* Chapter 8: System Integration Module registers */
struct sim {
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

/* Chapter 9: System Mode Controller registers */
struct smc {
	_RW uint8_t PMPROT; /* Power Mode Protection register */
	_RW uint8_t PMCTRL; /* Power Mode Control register */
	_RW uint8_t STOPCTRL; /* Stop Control Register */
	_RO uint8_t PMSTAT; /* Power Mode Status register */
} PACKED;

/* Chapter 10: Power Management Controller registers */
struct pmc {
	_RW uint8_t LVDSC1; /* Low Voltage Detect Status and Control 1 register */
	_RW uint8_t LVDSC2; /* Low Voltage Detect Status and Control 2 register */
	_RW uint8_t REGSC; /* Regulator Status and Control register */
} PACKED;

/* Chapter 11: Low-Leakage Wakeup Unit */
struct llwu {
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

/* Chapter 12: Reset Control Module registers */
struct rcm {
	_RO uint8_t SRS0; /* System Reset Status Register 0 */
	_RO uint8_t SRS1; /* System Reset Status Register 1 */
	PAD_BYTES(2);
	_RW uint8_t RPFC; /* Reset Pin Filter Control register */
	_RW uint8_t RPFW; /* Reset Pin Filter Width register */
} PACKED;

/* Chapter 14: Miscellaneous Control Module */
struct mcm {
	PAD_BYTES(8);
	_RO uint16_t PLASC; /* Crossbat switch (AXBS) slave configuration */
	_RO uint16_t PLAMC; /* Crossbar switch (AXBS) master configuration */
	_RW uint32_t PLACR; /* Platform Control register */
	PAD_BYTES(48);
	_RW uint32_t CPO; /* Compute Operation control register */
} PACKED;

/* Chapter 15: Micro Trace Buffer registers */
struct mtb {
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

/* Chapter 18: Direct Memory Access Multiplexer */
struct dmamux {
	_RW uint8_t CHCFG0; /* Channel Configuration register */
	_RW uint8_t CHCFG1; /* Channel Configuration register */
	_RW uint8_t CHCFG2; /* Channel Configuration register */
	_RW uint8_t CHCFG3; /* Channel Configuration register */
} PACKED;

/* Chapter 19: Direct Memory Access Controller Module */
struct dma {
	_RW uint32_t SAR; /* Source Address register */
	_RW uint32_t DAR; /* Destination Address register */
	_RW uint32_t DSR_BCR; /* DMA Status register / Byte count register */
	_RW uint32_t DCR; /* DMA control register */
} PACKED;

/* Chapter 20: Multi-purpose clock generator registers */
struct mcg {
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

/* Chapter 21: Oscillator Module registers */
struct osc {
	_RW uint8_t CR;
} PACKED;

/* Chapter 23: Flash Memory Module */
struct ftfa {
	_RW uint8_t FSTAT;
	_RW uint8_t FCNFG;
	_RO uint8_t FSEC;
	_RO uint8_t FOPT;
	_RW uint8_t FCCOB3;
	_RW uint8_t FCCOB2;
	_RW uint8_t FCCOB1;
	_RW uint8_t FCCOB0;
	_RW uint8_t FCCOB7;
	_RW uint8_t FCCOB6;
	_RW uint8_t FCCOB5;
	_RW uint8_t FCCOB4;
	_RW uint8_t FCCOBB;
	_RW uint8_t FCCOBA;
	_RW uint8_t FCCOB9;
	_RW uint8_t FCCOB8;
	_RW uint8_t FPROT3;
	_RW uint8_t FPROT2;
	_RW uint8_t FPROT1;
	_RW uint8_t FPROT0;
} PACKED;

/* Chapter 24: Analog to Digital Converters module */
struct adc {
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

/* Chapter 25: Comparator module */
struct cmp {
	_RW uint8_t CR0; /* Control register 0 */
	_RW uint8_t CR1; /* Control register 1 */
	_RW uint8_t FPR; /* Filter period register */
	_RW uint8_t SCR; /* Status and control register */
	_RW uint8_t DACCR; /* DAC control register */
	_RW uint8_t MUXCR; /* MUX control register */
} PACKED;

/* Chapter 26: 12 bit digital to analog converter (DAC) module */
struct dac {
	_RW uint8_t DAT0L; /* DAC data low register */
	_RW uint8_t DAT0H; /* DAC data high register */
	_RW uint8_t DAT1L; /* DAC data low register */
	_RW uint8_t DAT1H; /* DAC data high register */
	PAD_BYTES(28);
	_RW uint8_t SR; /* DAC status register */
	_RW uint8_t C0; /* DAC control register */
	_RW uint8_t C1; /* DAC control register 1 */
	_RW uint8_t C2; /* DAC control register 2 */
} PACKED;

/* Chapter 27: Timer/PWM Module registers */
struct tpm {
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

/* Chapter 28: Periodic Interrupt Timer module */
struct pit {
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

/* Chapter 29: Low-Power Timer module */
struct lptmr {
	_RW uint32_t CSR; /* Low Power Timer Control status register */
	_RW uint32_t PSR; /* Low Power Timer prescale register */
	_RW uint32_t CMR; /* Low Power Timer compare register */
	_RO uint32_t CNR; /* Low Power Timer counter register */
} PACKED;

/* Chapter 30: real-time clock module registers */
struct rtc {
	_RW uint32_t TSR; /* time seconds register */
	_RW uint32_t TPR; /* time prescaler register */
	_RW uint32_t TAR; /* time alarm register */
	_RW uint32_t TCR; /* time compensation register */
	_RW uint32_t CR; /* control register */
	_RW uint32_t SR; /* status register */
	_RW uint32_t LR; /* lock register */
	_RW uint32_t IER; /* interrupt enable register */
} PACKED;

/* Chapter 31: SPI Module registers */
struct spi {
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

/* Chapter 32: Universal asynchronous receiver/transmitter module 0 */
struct uart0 {
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

/* Chapter 33: Universal Asynchronous Receiver/Transmitter Modules 1 & 2 */
struct uart {
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

/* Chapter 34: GPIO Module registers */
struct gpio {
	_RW uint32_t PDOR;
	_WO uint32_t PSOR;
	_WO uint32_t PCOR;
	_WO uint32_t PTOR;
	_RO uint32_t PDIR;
	_RW uint32_t PDDR;
} PACKED;

/* Chapter 35: Touch Sensing Input Module */
struct tsi {
	_RW uint32_t GENCS; /* TSI General Control and Status Register */
	_RW uint32_t DATA; /* TSI DATA Register */
	_RW uint32_t TSHD; /* TSI Threshold Register */
} PACKED;

/* Peripheral module instances */
#define PORTA  (*((volatile struct port *) 0x40049000))
#define PORTB  (*((volatile struct port *) 0x4004A000))
#define PORTC  (*((volatile struct port *) 0x4004B000))
#define PORTD  (*((volatile struct port *) 0x4004C000))
#define PORTE  (*((volatile struct port *) 0x4004D000))
#define SIM    (*((volatile struct sim *)  0x40047000))
#define SMC    (*((volatile struct smc *)  0x4007E000))
#define PMC    (*((volatile struct pmc *)  0x4007D000))
#define LLWU   (*((volatile struct llwu *) 0x4007C000))
#define RCM    (*((volatile struct rcm *)  0x4007F000))
#define MCM    (*((volatile struct mcm *)  0xF0003000))
#define MTB    (*((volatile struct mtb *)  0xF0000000))
#define DMAMUX0 (*((volatile struct dmamux *) 0x40021000))
#define DMA0   (*((volatile struct dma *)  0x40008100))
#define DMA1   (*((volatile struct dma *)  0x40008110))
#define DMA2   (*((volatile struct dma *)  0x40008120))
#define DMA3   (*((volatile struct dma *)  0x40008130))
#define MCG    (*((volatile struct mcg *)  0x40064000))
#define OSC0   (*((volatile struct osc *)  0x40065000))
#define FTFA   (*((volatile struct ftfa *) 0x40020000))
#define ADC    (*((volatile struct adc *)  0x4003B000))
#define CMP    (*((volatile struct cmp *)  0x40073000))
#define DAC    (*((volatile struct dac *)  0x4003F000))
#define TPM0   (*((volatile struct tpm *)  0x40038000))
#define TPM1   (*((volatile struct tpm *)  0x40039000))
#define TPM2   (*((volatile struct tpm *)  0x4003A000))
#define PIT    (*((volatile struct pit *)  0x40037000))
#define LPTMR  (*((volatile struct lptmr *)0x40040000))
#define RTC    (*((volatile struct rtc *)  0x4003D000))
#define SPI0   (*((volatile struct spi *)  0x40076000))
#define SPI1   (*((volatile struct spi *)  0x40077000))
#define UART0  (*((volatile struct uart0 *)0x4006A000))
#define UART1  (*((volatile struct uart *) 0x4006B000))
#define UART2  (*((volatile struct uart *) 0x4006C000))
#define GPIOA  (*((volatile struct gpio *) 0x400FF000))
#define GPIOB  (*((volatile struct gpio *) 0x400FF040))
#define GPIOC  (*((volatile struct gpio *) 0x400FF080))
#define GPIOD  (*((volatile struct gpio *) 0x400FF0C0))
#define GPIOE  (*((volatile struct gpio *) 0x400FF100))
#define FGPIOA (*((volatile struct gpio *) 0xF8000000))
#define FGPIOB (*((volatile struct gpio *) 0xF8000040))
#define FGPIOC (*((volatile struct gpio *) 0xF8000080))
#define FGPIOD (*((volatile struct gpio *) 0xF80000C0))
#define FGPIOE (*((volatile struct gpio *) 0xF8000100))
#define TSI0   (*((volatile struct tsi *)  0x40045000))

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
CHECK_DEFINITION(FTFA,FPROT0,0x40020013);
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
