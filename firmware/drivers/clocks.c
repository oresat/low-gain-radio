/*!
 * \file    clocks.c
 * \brief   CLOCKS 
 *
 * \defgroup clocks
 * @{
 */

#include "port.h"
#include "clocks.h"

/*! UARTs
 */
void enable_uart0_clock()
{
	/* Select UART0 clock source as MCGPLL PLL */
	/* note: this step isn't needed for UART1/UART2
           since they are run off the bus clock */
	SIM.SOPT2 |= SOPT2_PLL_DIV_2 | SOPT2_UART0SRC_PLL ;
	SIM.SCGC4 |= SCGC_UART0_CLK;
}

void enable_uart1_clock()
{
	SIM.SCGC4 |= SCGC_UART1_CLK;
}

void enable_uart2_clock()
{
	SIM.SCGC4 |= SCGC_UART2_CLK;
}

void disable_uart0_clock()
{
	SIM.SCGC4 &= ~(SCGC_UART0_CLK);
}

void disable_uart1_clock()
{
	SIM.SCGC4 &= ~(SCGC_UART1_CLK);
}

void disable_uart2_clock()
{
	SIM.SCGC4 &= ~(SCGC_UART2_CLK);
}


/*! SPI
 * Ref: SIM_SCGC4 section 8.2.7
 */
void enable_spi0_clock()
{
	SIM.SCGC4 |= SCGC_SPI0_CLK;
}

void disable_spi0_clock()
{
	SIM.SCGC4 &= ~(SCGC_SPI0_CLK);
}

void enable_spi1_clock()
{
	SIM.SCGC4 |= SCGC_SPI1_CLK;
}

void disable_spi1_clock()
{
	SIM.SCGC4 &= ~(SCGC_SPI1_CLK);
}

void disable_all_spi_clocks()
{
	SIM.SCGC4 &= SCGC_SPI_CLK_OFF;
}

/*! Port Clocks
 */
void enable_all_port_clocks(void)
{
	/* enable clock for all ports */
	SIM.SCGC5 |= SCGC_PORTAE_CLK;
}

void disable_all_port_clocks(void)
{
	SIM.SCGC5 &= ~(SCGC_PORTAE_CLK);
}

void enable_port_clock_x(IO_Port port)
{
	switch(port)
	{
		case IOPORTA:
			SIM.SCGC5 |= SCGC_PORTA_CLK;
			break;
		case IOPORTB:
			SIM.SCGC5 |= SCGC_PORTB_CLK;
			break;
		case IOPORTC:
			SIM.SCGC5 |= SCGC_PORTC_CLK;
			break;
		case IOPORTD:
			SIM.SCGC5 |= SCGC_PORTD_CLK;
			break;
		case IOPORTE:
			SIM.SCGC5 |= SCGC_PORTE_CLK;
			break;
		default:
			break;
	}
}

void disable_port_clock_x(IO_Port port)
{
	switch(port)
	{
		case IOPORTA:
			SIM.SCGC5 &= ~(SCGC_PORTA_CLK);
			break;
		case IOPORTB:
			SIM.SCGC5 &= ~(SCGC_PORTB_CLK);
			break;
		case IOPORTC:
			SIM.SCGC5 &= ~(SCGC_PORTC_CLK);
			break;
		case IOPORTD:
			SIM.SCGC5 &= ~(SCGC_PORTD_CLK);
			break;
		case IOPORTE:
			SIM.SCGC5 &= ~(SCGC_PORTE_CLK);
			break;
		default:
			break;
	}
}

/* TPM Clocks */
void enable_tpm_clocks()
{
	SIM.SOPT2 |= TPMSRC_MCG_CLK;
	SIM.SCGC6 |= SCGC_TPM2_CLK | SCGC_TPM1_CLK | SCGC_TPM0_CLK;
}

void disable_tpm_clocks()
{
	SIM.SCGC6 &= ~(SCGC_TPM2_CLK | SCGC_TPM1_CLK | SCGC_TPM0_CLK);
	SIM.SOPT2 &= TPMSRC_DISABLE;
}

void enable_adc_clock(){
	SIM.SCGC6 |= SCGC_ADC0_CLK;
}

void disable_adc_clock(){
	SIM.SCGC6 &= ~(SCGC_ADC0_CLK);
}

/* PLL External Reference Divider values in MCG.C5 */
#define PRDIV0_0 0x0
#define PRDIV0_16 0xF

/* PLL Clock Enable bit in MCG.C5 */
#define PLLCLKEN (1 << 6)

/* PLL Select in MCG.C6 */
#define PLLS (1 << 6)

/* PLL VCO Divide Factor */
#define VDIV0_24 0x0

/* PLL Lock Bit in MCG.S */
#define LOCK0 (1 << 6)

/* Frequency range select encoding in MCG.C2 */
#define RANGE0_HF (1 << 4)
#define RANGE0_VHF (1 << 5)

/* External Reference Select in MCG.C2 */
#define EREFS0 (1 << 2)

/* External Referance Enable bit in OSC0.CR */
#define ERCLKEN (1 << 7)

void enable_pll_48()
{
	disable_spi0_clock();
	disable_all_port_clocks();

	/* set frequency range select to high frequency range for oscillator
	and select external reference clock
	*/
	MCG.C2 |= RANGE0_HF | EREFS0;

	/* enable external oscillator */
	OSC0.CR = ERCLKEN;

	/* enable MCGPLLCLK if system is in Normal Stop mode */
	MCG.C5 |= PLLCLKEN;

	/* select PLL instead of FLL, multiply signal by 24 to get 48MHz */
	MCG.C6 |= (1 << 6) | VDIV0_24;

	/* wait for PLL lock */
	while(!(MCG.S & LOCK0));

	enable_all_port_clocks();
	enable_spi0_clock();
        //enable_tpm_clocks();
	//enable_adc_clock();

	return;
}

/*! @} */

