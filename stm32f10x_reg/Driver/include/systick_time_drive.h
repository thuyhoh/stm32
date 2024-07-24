#include "stm32f10x.h" 
#include "stdint.h"

void SysTick_init(void);
void delayMillis(void);
void delay(uint64_t ms);
void delayus(void);
void delay_us(uint64_t us);
void SysTick_IT_Init(void);