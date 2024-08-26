#ifndef __STM32F103XX_H
#define __STM32F103XX_H

#include "stdint.h"
#include "CortexM3.h"


/* base addresses of Flash and SRAM memories */
#define FLASH_BASEADDR            0x08000000UL /*!< FLASH BASEADDR address in the alias region */
#define FLASH_BANK1_END       		0x0801FFFFUL /*!< FLASH END address of bank1 */

	
// bus base Address
#define APB1_BASEADDR							 PERI_BASEADDR
#define APB2_BASEADDR							(PERI_BASEADDR + 0x10000)
#define AHB_BASEADDR							(PERI_BASEADDR + 0x18000)

/* Peripheral base address of APB1 */

/* Peripheral base address of APB2 */
#define GPIOA_BASEADDR  (APB2_BASEADDR + 0x0800)
#define GPIOB_BASEADDR  (APB2_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR  (APB2_BASEADDR + 0x1000)

/* Peripheral base address of AHB */
#define RCC_BASEADDR		(0x40021000)


/* STRUCTURE OF PERIPHERAL */
typedef struct
{
	_vo uint32_t CR[2];
	_vo uint32_t IDR;
	_vo uint32_t ODR;
	_vo uint32_t BSRR;
	_vo uint32_t BRR;
	_vo uint32_t LCKR;
}GPIO_RegDef_t;

typedef struct
{
	_vo uint32_t CR;
	_vo uint32_t CFGR;
	_vo uint32_t CIR;
	_vo uint32_t APB2RSTR;
	_vo uint32_t APB1RSTR;
	_vo uint32_t AHBENR;
	_vo uint32_t APB2ENR;
	_vo uint32_t APB1ENR;
	_vo uint32_t BDCR;
	_vo uint32_t CSR;
}RCC_RegDef_t;



/*!< Peripheral declaration */
#define GPIOA_BASEPTR			(GPIO_RegDef_t*)GPIOA_BASEADDR
#define GPIOB_BASEPTR			(GPIO_RegDef_t*)GPIOB_BASEADDR
#define GPIOC_BASEPTR			(GPIO_RegDef_t*)GPIOC_BASEADDR

#define RCC_BASEPTR				(RCC_RegDef_t *)RCC_BASEADDR



#endif
