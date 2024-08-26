#include "stm32f103xx_gpio_drive.h"

/****************************************************************************
 * @fn	  				-  GPIO_PeriClockControl

 * @brief  				-  GPIO Peripheral Clock setup 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
static void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t EnorDis)
{
	static RCC_RegDef_t *pRCC = RCC_BASEPTR;
	if(EnorDis == ENABLE)
	{
		if(pGPIO == GPIOA_BASEPTR)
		{
			pRCC->APB2ENR |= (1<<2);
		}else if(pGPIO == GPIOB_BASEPTR)
		{
			pRCC->APB2ENR |= (1<<3);
		}else if(pGPIO == GPIOC_BASEPTR)
		{
			pRCC->APB2ENR |= (1<<4);
		}
	}else
	{
		if(pGPIO == GPIOA_BASEPTR)
		{
			pRCC->APB2ENR &= (uint32_t)~(1<<2);
		}else if(pGPIO == GPIOB_BASEPTR)
		{
			pRCC->APB2ENR &= (uint32_t)~(1<<3);
		}else if(pGPIO == GPIOC_BASEPTR)
		{
			pRCC->APB2ENR &= (uint32_t)~(1<<4);
		}
	}
}

/****************************************************************************
 * @fn	  				-			GPIO_Init

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
	GPIO_PeriClockControl(pGPIO_Handle->pGPIO,ENABLE);
	 
	if(pGPIO_Handle->GPIO_Config.PinMode != GPIO_IT_MODE)
	{
		uint8_t tmp1 = pGPIO_Handle->GPIO_Config.PinNumber / 8;
		uint8_t tmp2 = pGPIO_Handle->GPIO_Config.PinNumber % 8;
		uint32_t tmp = (uint32_t)(pGPIO_Handle->GPIO_Config.PinMode << (tmp2*4));
		pGPIO_Handle->pGPIO->CR[tmp1] |= tmp;
	}else
	{
		// IRQ mode
	}
}

/****************************************************************************
 * @fn	  				- 			GPIO_DeInit

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIO)
{
	static RCC_RegDef_t *pRCC = RCC_BASEPTR;
	if(pGPIO == GPIOA_BASEPTR)
	{
		pRCC->APB2RSTR |= (1<<2);
		pRCC->APB2RSTR &= (uint32_t)~(1<<2);
	}else if(pGPIO == GPIOB_BASEPTR)
	{
		pRCC->APB2RSTR |= (1<<3);
		pRCC->APB2RSTR &= (uint32_t)~(1<<3);
	}else if(pGPIO == GPIOC_BASEPTR)
	{
		pRCC->APB2RSTR |= (1<<4);
		pRCC->APB2RSTR &= (uint32_t)~(1<<4);
	}
}

/****************************************************************************
 * @fn	  				- 			GPIO_ReadFromInputPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	_vo uint8_t PinState = (uint8_t)(pGPIO->IDR >> PinNumber)&0x1;
	return PinState;
}

/****************************************************************************
 * @fn	  				- 		GPIO_ReadFromInputPort

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO)
{
	_vo uint16_t PortState = (uint16_t)pGPIO->IDR;
	return PortState;
}

/****************************************************************************
 * @fn	  				- 			GPIO_WriteToOutputPin

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t PinState)
{
	if(PinState == SET)
	{
		pGPIO->ODR |= 1<<PinNumber;
	}else
	{
		pGPIO->ODR &= (uint32_t)~(1<<PinNumber);
	}
}

/****************************************************************************
 * @fn	  				- 			GPIO_WriteToOutputPort

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint16_t PortState)
{
	pGPIO->ODR |= PortState;
}

/****************************************************************************
 * @fn	  				- 			GPIO_ToggleOutputPin	

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	pGPIO->ODR ^= (1<<PinNumber);
}

/****************************************************************************
 * @fn	  				- 					GPIO_IRQConfig

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi){}
	
/****************************************************************************
 * @fn	  				- 					GPIO_IRQHandler

 * @brief  				- 

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/	
void GPIO_IRQHandler(uint8_t PinNumber){}
