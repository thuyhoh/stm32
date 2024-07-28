/*
doc: PCD8544.PDF
*/

#include "stm32f10x.h"                  // Device header
#include "SPI_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"
#include "nokia5110lcd.h"

unsigned char n5110_buffer[6][84];

int main(void){
	// n5110_init(1);
	systick_init();
	
	
	while(1){
		GPIOx_W(PA,1,HIGH);
		SPI_Tx(1,0x1F);
		SPI_Tx(1,0x05);
		SPI_Tx(1,0x07);
		SPI_Tx(1,0x00);
		SPI_Tx(1,0x00);
		GPIOx_W(PA,1,LOW);
		DelayMs(500);
	}
}
