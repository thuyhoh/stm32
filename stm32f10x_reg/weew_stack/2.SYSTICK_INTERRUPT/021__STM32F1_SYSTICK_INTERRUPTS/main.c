#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"

int main(void){
	// set up
	init_gp(PA,0,IN,I_PP);
	init_gp(PA,12,OUT50,O_GP_PP);
	init_gp(PC,13,OUT50,O_GP_PP);
	
	__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = 7200000-1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7;
	__enable_irq();
	
	// loop
	while(1){
		W_GP(PA,12,R_GP(PA,0)); // viec nhan tin hieu tu button say ra song song voi viec led C13 nhap nhay
	}
	
}

void SysTick_Handler(void){ // ham ngat
	if(R_GP(PC,13)){
		W_GP(PC,13,0);
	}
	else{
		W_GP(PC,13,1);
	}
}
