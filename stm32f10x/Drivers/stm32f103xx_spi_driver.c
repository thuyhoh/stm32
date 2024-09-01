#include "stm32f103xx_spi_driver.h"

static void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDi)
{
	if(ENorDi == CLOCK_ENABLE)
	{
		if(pSPIx == SPI1_BASEPTR)
		{
			SPI1_PCLK_ENABLE();
		}else if (pSPIx == SPI2_BASEPTR)
		{
			SPI2_PCLK_ENABLE();
		}else if(pSPIx == SPI3_BASEPTR)
		{
			SPI3_PCLK_ENABLE();
		}else
		{
			// error
		}
	}else
	{
		if(pSPIx == SPI1_BASEPTR)
		{
			SPI1_PCLK_DISABLE();
		}else if (pSPIx == SPI2_BASEPTR)
		{
			SPI2_PCLK_DISABLE();
		}else if(pSPIx == SPI3_BASEPTR)
		{
			SPI3_PCLK_DISABLE();
		}else
		{
			// error
		}
	}
}

/*
											master												slave
	SCK				 Alternate function push-pull					Input floating 
	MOSI			 Alternate function push-pull					Input floating /Input pull-up
	MISO			 Input floating / Input pull-up				Alternate function push-pull
	NSS				 Software, GPIO												Input floating/ Input pull-up / Input pull-down

SPI1
SCK	:	PA5
MISO:	PA6
MOSI:	PA7
NSS	:	PA4

SPI2
SCK	:	PB13
MISO:	PB14
MOSI:	PB15
NSS	:	PB12
*/

static void SPI_PinConfig(SPI_RegDef_t *pSPIx, uint8_t SPI_Mode)
{
	GPIO_Handle_t GPIO_Handle;
	
	if(SPI_Mode == SPI_MASTER_MODE)
	{	// Master Mode
		if(pSPIx == SPI1_BASEPTR)
		{
			GPIO_Handle.pGPIOx = GPIOB_BASEPTR;
			// SCK_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_13;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// MISO_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_14;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
			GPIO_Init(&GPIO_Handle);
			// MOSI_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_15;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// NSS_Pin -> HardWare
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_12; 
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_GP_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			GPIO_SetPin(GPIO_Handle.pGPIOx, GPIO_Handle.GPIO_Config.GPIO_PinNumber);
		}
		else if(pSPIx == SPI2_BASEPTR)
		{
			GPIO_Handle.pGPIOx = GPIOA_BASEPTR;
			// SCK_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_5;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// MISO_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_6;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_INPUT_PU_PD;
			GPIO_Init(&GPIO_Handle);
			// MOSI_Pin
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_7;
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_AF_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			// NSS_Pin -> HardWare
			GPIO_Handle.GPIO_Config.GPIO_PinNumber = GPIO_PIN_4; 
			GPIO_Handle.GPIO_Config.GPIO_PinMode = GPIO_OUTPUT_50MHZ_GP_PP_MODE;
			GPIO_Init(&GPIO_Handle);
			GPIO_SetPin(GPIO_Handle.pGPIOx, GPIO_Handle.GPIO_Config.GPIO_PinNumber);
		}
		else
		{
			// error
		}
	}else 
	{	// Slave Mode
		// to do
	}
}
	

void SPI_Init(SPI_Handle_t *SPI_Handle)
{
	// Enable Clock for SPI
	SPI_PeriClockControl(SPI_Handle->pSPIx, ENABLE);
	
	// Pin Confic
	SPI_PinConfig(SPI_Handle->pSPIx, SPI_Handle->SPI_Config.SPI_Mode);
	uint32_t tmpReg = 0;
	
	// Configure SPI Mode
	tmpReg |= (uint32_t)(SPI_Handle->SPI_Config.SPI_Mode<<2);
	
	// Configure SPI Bus Config
	if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		tmpReg &= (uint32_t)~(1<<15);
	}else if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tmpReg |= (uint32_t)(1<<15);
	}else if(SPI_Handle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		tmpReg &= (uint32_t)~(1<<15);
		tmpReg &= (uint32_t)~(1<<14);
	}else
	{
		// errror
	}
	
	tmpReg |= (uint32_t)((SPI_Handle->SPI_Config.SPI_BaudRate 			<< 3)  | 		/**/
											 (SPI_Handle->SPI_Config.SPI_FrameFormat 	<< 7)    |		/*MSB or LSB first*/
											 (SPI_Handle->SPI_Config.SPI_DFF 					<< 11)   |		/**/
											 (SPI_Handle->SPI_Config.SPI_CPOL 					<< 1)  |		/**/
										   (SPI_Handle->SPI_Config.SPI_CPHA  				<< 0 ))  ;	  /**/
	
	// restore in SPI_CR1 register
	SPI_Handle->pSPIx->CR1 |= tmpReg;				
}
void SPI_Deinit(SPI_RegDef_t *pSPIx)
{
	// reset SPIx Register
	// Disable Clock for SPI
}

/**/
void SPI_NSS(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1_BASEPTR)
	{
		GPIO_ToggleOutputPin(GPIOB_BASEPTR, GPIO_PIN_12);
	}else if(pSPIx == SPI2_BASEPTR)
	{
		GPIO_ToggleOutputPin(GPIOA_BASEPTR, GPIO_PIN_4);
	}else
	{
		// error
	}
}


static uint8_t SPI_GetFlag(SPI_RegDef_t *pSPIx,uint32_t SPI_Flag)
{
	if(pSPIx->SR &= SPI_Flag) return FLAG_SET;
	else return FLAG_RESET;
}

/* Transmit data */
void SPI_Send(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len)
	{
		while(SPI_GetFlag(pSPIx, SPI_TXE_FLAG) == FLAG_RESET){}
		if(pSPIx->CR1 & SPI_CR1_DFF)
		{ // DFF 16bits
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			len = len - 2;
			(uint16_t *)pTxBuffer++;
		}else
		{	// DFF 16bits
			pSPIx->DR = *pTxBuffer;
			len = len - 1;
			pTxBuffer++;
		}
	}
}

void SPI_Transmit(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	SPI_NSS(pSPIx);
	SPI_Send(pSPIx, pTxBuffer, len);
	SPI_NSS(pSPIx);
}

/* Receive data */
void SPI_Receive(void)
{}

/* IRQ Configure and IRQ handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{}
void SPI_IRQHandling(SPI_RegDef_t *pSPIx)
{}

