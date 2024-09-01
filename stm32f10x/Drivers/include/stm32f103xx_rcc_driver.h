#ifndef _STM32F103XX_RCC_DRIVE_H
#define _STM32F103XX_RCC_DRIVE_H

#include "stm32f103xx.h"
#include "stdint.h"

/* Macro */
#define CLOCK_ENABLE				1
#define CLOCK_DISABLE				0

/* Peripheral Clock Enable */
#define GPIOA_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<2)
#define GPIOB_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<3)
#define GPIOC_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<4)

#define AFIO_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<0)

#define SPI1_PCLK_ENABLE()				RCC_BASEPTR->APB2ENR |= (1<<12)
#define SPI2_PCLK_ENABLE()				RCC_BASEPTR->APB1ENR |= (1<<14)
#define SPI3_PCLK_ENABLE()				RCC_BASEPTR->APB1ENR |= (1<<15)

/* Peripheral Clock Disable */
#define GPIOA_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<2)
#define GPIOB_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<3)
#define GPIOC_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<4)

#define AFIO_PCLK_DISABLE()				  RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<0)

#define SPI1_PCLK_DISABLE()				RCC_BASEPTR->APB2ENR &= (uint32_t)~(1<<12)
#define SPI2_PCLK_DISABLE()				RCC_BASEPTR->APB1ENR &= (uint32_t)~(1<<14)
#define SPI3_PCLK_DISABLE()				RCC_BASEPTR->APB1ENR &= (uint32_t)~(1<<15)

/* Pheripheral Register Reset */
#define GPIOA_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<2); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<2);}while(0)
#define GPIOB_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<3); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<3);}while(0)
#define GPIOC_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<4); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<4);}while(0)

#define AFIO_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<0); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<0);}while(0)

#define SPI1_REG_RESET()						do{RCC_BASEPTR->APB2RSTR |= (1<<12); RCC_BASEPTR->APB2RSTR &= (uint32_t)~(1<<12);}while(0)
#define SPI2_REG_RESET()						do{RCC_BASEPTR->APB1RSTR |= (1<<14); RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1<<14);}while(0)
#define SPI3_REG_RESET()						do{RCC_BASEPTR->APB1RSTR |= (1<<15); RCC_BASEPTR->APB1RSTR &= (uint32_t)~(1<<15);}while(0)


#endif
