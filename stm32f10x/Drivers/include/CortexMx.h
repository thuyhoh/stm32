#ifndef __CortexMX_H_
#define __CortexMX_H_

#include "stdint.h"

#define _vo 																								volatile
#define _noreturn																						__attribute__((noreturn))

/* BIT BANDING */
#include "CortexMx_BitBand.h"

#define SRAM_BASEADDR																				0x20000000UL /*!< SRAM BASE ADDRESS >*/
#define SRAM_ALIAS_BASEADDR																	0x22000000U

#define PERI_BASEADDR																				0x40000000UL /*!< PHERIPHERAL BASE ADDRESS >*/
#define PERI_ALIAS_BASEADDR																	0x42000000UL


/* Systick Timer */
#include "CortexMx_SysTick_Timer.h"

#define SYSTICK_BASEADDR																			0xE000E010u

typedef struct 
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;
}SysTick_RegDef_t;																							

#define SYSTICK_BASEPTR																				(SysTick_RegDef_t *)SYSTICK_BASEADDR


/* NVIC */
#include "CortexMx_NVIC.h"

/* base address of NVIC */
#define NVIC_ICTR_BASE																	((_vo uint32_t *)0xE000E004U)
 
#define NVIC_ISER_BASE																	((_vo uint32_t *)0xE000E100U)

#define NVIC_ICER_BASE																	((_vo uint32_t *)0xE000E180U)

#define NVIC_ISPR_BASE																	((_vo uint32_t *)0xE000E200U)

#define NVIC_ICPR_BASE																	((_vo uint32_t *)0xE000E280U)

#define NVIC_IABR_BASE																	((_vo uint32_t *)0xE000E300U)

#define NVIC_IPR_BASE																		((_vo uint32_t *)0xE000E400U)	



void Switch_SpToPSP(void);

#endif	/* __CortexMX_H_ */
