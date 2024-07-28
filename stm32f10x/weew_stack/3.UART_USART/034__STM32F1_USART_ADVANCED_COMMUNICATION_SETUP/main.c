/*
	* File: STM32F1_comunicate with ESP01
	* Author: Nguyen Trong Thuy
	* Date:  2/2/2024
*/

/*
	1 - USART-UART advanced communication strategy 
	2 - update the UART/ Systick interrupt library
	3 - make the input function (Equivalent of the input for python)
*/


#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"
#include "systick_time.h"
#include "uart_driver.h"

/*    UART Manager
	0 - count
	1 - signal
	2 - bridge
	3 - terminator should 1: terminator / 0 : interrupt
	4 - terminator char
	5 - time const 
	6 - time counter 
*/

char UART1_msg[100];
unsigned short UART1_signal = 0;
unsigned int UART1_counter = 0;
unsigned short UART1_bgd = 0;

unsigned short uart_1_mgr[7] = {0,0,0,0,'\n',0,0};

char UART2_msg[100];
unsigned short UART2_signal = 0;
unsigned int UART2_counter = 0;
unsigned short UART2_bgd = 0;
unsigned short uart_2_mgr[7] = {0,0,0,0,'\n',0,0};

char UART3_msg[100];
unsigned short UART3_signal = 0;
unsigned int UART3_counter = 0;
unsigned short UART3_bgd = 0;
unsigned short uart_3_mgr[7] = {0,0,0,0,'\n',0,0};

char chat = 'C';
char msg[30] = "hello thuy";

void USART2_IRQHandler();
void USART2_IRQHandler();
void USART2_IRQHandler();

int main(void){
	Systick_init();
	UART_init(1,9600);
	UART_init(2,9600);
	UART_init(3,9600);
	Delayms(10);
	
	while(1){
		// TRUONG HOP 2 THIET BI KHONG CUNG TOC DO BR 
		// LAY STM32 LAM CAU NOI 
		
		if(uart_2_mgr[1] == 1){ // UART3_BRR < UART2_BRR
			UART_SEND(3,UART2_msg);
			uart_2_mgr[1] = 0;
			str_empty(UART2_msg);
		}
		if(uart_3_mgr[1] == 1){// UART3_BRR < UART2_BRR
			UART_SEND(2,UART3_msg);
			uart_3_mgr[1] = 0;
			str_empty(UART3_msg);
		}
	}
}

void USART2_IRQHandler(){// ham ngat tai USART2 khi tin hieu tai cac chan uart2(tx,rx)
	UART_ISR(2,uart_2_mgr,UART2_msg);
}

void USART3_IRQHandler(){// ham ngat tai USART2 khi tin hieu tai cac chan uart2(tx,rx)
	UART_ISR(3,uart_3_mgr,UART3_msg);
}

void SysTick_Handler(void){ // ngat systick
	systick_int(uart_1_mgr, uart_2_mgr, uart_3_mgr);
}
