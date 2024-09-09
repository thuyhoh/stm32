#include "stm32f407xx_rcc_driver.h"

static uint16_t AHB_Prescaler[8] = {2, 4, 8, 16, 64, 128, 256, 512}; 
static uint8_t APB1_Prescaler[4] = {2, 4, 8, 16};
static uint8_t APB2_Prescaler[4] = {2, 4, 8, 16};
void RCC_Config(RCC_Config_t *pRCC_Config)
{
	
}



// Get the value of APB1 Clock 
uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1, SystemClk;
	uint16_t clkSrc, temp, ahbPrescaler;
	uint8_t apb1Prescaler;
	
	// Get Clock Source
	clkSrc = ((RCC_BASE->CFGR >> 2) & 0x03);
	// System Clock 
	if(clkSrc == SYS_HSI_OSC)
	{// HSI oscillator used as the system clock
		SystemClk = HSI_CLOCK_SOURCE; 
	}
	else if(clkSrc == SYS_HSE_OSC)
	{// HSEoscillator used as the system clock
		SystemClk = HSE_CLOCK_SOURCE; 
	}else if(clkSrc == SYS_PLL_OSC)
	{// PLL oscillator used as the system clock
		SystemClk = PLL_CLOCK_SOURCE;
	}else
	{ //  not applicable
		SystemClk = HSI_CLOCK_SOURCE;
	}
	
	// get AHB1 Prescaler 
	temp = ((RCC_BASE->CFGR >> 4) & 0xf);
	if(temp < 8)
	{
		ahbPrescaler = 1;
	}
	else
	{
		ahbPrescaler = AHB_Prescaler[temp - 8];
	}
	
	temp = ((RCC_BASE->CFGR >> 10) & 0x7);
	if(temp < 4)
	{
		apb1Prescaler = 1;
	}else 
	{
		apb1Prescaler = APB1_Prescaler[temp - 4];
	}
	pclk1 = (SystemClk / ahbPrescaler)/apb1Prescaler;
	
	return pclk1;
}

// Get the value of APB2 Clock 
uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2, SystemClk;
	uint16_t clkSrc, temp, ahbPrescaler;
	uint8_t apb2Prescaler;
	// Get Clock Source
	clkSrc = ((RCC_BASE->CFGR >> 2) & 0x03);
	// System Clock 
	if(clkSrc == SYS_HSI_OSC)
	{// HSI oscillator used as the system clock
		SystemClk = HSI_CLOCK_SOURCE; 
	}
	else if(clkSrc == SYS_HSE_OSC)
	{// HSEoscillator used as the system clock
		SystemClk = HSE_CLOCK_SOURCE; 
	}else if(clkSrc == SYS_PLL_OSC)
	{// PLL oscillator used as the system clock
		SystemClk = PLL_CLOCK_SOURCE;
	}else
	{ //  not applicable
		SystemClk = HSI_CLOCK_SOURCE;
	}
	
	// get AHB1 Prescaler 
	temp = ((RCC_BASE->CFGR >> 4) & 0xf);
	if(temp < 8)
	{
		ahbPrescaler = 1;
	}
	else
	{
		ahbPrescaler = AHB_Prescaler[temp - 8];
	}
	
	temp = ((RCC_BASE->CFGR >> 13) & 0x7);
	if(temp < 4)
	{
		apb2Prescaler = 1;
	}else 
	{
		apb2Prescaler = APB2_Prescaler[temp - 4];
	}
	pclk2 = (SystemClk / ahbPrescaler)/apb2Prescaler;
	
	return pclk2;
}
