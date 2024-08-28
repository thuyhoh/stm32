/*
 * stm32f4xx.h
 *
 *  Created on: Aug 20, 2024
 *      Author: ASUS
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_

#include <stdint.h>

/*
 * base addresses of Flash and SRAM memories
 */

#define _vo						volatile

#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U
#define SRAM2_BASEADDR			(SRAM1_BASEADDR+112*1024)
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM					SRAM1_BASEADDR

/*
 * AHBx and APBx bus Peripheral base address
 */

#define AHB1PERIPH_BASE			0x40020000U
#define APB1PERIPH_BASE			0x40000000U
#define AHB2PERIPH_BASE			0x50000000U
#define APB2PERIPH_BASE			0x40010000U

/*
 * Address of peripheral in AHB1
 */

#define GPIOA_BASEADDR			(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASE + 0x2000)

#define RCC_BASEADDR			(AHB1PERIPH_BASE + 0x3800)

/*
 *	Address of peripheral in APB1
 */
#define I2C1_BASEADDR			(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR			(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR			(APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASE + 0x4800)

#define UART4_BASEADDR			(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASE + 0x5000)


/*
 * Address of peripheral in APB2
 */

#define SPI1_BASEADDR			(APB2PERIPH_BASE + 0x3000)

#define USART1_BASEADDR			(APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASE + 0x1400)

#define EXTI_BASEADDR			(APB2PERIPH_BASE + 0x3C00)

#define SYSCFG_BASEADDR			(APB2PERIPH_BASE + 0x3800)




/*
 *	Define Register of Peripheral
 */
typedef struct
{
	_vo uint32_t MODER;
	_vo uint32_t OTYPER;
	_vo uint32_t OSPEEDR;
	_vo uint32_t PUPDR;
	_vo uint32_t IDR;
	_vo uint32_t ODR;
	_vo uint32_t BSRR;
	_vo uint32_t LCKR;
	_vo uint32_t AFR[2];
}GPIO_RegDef_t;

typedef struct
{
	_vo uint32_t IMR;
	_vo uint32_t EMR;
	_vo uint32_t RTSR;
	_vo uint32_t FTSR;
	_vo uint32_t SWIER;
	_vo uint32_t PR;
}EXTI_RegDef_t;

typedef struct
{
	_vo uint32_t MEMRMP;
	_vo uint32_t PMC;
	_vo uint32_t EXTICR1;
	_vo uint32_t EXTICR2;
	_vo uint32_t EXTICR3;
	_vo uint32_t EXTICR4;
	_vo uint32_t CMPCR;
}SYSCFG_RegDef_t;
/*
 *
 */
typedef struct
{
	_vo uint32_t PLLCFGR;
	_vo uint32_t CR;
	_vo uint32_t CFGR;
	_vo uint32_t CIR;
	_vo uint32_t AHB1RSTR;
	_vo uint32_t AHB2RSTR;
	_vo uint32_t AHB3RSTR;
	_vo uint32_t Reserved0;
	_vo uint32_t APB1RSTR;
	_vo uint32_t APB2RSTR;
	_vo uint32_t Reserved1;
	_vo uint32_t Reserved2;
	_vo uint32_t AHB1ENR;
	_vo uint32_t AHB2ENR;
	_vo uint32_t AHB3ENR;
	_vo uint32_t Reserved3;
	_vo uint32_t APB1ENR;
	_vo uint32_t APB2ENR;
	_vo uint32_t Reserved4;
	_vo uint32_t Reserved5;
	_vo uint32_t AHB1LPENR;
	_vo uint32_t AHB2LPENR;
	_vo uint32_t AHB3LPENR;
	_vo uint32_t Reserved6;
	_vo uint32_t APB1LPENR;
	_vo uint32_t APB2LPENR;
	_vo uint32_t Reserved7;
	_vo uint32_t Reserved8;
	_vo uint32_t BDCR;
	_vo uint32_t CSR;
	_vo uint32_t Reserved9;
	_vo uint32_t Reserved10;
	_vo uint32_t SSCGR;
	_vo uint32_t PLLI2SCFGR;
}RCC_RegDef_t;

typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t SR;
	_vo uint32_t DR;
	_vo uint32_t CRCPR;
	_vo uint32_t RXCRCR;
	_vo uint32_t TXCCRCR;
	_vo uint32_t I2SCFGR;
	_vo uint32_t I2SPR;
}SPI_RegDef_t;

typedef struct
{
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t OAR1;
	_vo uint32_t OAR2;
	_vo uint32_t DR;
	_vo uint32_t SR1;
	_vo uint32_t SR2;
	_vo uint32_t CCR;
	_vo uint32_t TRISE;
	_vo uint32_t FLTR;
}I2C_RegDef_t;

typedef struct
{
	_vo uint32_t SR;
	_vo uint32_t DR;
	_vo uint32_t BRR;
	_vo uint32_t CR1;
	_vo uint32_t CR2;
	_vo uint32_t CR3;
	_vo uint32_t GTPR;
}USART_RegDef_t;


/*
 *	base ptr of peripheral
 */

#define GPIOA_BASE				((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB_BASE				((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC_BASE				((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD_BASE				((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE_BASE				((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF_BASE				((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG_BASE				((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH_BASE				((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI_BASE				((GPIO_RegDef_t *)GPIOI_BASEADDR)

#define RCC_BASE				((RCC_RegDef_t *)RCC_BASEADDR)

//#define I2C1_BASE
//#define I2C2_BASE
//#define I2C3_BASE

//#define SPI1_BASE
//#define SPI2_BASE
//#define SPI3_BASE
//#define SPI4_BASE
//#define SPI5_BASE
//#define SPI6_BASE

//#define USART1_BASE
//#define USART2_BASE
//#define USART3_BASE
//#define UART4_BASE
//#define UART5_BASE
//#define USART6_BASE

/* Enable Clock for GPIOx */
#define GPIOA_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 0)
#define GPIOB_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 1)
#define GPIOC_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 2)
#define GPIOD_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 3)
#define GPIOE_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 4)
#define GPIOF_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 5)
#define GPIOG_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 6)
#define GPIOH_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 7)
#define GPIOI_PCLK_EN() 			RCC_BASE->AHB1ENR |= (1 << 8)

/* Enable Clock for I2Cx */
//#define I2C1_PCLK_EN
//#define I2C2_PCLK_EN
//#define I2C3_PCLK_EN

/* Enable Clock for SPIx */
//#define SPI1_PCLK_EN
//#define SPI2_PCLK_EN
//#define SPI3_PCLK_EN
//#define SPI4_PCLK_EN
//#define SPI5_PCLK_EN
//#define SPI6_PCLK_EN

/* Enable Clock for USARTx */
//#define USART1_PCLK_EN
//#define USART2_PCLK_EN
//#define USART3_PCLK_EN
//#define UART4_PCLK_EN
//#define UART5_PCLK_EN
//#define USART6_PCLK_EN

/* Disable Clock for GPIOx */
#define GPIOA_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 0)
#define GPIOB_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 1)
#define GPIOC_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 2)
#define GPIOD_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 3)
#define GPIOE_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 4)
#define GPIOF_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 5)
#define GPIOG_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 6)
#define GPIOH_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 7)
#define GPIOI_PCLK_DIS() 			RCC_BASE->AHB1ENR &= ~(1 << 8)

/* Disable Clock for I2Cx */
//#define I2C1_PCLK_DIS
//#define I2C2_PCLK_DIS
//#define I2C3_PCLK_DIS

/* Disable Clock for SPIx */
//#define SPI1_PCLK_DIS
//#define SPI2_PCLK_DIS
//#define SPI3_PCLK_DIS
//#define SPI4_PCLK_DIS
//#define SPI5_PCLK_DIS
//#define SPI6_PCLK_DIS

/* Disable Clock for USARTx */
//#define USART1_PCLK_DIS
//#define USART2_PCLK_DIS
//#define USART3_PCLK_DIS
//#define UART4_PCLK_DIS
//#define UART5_PCLK_DIS
//#define USART6_PCLK_DIS

/* Define some general Macro */
#define ENABLE					1
#define DISABLE					0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			ENABLE
#define GPIO_PIN_RESET			DISABLE

#endif /* INC_STM32F4XX_H_ */
