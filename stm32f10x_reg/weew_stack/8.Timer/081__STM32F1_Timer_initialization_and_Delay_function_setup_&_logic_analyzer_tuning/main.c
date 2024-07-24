#include "stm32f10x.h"

int main(void)
{
	// set up  the counter a the bus level
	RCC->APB2ENR = (1<<12);
	// set up the counter count to 0
	TIM1->CNT = 0;
	// set up the prescaller to 72 - 1 div equal to 1 Micro second
	TIM1->PSC = 72 - 1;
	// enable counter
	TIM1->CR1 |= 1;
	
	while(1)
	{
		
	}
}
