#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x.h"
#include "stdint.h"

typedef enum
{
	FLASH_OK,
	FLASH_ERROR,
}Flash_Status;

void Flash_Lock(void);
void Flash_Unlock(void);
void Flash_Read(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght);
Flash_Status Flash_Write(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght);
Flash_Status Flash_Erase(uint32_t addr_page);

#endif
