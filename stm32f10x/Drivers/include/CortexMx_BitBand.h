#ifndef __CORTEXMX_BITBAND_H_
#define __CORTEXMX_BITBAND_H_

#include "CortexMx.h"

#define ALIAS_SRAM_ADDRESS(SRAM_addr, bitNo)							 	(SRAM_ALIAS_BASEADDR + (((SRAM_addr) - SRAM_BASEADDR)*32) + ((bitNo) * 4))
#define ALIAS_PERI_ADDRESS(PERI_addr, bitNo)				 			 	(PERI_ALIAS_BASEADDR + (((PERI_addr) - PERI_BASEADDR)*32) + ((bitNo) * 4))

#define ALIAS_SRAM_POINTER(SRAM_addr, bitNo)								(uint8_t *)ALIAS_SRAM_ADDRESS(SRAM_addr, bitNo)
#define ALIAS_PERI_POINTER(PERI_addr, bitNo)								(uint8_t *)ALIAS_PERI_ADDRESS(PERI_addr, bitNo)

/* Macro of Bit Status */
#define SET_BIT																							0x01
#define RESET_BIT																						0x00

#define BITBAND_SRAM_SET_BIT(SRAM_addr, bitNo)							*(ALIAS_SRAM_POINTER(SRAM_addr, bitNo)) = SET_BIT
#define BITBAND_SRAM_RESET_BIT(SRAM_addr, bitNo)						*(ALIAS_SRAM_POINTER(SRAM_addr, bitNo)) = RESET_BIT

#define BITBAND_PERI_SET_BIT(PERI_addr, bitNo)							*(ALIAS_PERI_POINTER(PERI_addr, bitNo)) = SET_BIT
#define BITBAND_PERI_RESET_BIT(PERI_addr, bitNo) 						*(ALIAS_PERI_POINTER(PERI_addr, bitNo)) = RESET_BIT


#endif
