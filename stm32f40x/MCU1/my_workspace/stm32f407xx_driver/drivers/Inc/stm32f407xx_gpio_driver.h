/*
 * gpio_driver.h
 *
 *  Created on: Aug 23, 2024
 *      Author: THUY
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include <stm32f4xx.h>

/*
 *
 */
typedef struct
{
	uint8_t GPIO_PinNumber;			/* !< possible values from @GPIO_NUMBER > */
	uint8_t GPIO_PinMode; 			/* !< possible values from @GPIO_MODE > */
	uint8_t GPIO_PinSpeed;			/* !< possible values from @GPIO_OP_SPEED > */
	uint8_t GPIO_PinPuPdControl;	/* !< possible values from @@GPIO_PU/PD > */
	uint8_t GPIO_PinOPType;			/* !< possible values from @GPIO_OPTYPE > */
	uint8_t GPIO_PinAltFunMode;		/* !< possible values from @GPIO_AltFunMode > */
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
#define GPIO_PIN_19			10
#define GPIO_PIN_11			11
#define GPIO_PIN_12			12
#define GPIO_PIN_13			13
#define GPIO_PIN_14			14
#define GPIO_PIN_15			15

/* @GPIO_MODE
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTF 		2
#define GPIO_MODE_ANALOG 	3
//#define GPIO_MODE_IT 		4
//#define GPIO_MODE_IT 		5
//#define GPIO_MODE_IT 		6

/* @GPIO_OPTYPE
 * GPIO port output type possible value
 */
#define GPIO_OTYPER_PP		0
#define GPIO_OTYPER_OD		1

/* @GPIO_OP_SPEED
 * GPIO port output speed possible value
 */
#define GPIO_OP_LOW			0
#define GPIO_OP_MEDIUM		1
#define GPIO_OP_HIGH		2
#define GPIO_OP_VHIGH		3

/* @GPIO_PU/PD
 * GPIO port pull-up/pull-down
 */
#define GPIO_NO_PP			0
#define GPIO_PU				1
#define GPIO_PD				2

/*
 *
 */

/*
 * GPIO Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t ENorDI);

/*
 * GPIO Init and DeInit
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIO);

/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIO);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber, uint8_t State);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIO, uint8_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIO, uint8_t PinNumber);
/*
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandler(uint8_t PinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
