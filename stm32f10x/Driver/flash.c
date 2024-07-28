#include "flash.h"

void Flash_Lock(void)
{
	// set Lock bit in FLASH_CR
	FLASH->CR |= 1<<6;
}

//
void Flash_Unlock(void)
{
	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;
}

//
void Flash_Read(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght)
{
	uint32_t i;
	for(i = 0; i< Lenght; i++)
	{
		*(uint8_t*)(Buff + i) = *(uint8_t*)(AddrStart + i); 
	}
}
//
Flash_Status Flash_Write(volatile uint32_t AddrStart, uint8_t* Buff, uint32_t Lenght)
{
	if((AddrStart == 0x0000) ||  Buff == 0x00 || ((Lenght%2)| (Lenght == 0)))
	{
		// Error
		return FLASH_ERROR;
	}
	// check bit busy
	while(FLASH->SR & 1)
	{
		// wait to bay bit
	}
	// check Lock bit in FLASH_CR
	if(FLASH->CR & (1<<7))
	{
		Flash_Unlock();	
	}
	// Set the PG bit in the FLASH_CR register
	FLASH->CR |= 1<<0;
	uint32_t i;
	for(i = 0; i< (Lenght/2); i++)
	{
		*(uint16_t*)(AddrStart + i*2U) = *(uint16_t*)(Buff + i*2U);
	}
	// check bit busy
	while(FLASH->SR & 1)
	{
		// wait to bay bit
	}
	// clear the PG bit in the FLASH_CR register
	FLASH->CR |= ~(uint32_t)(1<<0);
	// Lock Flash
	Flash_Lock();
	return FLASH_OK;
}

//
Flash_Status Flash_Erase(uint32_t addr_page)
{
	if(addr_page < 0x08000000 || addr_page > 0x0801FFFF)
	{
		return FLASH_ERROR;
	}
	// check bit busy
	while(FLASH->SR & 1)
	{
		// wait to bay bit
	}
	// check Lock bit in FLASH_CR
	if(FLASH->CR & (1<<7))
	{
		Flash_Unlock();	
	}
	// Set the PER bit in the FLASH_CR register
	FLASH->CR |= 1<<1;	
	// Program the FLASH_AR register to select a page to erase
	FLASH->AR = addr_page;
	// Set the STRT bit in the FLASH_CR register
	FLASH->CR |= 1<<5;
	// waiting busy bit is reset
	while(FLASH->SR & 1<<0);
	// clear PER bit
	FLASH->CR &= ~(uint32_t)(1<<1);
	// clear STRT bit
	FLASH->CR &= 1<<5;
	// Lock Flash
	Flash_Lock();
	return FLASH_OK;
}
//
