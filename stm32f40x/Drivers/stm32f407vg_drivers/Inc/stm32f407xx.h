/*
 *  stm32f4xx.h
 *
 *  Created on: Aug 20, 2024
 *  Author: ASUS
 */

#ifndef __STM32F4XX_H_
#define __STM32F4XX_H_


#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

/* Include */
#include "CortexMx.h"
#include "CortexMx_BitBand.h"
#include "CortexMx_NVIC.h"
#include "CortexMx_SysTick_Timer.h"

#define HIGH		1
#define LOW			0



#define FLAG_SET	SET
#define FLAG_RESET	RESET

/* base addresses of Flash and SRAM memories */

#define NO_PR_BITS_IMPLEMENTED 					4          /* <! The Number of Bits used to Configure Priority IRQ > */

#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U
#define SRAM2_BASEADDR			(SRAM1_BASEADDR+112*1024)
#define ROM_BASEADDR				0x1FFF0000U
#define SRAM								SRAM1_BASEADDR

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
#define I2C1_BASEADDR				(APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR				(APB1PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR				(APB1PERIPH_BASE + 0x5C00)

#define SPI2_BASEADDR				(APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR				(APB1PERIPH_BASE + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASE + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASE + 0x4800)

#define UART4_BASEADDR			(APB1PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR			(APB1PERIPH_BASE + 0x5000)


/*
 * Address of peripheral in APB2
 */

#define SPI1_BASEADDR			  (APB2PERIPH_BASE + 0x3000)

#define USART1_BASEADDR			(APB2PERIPH_BASE + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASE + 0x1400)

#define EXTI_BASEADDR			  (APB2PERIPH_BASE + 0x3C00)

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
	_vo uint32_t EXTICR[4];
	uint32_t		 Reserved[2];
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
	uint32_t     Reserved0;
	_vo uint32_t APB1RSTR;
	_vo uint32_t APB2RSTR;
	uint32_t   Reserved1;
	uint32_t   Reserved2;
	_vo uint32_t AHB1ENR;
	_vo uint32_t AHB2ENR;
	_vo uint32_t AHB3ENR;
	uint32_t   Reserved3;
	_vo uint32_t APB1ENR;
	_vo uint32_t APB2ENR;
	uint32_t   Reserved4;
	uint32_t   Reserved5;
	_vo uint32_t AHB1LPENR;
	_vo uint32_t AHB2LPENR;
	_vo uint32_t AHB3LPENR;
	uint32_t   Reserved6;
	_vo uint32_t APB1LPENR;
	_vo uint32_t APB2LPENR;
	uint32_t   Reserved7;
	uint32_t   Reserved8;
	_vo uint32_t BDCR;
	_vo uint32_t CSR;
	uint32_t   Reserved9;
	uint32_t   Reserved10;
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

/* Define some general Macro */
#define ENABLE							1
#define DISABLE							0

#define SET									ENABLE
#define RESET								DISABLE

#define GPIO_PIN_SET				ENABLE
#define GPIO_PIN_RESET			DISABLE

#define GPIOA_BASE				((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB_BASE				((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC_BASE				((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD_BASE				((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE_BASE				((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF_BASE				((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG_BASE				((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH_BASE				((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI_BASE				((GPIO_RegDef_t *)GPIOI_BASEADDR)

#define EXTI_BASE					((EXTI_RegDef_t *)EXTI_BASEADDR)

#define SYSCFG_BASE				((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)

#define RCC_BASE				  ((RCC_RegDef_t *)RCC_BASEADDR)



#define I2C1_BASE					((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C2_BASE					((I2C_RegDef_t *)I2C2_BASEADDR)
#define I2C3_BASE					((I2C_RegDef_t *)I2C3_BASEADDR)

#define SPI1_BASE					((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2_BASE					((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3_BASE					((SPI_RegDef_t *)SPI3_BASEADDR)


#define USART1_BASE				((USART_RegDef_t *)USART1_BASEADDR)		
#define USART2_BASE				((USART_RegDef_t *)USART2_BASEADDR)
#define USART3_BASE				((USART_RegDef_t *)USART3_BASEADDR)
#define UART4_BASE				((USART_RegDef_t *)UART4_BASEADDR)
#define UART5_BASE				((USART_RegDef_t *)UART5_BASEADDR)
#define USART6_BASE				((USART_RegDef_t *)USART6_BASEADDR)





/* Enable Clock for I2Cx */
//#define I2C1_PCLK_EN
//#define I2C2_PCLK_EN
//#define I2C3_PCLK_EN








/* Disable Clock for I2Cx */
//#define I2C1_PCLK_DIS
//#define I2C2_PCLK_DIS
//#define I2C3_PCLK_DIS







/*
 * @VECTOR_TABLE
 */

#define IRQNO_EXTI0                 IRQ6
#define IRQNO_EXTI1                 IRQ7
#define IRQNO_EXTI2                 IRQ8
#define IRQNO_EXTI3                 IRQ9
#define IRQNO_EXTI4                 IRQ10
#define IRQNO_EXTI9_5               IRQ30
#define IRQNO_EXTI15_10             IRQ40


/*
#define                  IRQ0
#define                  IRQ1
#define                  IRQ2
#define                  IRQ3
#define                  IRQ4
#define                  IRQ5

#define                  IRQ11
#define                  IRQ12
#define                  IRQ13
#define                  IRQ14
#define                  IRQ15
#define                  IRQ16
#define                  IRQ17
#define                  IRQ18
#define                  IRQ19
#define                  IRQ20
#define                  IRQ21
#define                  IRQ22
#define                  IRQ23
#define                  IRQ24
#define                  IRQ25
#define                  IRQ26
#define                  IRQ27
#define                  IRQ28
#define                  IRQ29

#define                  IRQ31
#define                  IRQ32
#define                  IRQ33
#define                  IRQ34
#define                  IRQ35
#define                  IRQ36
#define                  IRQ37
#define                  IRQ38
#define                  IRQ39

#define                  IRQ41
#define                  IRQ42
#define                  IRQ43
#define                  IRQ44
#define                  IRQ45
#define                  IRQ46
#define                  IRQ47
#define                  IRQ48
#define                  IRQ49
#define                  IRQ50
#define                  IRQ51
#define                  IRQ52
#define                  IRQ53
#define                  IRQ54
#define                  IRQ55
#define                  IRQ56
#define                  IRQ57
#define                  IRQ58
#define                  IRQ59
#define                  IRQ60
#define                  IRQ61
#define                  IRQ62
#define                  IRQ63
#define                  IRQ64
#define                  IRQ65
#define                  IRQ66
#define                  IRQ67
#define                  IRQ68
#define                  IRQ69
#define                  IRQ70
#define                  IRQ71
#define                  IRQ72
#define                  IRQ73
#define                  IRQ74
#define                  IRQ75
#define                  IRQ76
#define                  IRQ77
#define                  IRQ78
#define                  IRQ79
#define                  IRQ80
#define                  IRQ81
#define                  IRQ82
#define                  IRQ83
#define                  IRQ84
#define                  IRQ85
#define                  IRQ86
#define                  IRQ87
#define                  IRQ88
#define                  IRQ89
#define                  IRQ90
#define                  IRQ91
#define                  IRQ92
#define                  IRQ93
#define                  IRQ94
#define                  IRQ95
#define                  IRQ96
#define                  IRQ97
#define                  IRQ98
#define                  IRQ99
#define                  IRQ100
#define                  IRQ101
#define                  IRQ102
#define                  IRQ103
#define                  IRQ104
#define                  IRQ105
#define                  IRQ106
#define                  IRQ107
#define                  IRQ108
#define                  IRQ109
#define                  IRQ110
#define                  IRQ111
#define                  IRQ112
#define                  IRQ113
#define                  IRQ114
#define                  IRQ115
#define                  IRQ116
#define                  IRQ117
#define                  IRQ118
#define                  IRQ119
#define                  IRQ120
#define                  IRQ121
#define                  IRQ122
#define                  IRQ123
#define                  IRQ124
#define                  IRQ125
#define                  IRQ126
#define                  IRQ127
#define                  IRQ128
#define                  IRQ129
#define                  IRQ130
#define                  IRQ131
#define                  IRQ132
#define                  IRQ133
#define                  IRQ134
#define                  IRQ135
#define                  IRQ136
#define                  IRQ137
#define                  IRQ138
#define                  IRQ139
#define                  IRQ140
#define                  IRQ141
#define                  IRQ142
#define                  IRQ143
#define                  IRQ144
#define                  IRQ145
#define                  IRQ146
#define                  IRQ147
#define                  IRQ148
#define                  IRQ149
#define                  IRQ150
#define                  IRQ151
#define                  IRQ152
#define                  IRQ153
#define                  IRQ154
#define                  IRQ155
#define                  IRQ156
#define                  IRQ157
#define                  IRQ158
#define                  IRQ159
#define                  IRQ160
#define                  IRQ161
#define                  IRQ162
#define                  IRQ163
#define                  IRQ164
#define                  IRQ165
#define                  IRQ166
#define                  IRQ167
#define                  IRQ168
#define                  IRQ169
#define                  IRQ170
#define                  IRQ171
#define                  IRQ172
#define                  IRQ173
#define                  IRQ174
#define                  IRQ175
#define                  IRQ176
#define                  IRQ177
#define                  IRQ178
#define                  IRQ179
#define                  IRQ180
#define                  IRQ181
#define                  IRQ182
#define                  IRQ183
#define                  IRQ184
#define                  IRQ185
#define                  IRQ186
#define                  IRQ187
#define                  IRQ188
#define                  IRQ189
#define                  IRQ190
#define                  IRQ191
#define                  IRQ192
#define                  IRQ193
#define                  IRQ194
#define                  IRQ195
#define                  IRQ196
#define                  IRQ197
#define                  IRQ198
#define                  IRQ199
#define                  IRQ200
#define                  IRQ201
#define                  IRQ202
#define                  IRQ203
#define                  IRQ204
#define                  IRQ205
#define                  IRQ206
#define                  IRQ207
#define                  IRQ208
#define                  IRQ209
#define                  IRQ210
#define                  IRQ211
#define                  IRQ212
#define                  IRQ213
#define                  IRQ214
#define                  IRQ215
#define                  IRQ216
#define                  IRQ217
#define                  IRQ218
#define                  IRQ219
#define                  IRQ220
#define                  IRQ221
#define                  IRQ222
#define                  IRQ223
#define                  IRQ224
#define                  IRQ225
#define                  IRQ226
#define                  IRQ227
#define                  IRQ228
#define                  IRQ229
#define                  IRQ230
#define                  IRQ231
#define                  IRQ232
#define                  IRQ233
#define                  IRQ234
#define                  IRQ235
#define                  IRQ236
#define                  IRQ237
#define                  IRQ238
#define                  IRQ239
*/


#endif /* __STM32F4XX_H_ */
