
/*
* 	file_name  :stm32f407xx_gpio_driver.c
 *	Date			 : Aug 23, 2024
 *  Peripheral :					
 *  Author		 : Thuy
 */
#include <stm32f407xx_gpio_driver.h>


/****************************************************************************
 * @fn	  					- GPIO_PeriClockControl

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
 ****************************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t * pGPIO, uint8_t ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pGPIO == GPIOA_BASE)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIO == GPIOB_BASE)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIO == GPIOC_BASE)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIO == GPIOD_BASE)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIO == GPIOE_BASE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIO == GPIOF_BASE)
		{
			GPIOF_PCLK_EN();
		}
		else if(pGPIO == GPIOG_BASE)
		{
			GPIOG_PCLK_EN();
		}
		else if(pGPIO == GPIOH_BASE)
		{
			GPIOH_PCLK_EN();
		}
		else if(pGPIO == GPIOI_BASE)
		{
			GPIOI_PCLK_EN();
		}	
	}
	else
	{
		if(pGPIO == GPIOA_BASE)
		{
			GPIOA_PCLK_DIS();
		}
		else if(pGPIO == GPIOB_BASE)
		{
			GPIOB_PCLK_DIS();
		}
		else if(pGPIO == GPIOC_BASE)
		{
			GPIOC_PCLK_DIS();
		}
		else if(pGPIO == GPIOD_BASE)
		{
			GPIOD_PCLK_DIS();
		}
		else if(pGPIO == GPIOE_BASE)
		{
			GPIOE_PCLK_DIS();
		}
		else if(pGPIO == GPIOF_BASE)
		{
			GPIOF_PCLK_DIS();
		}
		else if(pGPIO == GPIOG_BASE)
		{
			GPIOG_PCLK_DIS();
		}
		else if(pGPIO == GPIOH_BASE)
		{
			GPIOH_PCLK_DIS();
		}
		else if(pGPIO == GPIOI_BASE)
		{
			GPIOI_PCLK_DIS();
		}	
	}
}


/****************************************************************************
 * @fn	  					- GPIO_Init

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
	uint32_t temp;
	// 1. Configure the mode of the gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// the non interrupt mode
		temp = (uint32_t)(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= (uint32_t)~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= temp;

	}else
	{
		// IRQ mode
		
		if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
//			1. Configure the FTSR
			EXTI_BASE->FTSR |= (1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI_BASE->RTSR &= (uint32_t)~(1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			
		}else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
//			1. Configure the RTSR			
			EXTI_BASE->FTSR &= ~(1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI_BASE->RTSR |= (1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			
		}else if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
//			1. Configure both FTSR and RTSR
			EXTI_BASE->FTSR |= (1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			EXTI_BASE->RTSR |= (1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		}
		
//		2. Configure the GPIOA_BASE port selcection in SYSCFG_EXTICR
		uint8_t tmp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t tmp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		
		uint8_t PortCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_BASE->EXTICR[tmp1] |= (uint32_t)PortCode<<(tmp2*4);
		
//		3. enable the exti interrput delivery using IMR		
		EXTI_BASE->IMR |= (1<<(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	}

	temp = 0;

	// 2. Configure the speed
	temp = (uint32_t)(pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= (uint32_t)~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3. Configure the pull up/pull down settings
	temp = (uint32_t)(pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= (uint32_t)~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4. Configure the optype
	temp = (uint32_t)(pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. Configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTF)
	{
		// configure the alternative function
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] |= (uint32_t)~(0xf<< (4*temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (uint32_t)(pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2));
	}
}


/****************************************************************************
 * @fn	  					- GPIO_DeInit

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIO)
{
	if(pGPIO == GPIOA_BASE)
	{
		GPIOA_REG_RESET();
	}
	else if(pGPIO == GPIOB_BASE)
	{
		GPIOB_REG_RESET();
	}
	else if(pGPIO == GPIOC_BASE)
	{
		GPIOC_REG_RESET();
	}
	else if(pGPIO == GPIOD_BASE)
	{
		GPIOD_REG_RESET();
	}
	else if(pGPIO == GPIOE_BASE)
	{
		GPIOE_REG_RESET();
	}
	else if(pGPIO == GPIOF_BASE)
	{
		GPIOF_REG_RESET();
	}
	else if(pGPIO == GPIOG_BASE)
	{
		GPIOG_REG_RESET();
	}
	else if(pGPIO == GPIOH_BASE)
	{
		GPIOH_REG_RESET();
	}
	else if(pGPIO == GPIOI_BASE)
	{
		GPIOI_REG_RESET();
	}		
	GPIO_PeriClockControl(pGPIO, DISABLE);
}


/****************************************************************************
 * @fn	  					- GPIO_ReadFromInputPin

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	uint8_t PinState;
	PinState = (pGPIO->IDR >>PinNumber)& 0x1;
	return PinState;
}


/****************************************************************************
 * @fn	  					- GPIO_ReadFromInputPort

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO)
{
	_vo uint16_t PortValue = (_vo uint16_t)pGPIO->IDR;
	return PortValue;
}


/****************************************************************************
 * @fn	  					- GPIO_WriteToOutputPin

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t State)
{
	if(State == GPIO_PIN_SET)
	{
		pGPIO->ODR |= (1<< PinNumber);
	}else
	{
		pGPIO->ODR &= ~(1<< PinNumber);
	}
}


/****************************************************************************
 * @fn	  					- GPIO_WriteToOutputPort

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint8_t Value)
{
	pGPIO->ODR |= Value;
}


/****************************************************************************
 * @fn	  					- GPIO_ToggleOutputPin

 * @brief  					- 

 * @param[pGPIO]  	- 
 * @param[ENorDI]  	
 * @param[]  				-

 * @return 					- 

 * @note	  				- 
****************************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	pGPIO->ODR ^= (1<<PinNumber);
}
/* IRQ Configuration and ISR handling */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			// ISER0
			*NVIC_ISER0 |= 1<< IRQNumber ;
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// ISER1
			*NVIC_ISER1 |= 1<< (IRQNumber % 32);
		}
		else if(IRQNumber > 64 && IRQNumber < 96)
		{
			// ISER2
			*NVIC_ISER2 |= 1<< (IRQNumber % 64);
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			// ICER0
			*NVIC_ICER0 |= 1<< IRQNumber ;
		}
		else if(IRQNumber > 31 && IRQNumber < 64)
		{
			// ICER1
			*NVIC_ICER1 |= 1<< (IRQNumber % 32);
		}
		else if(IRQNumber > 64 && IRQNumber < 96)
		{
			// ICER2
			*NVIC_ICER2 |= 1<< (IRQNumber % 64);
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	// find position of the IRQPriority 
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_Section = IRQNumber % 4;
	
	// Clear NVIC_IPR
	*(NVIC_IPR_BASE+iprx) &=  (uint32_t)~(0xff << (iprx_Section*8));
	
	// Set Priority of IRQNumber
	uint8_t shift_amount = (iprx_Section*8) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE + iprx) |=  (uint32_t)(IRQPriority << shift_amount );
}

void GPIO_IRQHandling(uint8_t PinNumber)
{
	// clear the PR flag in EXTI->PR
	if(EXTI_BASE->PR & (1<<PinNumber))
	{
		EXTI_BASE->PR |= (1<<PinNumber);
	}
}
