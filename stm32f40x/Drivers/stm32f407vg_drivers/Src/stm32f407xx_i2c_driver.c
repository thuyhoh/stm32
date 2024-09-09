/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#include "stm32f407xx_i2c_driver.h"

/* Peripheral Clock setup */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{ 
		if(pI2Cx == I2C1_BASE)
		{
			I2C1_PCLK_EN();
		}else if(pI2Cx == I2C2_BASE)
		{
			I2C2_PCLK_EN();
		}else if(pI2Cx == I2C3_BASE)
		{
			I2C3_PCLK_EN();
		}else
		{
			// error
		}
	}else
	{
		if(pI2Cx == I2C1_BASE)
		{
			I2C1_PCLK_DIS();
		}else if(pI2Cx == I2C2_BASE)
		{
			I2C2_PCLK_DIS();
		}else if(pI2Cx == I2C3_BASE)
		{
			I2C3_PCLK_DIS();
		}else
		{
			// error
		}
	}
}

/* I2C Init and DeInit */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	
}
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	
}

/* Receive and Transmit Data  */
void I2C_SendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t len);
void I2C_ReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t len);


/* IRQ Configuration and ISR handling */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{
	NVIC_IRQConfig(IRQNumber, ENABLE);
	NVIC_IRQPriorityConfig(IRQNumber, IRQPriority);
}
void I2C_IRQHandling(I2C_Handle_t *pI2CHandle)
{
	
}

/*
 * Other Peripheral Control APIs
 */
void I2C_PeriControl(SPI_RegDef_t *pSPIx, uint8_t ENorDIS)
{
	if(ENorDIS == ENABLE)
	{
		
	}else 
	{
		
	}
}
void I2C_PinConfig(I2C_RegDef_t *pI2Cx, uint8_t I2C_DeviceMode)
{
}
