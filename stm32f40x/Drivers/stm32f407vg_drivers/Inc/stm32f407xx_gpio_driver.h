/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 23, 2024
 *  Author     : THUY
 */

#ifndef __STM32F407XX_GPIO_DRIVER_H_
#define __STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f407xx_rcc_driver.h"
/*
 * 
 */
typedef struct
{
	uint8_t GPIO_PinNumber;			     /* !< possible values from @GPIO_NUMBER > */
	uint8_t GPIO_PinMode; 			     /* !< possible values from @GPIO_MODE > */
	uint8_t GPIO_PinSpeed;			     /* !< possible values from @GPIO_OP_SPEED > */
	uint8_t GPIO_PinPuPdControl;	   /* !< possible values from @@GPIO_PU/PD > */
	uint8_t GPIO_PinOPType;			     /* !< possible values from @GPIO_OPTYPE > */
	uint8_t GPIO_PinAltFunMode;		   /* !< possible values from @GPIO_AltFunMode > */
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

/* @GPIO_NUMBER
 * the number of pin in GPIO
 */
#define GPIO_PIN_0			0
#define GPIO_PIN_1			1
#define GPIO_PIN_2			2
#define GPIO_PIN_3			3
#define GPIO_PIN_4			4
#define GPIO_PIN_5			5
#define GPIO_PIN_6			6
#define GPIO_PIN_7			7
#define GPIO_PIN_8			8
#define GPIO_PIN_9			9
#define GPIO_PIN_10			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15

/* @GPIO_MODE
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		  	0
#define GPIO_MODE_OUT 			1
#define GPIO_MODE_ALTF 			2
#define GPIO_MODE_ANALOG 		3
#define GPIO_MODE_IT_FT 		4
#define GPIO_MODE_IT_RT 		5
#define GPIO_MODE_IT_RFT 		6  

/* @GPIO_OPTYPE
 * GPIO port output type possible value
 */
#define GPIO_OTYPER_PP		0
#define GPIO_OTYPER_OD		1

/* @GPIO_OP_SPEED
 * GPIO port output speed possible value
 */
#define GPIO_OP_LOW			  0
#define GPIO_OP_MEDIUM		1
#define GPIO_OP_HIGH		  2
#define GPIO_OP_VHIGH		  3

/* @GPIO_PU/PD
 * GPIO port pull-up/pull-down
 */
#define GPIO_NO_PP			0
#define GPIO_PU				  1
#define GPIO_PD				  2

/**/
#define GPIO_AF_AF0			0
#define GPIO_AF_AF1			1
#define GPIO_AF_AF2			2
#define GPIO_AF_AF3			3
#define GPIO_AF_AF4			4
#define GPIO_AF_AF5			5
#define GPIO_AF_AF6			6
#define GPIO_AF_AF7			7
#define GPIO_AF_AF8			8
#define GPIO_AF_AF9			9
#define GPIO_AF_AF10		10
#define GPIO_AF_AF11		11
#define GPIO_AF_AF12		12
#define GPIO_AF_AF13		13
#define GPIO_AF_AF14		14
#define GPIO_AF_AF15		15

/*
 * BIT POSITION OF RCC
 */
// RCC_AHB1ENR
#define RCC_AHB1ENR_GPIOAENR				0
#define RCC_AHB1ENR_GPIOBENR				1
#define RCC_AHB1ENR_GPIOCENR				2
#define RCC_AHB1ENR_GPIODENR				3
#define RCC_AHB1ENR_GPIOEENR				4
#define RCC_AHB1ENR_GPIOFENR				5
#define RCC_AHB1ENR_GPIOGENR				6
#define RCC_AHB1ENR_GPIOHENR				7
#define RCC_AHB1ENR_GPIOIENR				8

// RCC_APB2ENR
#define RCC_APB2ENR_SYSCFGENR			14

// RCC_AHB1RSTR
#define RCC_AHB1RSTR_GPIOARST				0
#define RCC_AHB1RSTR_GPIOBRST				1
#define RCC_AHB1RSTR_GPIOCRST				2
#define RCC_AHB1RSTR_GPIODRST				3
#define RCC_AHB1RSTR_GPIOERST				4
#define RCC_AHB1RSTR_GPIOFRST				5
#define RCC_AHB1RSTR_GPIOGRST				6
#define RCC_AHB1RSTR_GPIOHRST				7
#define RCC_AHB1RSTR_GPIOIRST				8

// RCC_APB2RSTR
#define RCC_APB1RSTR_ENRSYSCFG				14

/**/
#define GPIO_BASEADDR_TO_CODE(x)			( (x == GPIOA_BASE) ?0:\
																				(x == GPIOB_BASE) ?1:\
																				(x == GPIOC_BASE) ?2:\
																				(x == GPIOD_BASE) ?3:\
																				(x == GPIOE_BASE) ?4:\
																				(x == GPIOF_BASE) ?5:\
																				(x == GPIOG_BASE) ?6:\
																				(x == GPIOH_BASE) ?7:\
																				(x == GPIOI_BASE) ?8:9 )


/****************************************************************************



******************************************************************************/

/*
 * Clock and Reset Control of GPIO
 */

/* Enable Clock for GPIOx */
#define GPIOA_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOAENR)
#define GPIOB_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOBENR)
#define GPIOC_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOCENR)
#define GPIOD_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIODENR)
#define GPIOE_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOEENR)
#define GPIOF_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOFENR)
#define GPIOG_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOGENR)
#define GPIOH_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOHENR)
#define GPIOI_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << RCC_AHB1ENR_GPIOIENR)

/* Enable Clock for SYSCFG*/
#define SYSCFG_PCLK_EN()			RCC_BASE->APB2ENR |= (1 << RCC_APB2ENR_SYSCFGENR)

/* Disable Clock for GPIOx */
#define GPIOA_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOAENR)
#define GPIOB_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOBENR)
#define GPIOC_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOCENR)
#define GPIOD_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIODENR)
#define GPIOE_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOEENR)
#define GPIOF_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOFENR)
#define GPIOG_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOGENR)
#define GPIOH_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOHENR)
#define GPIOI_PCLK_DIS() 			RCC_BASE->AHB1ENR &= (uint32_t)~(1 << RCC_AHB1ENR_GPIOIENR)

/* Disable Clock for SYSCFG*/
#define SYSCFG_PCLK_DIS()			RCC_BASE->APB2ENR &= (uint32_t)~(1 << RCC_APB2ENR_SYSCFGENR)

/*
 * Macro to reset GPIOx peripheral
 */
#define GPIOA_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOARST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOARST);}while(0)
#define GPIOB_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOBRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOBRST);}while(0)
#define GPIOC_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOCRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOCRST);}while(0)
#define GPIOD_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIODRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIODRST);}while(0)
#define GPIOE_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOERST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOERST);}while(0)
#define GPIOF_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOFRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOFRST);}while(0)
#define GPIOG_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOGRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOGRST);}while(0)
#define GPIOH_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOHRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOHRST);}while(0)
#define GPIOI_REG_RESET()			do{RCC_BASE->AHB1RSTR |= (1<<RCC_AHB1RSTR_GPIOIRST); RCC_BASE->AHB1RSTR &= (uint32_t)~(1<<RCC_AHB1RSTR_GPIOIRST);}while(0)

/* Disable Clock for SYSCFG*/
#define SYSCFG_REG_RESET()		do{RCC_BASE->APB2RSTR |= (1<<RCC_APB2RSTR_SYSCFG); RCC_BASE->APB2RSTR &= (uint32_t)~(1<<RCC_APB2RSTR_SYSCFG);}while(0)


/* GPIO Peripheral Clock setup */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t ENorDI);

/* GPIO Init and DeInit */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIO);

/* Data read and write */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t State);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);

/* IRQ Configuration and ISR handling */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

/*
 * Other Configure function
 */
void GPIO_DigitalOutputConfig(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
void GPIO_DigitalInputConfig(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);

#endif /* __STM32F407XX_GPIO_DRIVER_H_ */
