#include "stm32f10x.h" 
#include "systick_drive.h"

void systick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
}

void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}
void systick_int_start(void){
	// tat toan bo ngat tren ngoai vi
	__disable_irq(); 
	SysTick->CTRL = 0;
	SysTick->LOAD = 72000 - 1;
	SysTick->VAL = 0;
	// set TICKINT = 1; enable interrupt
	SysTick->CTRL |= 7;
	// cho phep ngat hoat dong
	__enable_irq();
	
}
