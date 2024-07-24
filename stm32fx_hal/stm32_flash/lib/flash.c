#include "flash.h"

void flash_unlock(void)
{
	HAL_FLASH_Unlock();
}
void flash_lock(void)
{
	HAL_FLASH_Lock();
}

void flash_erease(uint32_t addr)
{
	FLASH_EraseInitTypeDef fl_er_init;
	fl_er_init.PageAddress = addr;
	fl_er_init.NbPages = 1;
	fl_er_init.TypeErase = FLASH_TYPEERASE_PAGES;
	uint32_t PageError;
	HAL_FLASHEx_Erase(&fl_er_init,&PageError);
}

void flash_write_arr(uint32_t addr, uint8_t *data, uint16_t len)
{
	uint16_t i;
	for(i = 0; i< len/2; i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr+ i, ((uint16_t)data[i+1]<<8 | data[i]));
	}
}

void flash_read_arr(uint32_t addr, uint8_t *data, uint16_t len)
{
	uint32_t *ptr = (uint32_t *)addr;
	uint16_t tmp;
	uint16_t i;
	for(i = 0; i< len; i = i+2)
	{
		tmp = *(ptr+i);
		data[i] = tmp;
		data[i+1] = tmp >> 8;
	}
}
