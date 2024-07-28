#include "stm32f10x.h"                  // Device header

#include "SPI_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"

/*
	SPIx_SCK: 
		- master: Alternate function push-pull
		- slave : Input floating
	SPIx_MOSI:
		- master: Alternate function push-pull
		- slave : Input floating / Input pull-up
	SPIx_MISO :
		- master: input floating / Input pull-up
		- slave : Alternate function push-pull(point to point)/ Alternate function open drain(muti-slave)
	SPIx_NSS 	:
		- software : Input floating/ Input pull-up / Input pull-down
		- hardware : Be used as a GPIO
		
*/

void SPI_init(unsigned short Spi_Channel){
	// enable altenative function for pin
	RCC->APB2ENR |= 1; 
	if(Spi_Channel == 1){
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
	}
	else if(Spi_Channel == 2){
		RCC->APB1ENR |= 0x4000;	// Enable SPI2
		// Setup the pin
		GPIOx_init(PB,12,OUT50,O_AF_PP);
		GPIOx_init(PB,13,OUT50,O_AF_PP);
		GPIOx_init(PB,14,IN,I_PP);
		GPIOx_init(PB,15,OUT50,O_AF_PP);
		
		// setup SPI peripherals
		SPI2->CR1 |= 0x4;
		SPI2->CR1 |= 0x32;
		SPI2->CR2 |= 0x4;
		SPI2->CR1 |= 0x40;
		GPIOx_W(PB,12,HIGH);
	}
}

void SPI_Tx(unsigned Spi_Channel, char Tx_char){
	if(Spi_Channel == 1){
		GPIOx_W(PA,4,LOW);
		SPI1->DR = Tx_char;
		while(SPI1->SR & 0x80);
		GPIOx_W(PA,4,HIGH);
	}
	else if(Spi_Channel == 2){
		GPIOx_W(PB,12,LOW);
		SPI2->DR = Tx_char;
		while(SPI2->SR & 0x80);
		GPIOx_W(PB,12,HIGH);
	}
}

void SPI_Msg(unsigned short Spi_Channel, char const* msg){
	int i = 0;
	if(Spi_Channel == 1){
		GPIOx_W(PA,4,LOW);
		while(*(msg+i) != '\0'){
			SPI1->DR = *(msg+i);
			while(SPI1->SR & 0x80);
			i++;
		}
		GPIOx_W(PA,4,HIGH);
	}else if(Spi_Channel == 2){
		GPIOx_W(PB,12,LOW);
		while(*(msg+i) != '\0'){
			SPI2->DR = *(msg+i);
			while(SPI2->SR & 0x80);
			i++;
		}
		GPIOx_W(PB,12,HIGH);
	}
}
