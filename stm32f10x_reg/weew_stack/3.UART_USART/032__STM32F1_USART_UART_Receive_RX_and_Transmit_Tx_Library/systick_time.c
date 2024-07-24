#include "systick_time.h"
#include "stm32f10x.h"                  // Device header


void Systick_init(void){
	// reset reg value
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00ffffff;
	// SysTick->LOAD thanh ghi load duoc ghi vao SysTick->VAL
	SysTick->VAL = 0;
	
	// enable bit 0,2
	SysTick->CTRL |= 5;
}

void DelayMilis(void){
	SysTick->LOAD = 0x1A5E0; // 0x1A5E0: so xung duoc tao ra trong 1ms
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	// SysTick_CTRL->bit17: co ngat khi SysTick->VAL dem 1->0
}

void Delayms(unsigned long t){
	for(; t > 0; t--){
		DelayMilis();
	}
}

