#ifndef __STM32F103x8_H
#define __STM32F103x8_H

#include "stdint.h"
#define _vo volatile

/* base addresses of Flash and SRAM memories */
#define FLASH_BASEADDR            0x08000000UL /*!< FLASH BASEADDR address in the alias region */
#define FLASH_BANK1_END       		0x0801FFFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASEADDR							0x20000000UL /*!< SRAM BASE ADDRESS >*/
#define PERI_BASEADDR							0x40000000UL
	
// bus base Address
#define APB1_BASEADDR							PERI_BASEADDR
#define APB2_BASEADDR							(PERI_BASEADDR + 0x10000)
#define AHB_BASEADDR							(PERI_BASEADDR + 0x18000)

/* Peripheral base address of APB1 */

/* Peripheral base address of APB2 */
#define GPIOA_BASEADDR  (APB2_BASEADDR + 0x0800)
#define GPIOB_BASEADDR  (APB2_BASEADDR + 0x0C00)
#define GPIOC_BASEADDR  (APB2_BASEADDR + 0x1000)

/* Peripheral base address of AHB */
#define RCC_BASEADDR		(AHB_BASEADDR + 0x3000)


/* STRUCTURE OF PERIPHERAL */
typedef struct
{
	_vo uint32_t CRL;
	_vo uint32_t CRH;
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
#define GPIOA_BASE			(GPIO_RegDef_t*)GPIOA_BASEADDR
#define GPIOB_BASE			(GPIO_RegDef_t*)GPIOB_BASEADDR
#define GPIOC_BASE			(GPIO_RegDef_t*)GPIOC_BASEADDR

#define RCC_BASE				(RCC_RegDef_t *)RCC_BASEADDR

#endif