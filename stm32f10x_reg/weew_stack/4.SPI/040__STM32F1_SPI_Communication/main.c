#include "stm32f10x.h"
#include "systick_drive.h"
#include "gpio_drive.h"
#include "USART_drive.h"




// introduction SPI comunication 

/*	SPI 1
	PA4 --> SS		O_AF_PP
	PA5 --> SCLK	O_AF_PP
	PA6 --> MISO	I_PP
	PA7 --> MOSI	P_AF_PP
*/


int main(void){
// Active SPI peripheral / AFIO funtion
	RCC->APB2ENR |= 1;			// enable AFIO funtion
	RCC->APB2ENR |= 0x1000;	// Enable SPI1
// Setup the pin
	GPIOx_init(PA,4,OUT50,O_AF_PP);
	GPIOx_init(PA,5,OUT50,O_AF_PP);
	GPIOx_init(PA,6,IN,I_PP);
	GPIOx_init(PA,7,OUT50,O_AF_PP);
	
// setup SPI peripherals
	SPI1->CR1 |= 0x4;
	SPI1->CR1 |= 0x32;
	SPI1->CR2 |= 0x4;
	SPI1->CR1 |= 0x40;
	GPIOx_W(PA,4,HIGH);
	
	systick_init();
	
	while(1){
		DelayMs(50);
		GPIOx_W(PA,4,LOW);
		SPI1->DR = 'x';
		while(SPI1->SR & 0x80);
		GPIOx_W(PA,4,HIGH);
		
	}
}


