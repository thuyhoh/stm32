#include "stm32f10x.h"                  // Device header
#include "SPI_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"
#include "nokia5110lcd.h"
#include "stopwatch.h"
#include "help_func.h"

void sw_init(void){
	// enable afio
	RCC->APB2ENR |= 1;
	// initial EX PB0/PB1 interupt
	GPIOx_init(PB,0,IN,I_PP);
	GPIOx_init(PB,1,IN,I_PP);
	__disable_irq();
	AFIO->EXTICR[0] |= 0x11;
	EXTI->IMR |= 3;
	EXTI->RTSR |= 3;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	__enable_irq();
	
	// init Systick interrupt
	systick_int_start();
}

void sw_reset(unsigned short *sw_rst, unsigned long *millis){
	*sw_rst = 0;
	systick_init();
	*millis = 0;
	n5110_clear(1);
	n5110_add_print(1,2,25,"00:00:00");
	n5110_add_print(1,5,0,"start");
}

void sw_stop(unsigned int *counter){
	systick_init();
	*counter = 0;
	n5110_add_print(1,5,0,"start");
}

void sw_start(unsigned long *millis, unsigned int *counter, char *number, char *time){
	unsigned long milli = 0;
unsigned int seconds = 0;
unsigned int second = 0;
unsigned int minute = 0;		
	n5110_add_print(1,5,0,"stop");
			n5110_add_print(1,5,55,"reset");
			
			*millis += *counter;
			*counter = 0;
			seconds = *millis/10;
			milli = *millis % 10;
			second = seconds % 60;
			minute = seconds /60;
			
			digit_check(minute,number,time);
			digit_check(second,number,time);
			int_cvt_char(milli,number);
			Concatstr(time,number);
			str_empty(number);
			
			if(minute > 59){
				n5110_add_print(1,2,25,"00:00:00");
				*millis = 0;
			}else{
				n5110_add_print(1,2,25,time);
			}
			str_empty(time);
}

void digit_check(unsigned int time_cst,char number[],char time[]){
	int digit;
	int_cvt_char(time_cst,number);
			digit = str_len(number) + 1;
			if(digit == 1){
				Concatstr(time,"0");
				Concatstr(time,number);
			}else{
				Concatstr(time,number);
			}
			str_empty(number);
			Concatstr(time,":");
}
