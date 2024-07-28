#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"

int signal = 0;
void delay(void);

int main(void){
	
	init_gp(PA,0,IN,I_PP);
	init_gp(PC,13,OUT50,O_GP_PP);
	init_gp(PB,2,OUT50,O_GP_PP);
	//int i = 0;
	
	
	while(1){
		/*
		W_GP(PB,2,signal);
			if(signal){
				delay();
				W_GP(PC,13,HIGH);
				delay();
				W_GP(PC,13,LOW);
			}
			else{
				GPIOC->ODR |= 0x200;
			}
			
		*/
		delay();
		W_GP(PB,2,HIGH);
		W_GP(PC,13,HIGH);		
		delay();
		W_GP(PB,2,LOW);
		W_GP(PC,13,LOW);	
	}
	
}

void delay(void){
	int i;
	for(i = 0; i < 100000; i++);
}

void EXTI0_IRQHandler(void){ // ham thuc hien ngat ngoai tren tra cuu trong file setup
	EXTI->PR |= 1; // xoa ngat tren EXTI0
	if(signal){
		signal = 0;
	}else{
		signal = 1;
	}
}

