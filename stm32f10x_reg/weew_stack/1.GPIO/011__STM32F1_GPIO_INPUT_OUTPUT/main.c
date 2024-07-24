#include "stm32f10x.h"                  // Device header

void delay(void);

int main(void){
	RCC->APB2ENR |= 4;// en PORTC(bit 5) PORTA(bit 3)
	RCC->APB2ENR |= 0x10;
	GPIOA->CRL &= 0xFFFFFFF0; // set pin0 PORTA -> input
	GPIOA->CRL |= 0x1000; // pin0 PORTA -> input pull/push up
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00300000;
	
	while(1){
			if(GPIOA->IDR & 0x00000001){
				delay();
				GPIOC->ODR ^= 0x2000;
				delay();
			}
			else{
				GPIOC->ODR |= 0x200;
			}
	}
}

void delay(void){
	int i;
	for(i = 0; i < 100000; i++);
}

