#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"
#include "systick_time.h"

static char chat  = 'c';

int main(void){
	/*	uart2 init*/
	/* 	uart pin
		pin		chuc_nang  	config
		PA2 -> Tx   			OUTPUT : Alternate function push-pull
		PA3 -> Rx					INPUT	 : Input floating / Input pull-up	
	*/
	GPIOx_init(PA,2,OUT50,O_AF_PP);
	GPIOx_init(PA,3,IN,I_PP);
	// enable alternative function for pin
	RCC->APB2ENR |= 1;
	/*	enable clock uart	*/
	RCC->APB1ENR |= 0x20000;
	//	setup baundrate
	USART2->BRR = 0xEA6;
	// 	enable TRansmits
	USART2->CR1 |= 0x8;
	// 	enable recive
	USART2->CR1 |= 0x4;
	// enable uart
	USART2->CR1 |= 0x2000;
	Systick_init();
	while(1){
		
		// receive data 
		while((USART2->SR & 0x20) == 0x00);
		chat = (char)USART2->DR;
		
		// transmit data 
		while((USART2->SR & (1<<6)) == 0x00);
		USART2->DR = chat;
		
	}
	
}

