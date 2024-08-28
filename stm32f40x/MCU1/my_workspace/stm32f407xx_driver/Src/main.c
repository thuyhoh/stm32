/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f407xx_gpio_driver.h"

void delay(uint32_t times)
{
	while(times)
	{
		times--;
	}
}

int main(void)
{
	GPIO_Handle_t pGPIOLed;
	pGPIOLed.pGPIOx = GPIOD_BASE;
	pGPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
	pGPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	pGPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTYPER_PP;
	pGPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PP;
	pGPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_HIGH;

	GPIO_PeriClockControl(pGPIOLed.pGPIOx, ENABLE);
	GPIO_Init(&pGPIOLed);


    /* Loop forever */
	while(1)
	{
		GPIO_ToggleOutputPin(pGPIOLed.pGPIOx, pGPIOLed.GPIO_PinConfig.GPIO_PinNumber);
		delay(10000);
	}
}
