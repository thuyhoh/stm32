/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#include "stm32f407xx_spi_driver.h"


/* Peripheral Clock setup */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pSPIx == SPI1_BASE)
		{
			SPI1_PCLK_EN();
		}else if(pSPIx == SPI2_BASE)
		{
			SPI2_PCLK_EN();
		}else if(pSPIx == SPI3_BASE)
		{
			SPI3_PCLK_EN();
		}else
		{
			// error
		}
			
	}else
	{
		if(pSPIx == SPI1_BASE)
		{
			SPI1_PCLK_DIS();
		}else if(pSPIx == SPI2_BASE)
		{
			SPI2_PCLK_DIS();
		}else
		{
			SPI3_PCLK_DIS();
		}
	}
}
/*
*SPI1:GPIO_AF_AF5
				CONFIG
	NSS: 		PA4		PA15
	SCK:		PA5		PB3
	MISO:		PA6		PB4
	MOSI:		PA7		PB5

*SPI2:GPIO_AF_AF5
				CONFIG	
	NSS: 		PB9				PB12
	SCK:		PB10			PB13
	MISO:		PB14			PC2
	MOSI:		PB15			PC3

*SPI3:GPIO_AF_AF6
				CONFIG
	NSS: 		PA4				PA15
	SCK:		PB3				PC10			
	MISO:		PB4 			PC11
	MOSI:		PB5			PC12	
*/

static void SPI_PinConfig(SPI_RegDef_t *pSPIx, uint8_t SPI_DeviceMode)
{
	GPIO_Handle_t *pGPIO_Handle = (GPIO_Handle_t *)malloc(sizeof(GPIO_Handle_t));
	if(SPI_DeviceMode == SPI_DEVICE_MASTER_MODE)
	{	// Master mode
		if(pSPIx == SPI1_BASE)
		{
			pGPIO_Handle->pGPIOx = GPIOA_BASE;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTF;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF_AF5;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPER_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_VHIGH;
			
			// SCK_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
			GPIO_Init(pGPIO_Handle);
			
			// MISO_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
			GPIO_Init(pGPIO_Handle);
			
			// MOSI_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
			GPIO_Init(pGPIO_Handle);
			
			// NSS_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
			GPIO_Init(pGPIO_Handle);
			
		}
		else if(pSPIx == SPI2_BASE)
		{
			pGPIO_Handle->pGPIOx = GPIOB_BASE;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTF;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF_AF5;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPER_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_VHIGH;
			
			// SCK_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_10;
			GPIO_Init(pGPIO_Handle);
			
			// MISO_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
			GPIO_Init(pGPIO_Handle);
			
			// MOSI_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
			GPIO_Init(pGPIO_Handle);
			
			// NSS_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
			GPIO_Init(pGPIO_Handle);
		}
		else if(pSPIx == SPI3_BASE)
		{
			pGPIO_Handle->pGPIOx = GPIOB_BASE;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTF;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF_AF5;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPER_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PP;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_VHIGH;
			
			// SCK_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_3;
			GPIO_Init(pGPIO_Handle);
			
			// MISO_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
			GPIO_Init(pGPIO_Handle);
			
			// MOSI_Pin
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
			GPIO_Init(pGPIO_Handle);
			
			// NSS_Pin
			pGPIO_Handle->pGPIOx = GPIOC_BASE;
			pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
			GPIO_Init(pGPIO_Handle);
		}else
		{// error
			
		}
	
	}else
	{	// slave mode
		
	}
	
	free(pGPIO_Handle);
}

/* GPIO Init and DeInit */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	// Configure Clock
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	
	// Configure Pin
//	SPI_PinConfig(pSPIHandle->pSPIx);
		
	// congfigure the SPI_CR1 register
	uint32_t tempreg = 0;
	
	tempreg |= (uint32_t)(pSPIHandle->SPI_Config.SPI_DeviceMode << 2);
	
	// configure the bus config
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		// BIDI must be cleared
		tempreg &= (uint32_t)~(1<<15);
	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		// BIDI must be set
		tempreg &= (1<<15);
	}else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		// BIDI must be cleared 
		tempreg &= (uint32_t)~(1<<15);
		// RXONLY bit must be set
		tempreg |= (1<<10);
	}
	
	// Configure the serial clock (baud rate)
	tempreg |= (uint32_t)(pSPIHandle->SPI_Config.SPI_SclkSpeed << 3);
	// Configure the Data Frame Format
	tempreg |= (uint32_t)(pSPIHandle->SPI_Config.SPI_DFF << 11);
	// Configure the CPOL
	tempreg |= (uint32_t)(pSPIHandle->SPI_Config.SPI_CPOL<<1);
	// Configure the CPHA
	tempreg |= (uint32_t)(pSPIHandle->SPI_Config.SPI_CPHA<<0);
	
	pSPIHandle->pSPIx->CR1 = tempreg;
	tempreg =  0;
	
}
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	
}

static uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t SPI_FlagName)
{
	if( (pSPIx->SR & SPI_FlagName) == SPI_FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/* Data send */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len)
	{
		// 1. Waiting until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET){}
		
		// 2. Check the DFF	bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{  // 16 bit DFF
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			len = len - 2;
			(uint16_t *)pTxBuffer++;
		}else
		{  // 8 bit DFF
			pSPIx->DR = *(pTxBuffer);
			len = len - 1;
			pTxBuffer++;
		}
	}
}

void SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->RxState;
	if(state != SPI_BUSY_IN_RX)
	{
		// 1. Save the Tx Buffer and Txlen in to the global variable
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->Txlen = len;
		// 2. Mask the SPI state as busy in transmition so that no other code can 
		pSPIHandle->TxState = SPI_BUSY_IN_TX;
		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1<< SPI_CR2_TXEIE);
	}
//	return state;
}



/* Receivie data */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
	while(len)
	{
		// 1. Waiting until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET){}
		
		// 2. Check the DFF	bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{  // 16 bit DFF
			*((uint16_t *)pRxBuffer) = pSPIx->DR;
			len = len - 2;
			(uint16_t *)pRxBuffer++;
		}else
		{  // 8 bit DFF
			*(pRxBuffer) = pSPIx->DR;
			len = len - 1;
			pRxBuffer++;
		}
	}
}

void SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len)
{
	uint8_t state = pSPIHandle->RxState;
	if(state != SPI_BUSY_IN_TX)
	{
		// 1. Save the Tx Buffer and Txlen in to the global variable
		pSPIHandle->pRxBuffer = pTxBuffer;
		pSPIHandle->Rxlen = len;
		// 2. Mask the SPI state as busy in transmition so that no other code can 
		pSPIHandle->RxState = SPI_BUSY_IN_RX;
		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1<< SPI_CR2_TXEIE);
	}
//	return state;	
}

/* IRQ Configuration and ISR handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{}
void SPI_IRQHandling(SPI_RegDef_t *pSPIx)
{}

/*
 * Other Peripheral Control APIs
 */
static void SPI_PeriControl(SPI_RegDef_t *pSPIx, uint8_t ENorDIS)
{
	if(ENorDIS == SPI_PERI_ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}
	else
	{
		pSPIx->CR1 &= (uint32_t)~(1 << SPI_CR1_SPE);
	}
}

void SPI_Start(SPI_RegDef_t *pSPIx)
{
	SPI_PeriControl(pSPIx, SPI_PERI_ENABLE);
}
void SPI_Stop(SPI_RegDef_t *pSPIx)
{
	SPI_PeriControl(pSPIx, SPI_PERI_DISABLE);
}

void SPI_SSIConfig(SPI_RegDef_t *pSPIx)
{
	pSPIx->CR1 |= (1<<8);
}
