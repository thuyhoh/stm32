#include "stm32f10x.h"                  // Device header
#include "lcd_16x02_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"

/*
	pin setup 
	PA8  -> RS
	PA9  -> RW
	PA10 -> E
	PA0  -> DB0
	PA1  -> DB1
	PA2  -> DB2
	PA3  -> DB3
	PA4  -> DB4
	PA5  -> DB5
	PA6  -> DB6
	PA7  -> DB7	
*/



// Clear functions

// Write CMD & Data function



int main(void){
	SysTick_init();
	// Initialize PINs
	unsigned short i;
	for(i = 0; i<11; i++){
		GPIOx_init(PA,i,OUT50,O_GP_PP);
	}
	
	while(1){
		lcd_msg("hello",1,1);
	}
	//return 0;
}
