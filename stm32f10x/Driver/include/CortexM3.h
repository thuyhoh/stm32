#ifndef __CortexM3_H
#define __CortexM3_H

#include "stdint.h"

#define _vo 																								volatile



/* BIT BANDING */
#define SRAM_BASEADDR																				0x20000000UL /*!< SRAM BASE ADDRESS >*/
#define SRAM_ALIAS_BASEADDR																	0x22000000U

#define PERI_BASEADDR																				0x40000000UL /*!< PHERIPHERAL BASE ADDRESS >*/
#define PERI_ALIAS_BASEADDR																	0x42000000UL

#define ALIAS_SRAM_ADDRESS(SRAM_addr, bitNo)							 	(SRAM_ALIAS_BASEADDR + (((SRAM_addr) - SRAM_BASEADDR)*32) + ((bitNo) * 4))
#define ALIAS_PERI_ADDRESS(PERI_addr, bitNo)				 			 	(PERI_ALIAS_BASEADDR + (((PERI_addr) - PERI_BASEADDR)*32) + ((bitNo) * 4))

#define ALIAS_SRAM_POINTER(SRAM_addr, bitNo)								(uint8_t *)ALIAS_SRAM_ADDRESS(SRAM_addr, bitNo)
#define ALIAS_PERI_POINTER(PERI_addr, bitNo)								(uint8_t *)ALIAS_PERI_ADDRESS(PERI_addr, bitNo)

/* Macro of Bit Status */
#define SET_BIT																							0x01
#define RESET_BIT																						0x00

#define BITBAND_SRAM_SET_BIT(SRAM_addr, bitNo)							*(ALIAS_SRAM_POINTER(SRAM_addr, bitNo)) = SET
#define BITBAND_SRAM_RESET_BIT(SRAM_addr, bitNo)						*(ALIAS_SRAM_POINTER(SRAM_addr, bitNo)) = RESET

#define BITBAND_PERI_SET_BIT(PERI_addr, bitNo)							*(ALIAS_PERI_POINTER(PERI_addr, bitNo)) = SET
#define BITBAND_PERI_RESET_BIT(PERI_addr, bitNo) 						*(ALIAS_PERI_POINTER(PERI_addr, bitNo)) = RESET

/* NVIC */

/* base address of NVIC */
#define NVIC_BASEADDR                                        0xE000EF00

typedef struct
{																															/* <! Name of Register > */
	_vo uint32_t ISER[3];																				/* <! Interrupt set-enable registers > */
	_vo uint32_t ICER[3];																				/* <! Interrupt clear-enable registers > */
	_vo uint32_t ISPR[3];																				/* <! Interrupt set-pending registers > */
	_vo uint32_t ICPR[3];																				/* <! Interrupt clear-pending registers > */
	_vo uint32_t IABR[3];																				/* <! Interrupt active bit registers > */
	_vo uint32_t IPR[21];																				/* <! Interrupt priority registers > */
	_vo uint32_t STIR;			
}NVIC_RegDef_t;

#define NVIC_BASEPTR																					(NVIC_RegDef_t *)NVIC_BASEADDR

/* Macro of IRQ Status */
#define ACTIVE																								1
#define NONACTIVE																							0

//#define __irq_disable() 
//#define __irq_enable()	

//void NVIC_SetPriority(uint32_t Priority)

/* Systick Timer */

#endif
