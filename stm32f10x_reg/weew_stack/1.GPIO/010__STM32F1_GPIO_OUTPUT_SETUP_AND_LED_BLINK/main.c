#include "stm32f10x.h"                  // Device header

void delay(int time);

int main(void){
	RCC->APB2ENR |= 0x10; // set bit 5 (IOPCEN)
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00300000;
	while(1){
		GPIOC->ODR |= 0x2000;
		delay(3);
		GPIOA->ODR |= ~0x2000;
		delay(3);
	}
	//return 0;
}

void delay(int time){
	for(;time < 0; time--){
		int i = 0;
		for(; i< 10000;i++){
		}
	}
}
