/*
doc: PCD8544.PDF
*/

#include "stm32f10x.h"                  // Device header
#include "SPI_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"
#include "stopwatch.h"
#include "help_func.h"
#include "adc_drive.h"

/* 	connection lines
PA0 -->RST
PA1 --> DC
PA2 -->Screen Light
PA4 --> SS
PA5 --> SCLK
PA7 --> MOSI


PB0 -> reset
PB1 -> start/stop

*/
//
int adc_val;

int main(void)
{
	systick_init();
	adc_init(adc1,PA,0);
	while(1){
		if(adc_check(ADC1,PA,0))
		{
				adc_val = adc_rx(ADC1,PA,0);
		}
			
	}
		
}
	
	
	


