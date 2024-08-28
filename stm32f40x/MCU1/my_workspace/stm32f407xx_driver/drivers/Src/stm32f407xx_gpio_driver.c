
/*
 * gpio_driver.c
 *
 *  Created on: Aug 23, 2024
 *      Author: ASUS
 */
#include <stm32f407xx_gpio_driver.h>

/****************************************************************************
 * @fn	  			- GPIO_Init

 * @brief  			- this function Initialization for GPIO

 * @param[pGPIO]  	- base address of the GPIO peripheral
 * @param[ENorDI]  	- Enable or Disable
 * @param[]  		-

 * @return 			- none

 * @note	  		- none
 */
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
 * @fn	  			- GPIO_Init

 * @brief  			- this function Initialization for GPIO

 * @param[pGPIO]  	- base address of the GPIO peripheral
 * @param[ENorDI]  	- Enable or Disable
 * @param[]  		-

 * @return 			- none

 * @note	  		- none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp;
	// 1. Configure the mode of the gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		// the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= temp;

	}else
	{
		// IRQ mode
	}

	temp = 0;

	// 2. Configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3. Configure the pull up/pull down settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	// 4. Configure the optype
	temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	// 5. Configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTF)
	{
		// configure the alternative function
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] |= ~(0xf<< (4*temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*temp2);
	}
}
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
}

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	uint8_t PinState;
	PinState = (pGPIO->IDR >>PinNumber)& 0x1;
	return PinState;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO)
{
	return pGPIO->IDR;
}
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
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint8_t Value)
{
	pGPIO->ODR |= Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber)
{
	pGPIO->ODR ^= (1<<PinNumber);
}
/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi){}
void GPIO_IRQHandler(uint8_t PinNumber){}


