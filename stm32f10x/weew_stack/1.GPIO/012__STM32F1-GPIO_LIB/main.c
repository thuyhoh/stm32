#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"

void delay(void);

int main(void){
	
	init_gp(PA,0,IN,I_PP);
	init_gp(PC,13,OUT50,O_GP_PP);
	
	while(1){
			if(R_GP(PA,0) == 0){
				delay();
				W_GP(PC,13,HIGH);
				delay();
				W_GP(PC,13,LOW);
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

