#include "systick_time_drive.h"

void SysTick_init(void)
{
    // reset SysTick regsi
    SysTick->CTRL &= 0x00;
    SysTick->LOAD &= 0;
    SysTick->VAL  &= 0;
    // Counter enable(bit 0) &  Clock source selection(bit 2)
    SysTick->CTRL |= (1<<2) | 1; 
}

void delayMillis(void)
{
  // load 
  SysTick->LOAD = 72000 - 1;
	SysTick->VAL = 0;
	// COUNTFLAG
    while((SysTick->CTRL & 0x00010000) == 0);
}
 
void delay(uint64_t ms)
{   
    while (ms)
    {
        delayMillis();
        ms--;
    }   
}

void delayus(void)
{
    // load 
  SysTick->LOAD = 72 - 1;
	SysTick->VAL = 0;
	// COUNTFLAG
  while((SysTick->CTRL & 0x00010000) == 0);
}

void delay_us(uint64_t us)
{
    while(us)
    {
        delayus();
        us--;
    }
}

void SysTick_IT_Init(void)
{
	SysTick_init();
// Enable TICKINT_bit: SysTick exception request enable
	SysTick->CTRL |= 1<<1;
}

/* SysTick_Handler

	void SysTick_Handler();
	
*/

// PWM mode:

