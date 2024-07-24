#include "stm32f10x.h"
#include "systick_drive.h"
#include "gpio_drive.h"
#include "USART_drive.h"
#include "SPI_drive.h"



// introduction SPI comunication 

/*	SPI 1
	PA4 --> SS		O_AF_PP
	PA5 --> SCLK	O_AF_PP
	PA6 --> MISO	I_PP
	PA7 --> MOSI	P_AF_PP
*/


int main(void){
	SPI_init(1);
	SPI_init(2);
	
	systick_init();
	
	while(1){
		SPI_Msg(1,"hello");
		
	}
}

