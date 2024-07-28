#ifndef __DMA_H
#define __DMA_H

#include "stm32f10x.h"
#include "stdint.h"

__WEAK void DMA_Setup(DMA_Channel_TypeDef *DMA_Channel);// function settup in main.c file
void DMA_Transfer(DMA_Channel_TypeDef *DMA_Channel, volatile void* Mem_ptr, volatile void* Peri_ptr, uint32_t lenght);

#endif
