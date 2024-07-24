#include "systick_time.h"
#include "stm32f10x.h"                  // Device header

// SysTick initialization

void Systick_init(void){
	// reset reg value
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00ffffff;
	
	// SysTick->LOAD thanh ghi load duoc ghi vao SysTick->VAL
	SysTick->VAL = 0;
	
	// enable bit 0,2
	SysTick->CTRL |= 5;
}

// set up delay 1(ms) function

void DelayMilis(void){
	SysTick->LOAD = 72000; // 72000: so xung duoc tao ra trong 1ms 108Mhz
	SysTick->VAL = 0;
	
	while((SysTick->CTRL & 0x00010000) == 0);
	// SysTick_CTRL->bit17: co ngat khi SysTick->VAL dem 1->0
}

// set up delay t(ms) function
void Delayms(unsigned long t){
	for(; t > 0; t--){
		DelayMilis();
	}
}

// set up systick_interrupt initialization

void systick_int_start(void){
	__disable_irq();
	SysTick->CTRL = 0;
	SysTick->LOAD = 72000; // 1ms ->  72000hz
	SysTick->VAL = 0;
	SysTick->CTRL |= 7; // Enable systick interrupt
	__enable_irq();
	
}


void systick_int(unsigned short uart_1_mgr[], unsigned short uart_2_mgr[], unsigned short uart_3_mgr[]){
	if(uart_1_mgr[0] != 0){
		if(uart_1_mgr[6] == 0){
			uart_1_mgr[0] = 0;
			uart_1_mgr[1] = 1;
			Systick_init();// close systick_int
		}else{
			uart_1_mgr[6]--;
		}
	}else if(uart_2_mgr[0] != 0){
		if(uart_2_mgr[6] == 0){
			uart_2_mgr[0] = 0;
			uart_2_mgr[1] = 1;
			Systick_init();
		}else{
			uart_2_mgr[6]--;
		}
	}else if(uart_3_mgr[0] != 0){
		if(uart_3_mgr[6] == 0){
			uart_3_mgr[0] = 0;
			uart_3_mgr[1] = 1;
			Systick_init();
		}else{
			uart_3_mgr[6]--;
		}
	}
}
	
