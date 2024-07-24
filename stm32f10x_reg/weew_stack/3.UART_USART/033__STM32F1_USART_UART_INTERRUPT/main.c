#include "stm32f10x.h"
#include "systick_drive.h"
#include "gpio_drive.h"
#include "USART_drive.h"

char USART1_msg[200];
unsigned short USART1_count 	= 0;
unsigned short USART1_signal 	= 0;
unsigned short USART1_bridge	= 0;// USART1 -> USARTx

char USART2_msg[200];
unsigned short USART2_count 	= 0;
unsigned short USART2_signal 	= 0;
unsigned short USART2_bridge	= 0;// USART1 -> USARTx

char USART3_msg[200];
unsigned short USART3_count 	= 0;
unsigned short USART3_signal 	= 0;
unsigned short USART3_bridge	= 0;// USART1 -> USARTx

void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

char msg[200];

// introduction SPI comunication 

int main(void){
	systick_init();
	USART_init(1,11200);
	USART_init(2,11200);
	USART_init(3,11200);
	while(1){
			if(USART2_signal == 1){
				USART_Send(3,msg);
				USART2_signal = 0;
				empty_str(USART2_msg);
			}
			if(USART3_signal == 1){
				USART_Send(2,msg);
				USART3_signal = 0;
				empty_str(USART3_msg);
			}
	}
}



void USART2_IRQHandler(void){
	USART_ISR(2,0,&USART2_signal,&USART2_count,USART2_msg);
}

void USART3_IRQHandler(void){
	USART_ISR(3,0,&USART3_signal,&USART3_count,USART3_msg);
}


