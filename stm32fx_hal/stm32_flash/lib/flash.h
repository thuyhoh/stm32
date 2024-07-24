#ifndef __FLASH_H_
#define __FLASH_H_

#include "main.h"

void flash_erease(uint32_t addr);
void flash_write_arr(uint32_t addr, uint8_t *data, uint16_t len);
void flash_read_arr(uint32_t addr, uint8_t *data, uint16_t len);4
void flash_unlock(void);
void flash_lock(void);
#endif
