/*
	* File: STM32F1_UART_ESP01_LIB
	* Author: nguyen trong thuy 
	* Created on 1/2/2024
*/



/*
	Introduction to ESP01/ESP8266 hard and soft with poof of working using UART	Bridge communication (part 1)
	Create the ESP01 set up library/ menu(part 2)
	Creatint the ESP01 wiffi communication library (part 3)
*/

#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"
#include "systick_time.h"
#include "uart_driver.h"
#include "help_func.h"
#include "esp01_lib.h"

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

int main(void){
	
	/*
		* UART3:-> ESP01
		* UART2:->DFT
	*/
	
	
	
	Systick_init();
	UART_init(2,115200);
	UART_init(3,115200);
	Delayms(10);
	esp_menu();
/*
	esp_net_auto_connect(UART3_msg,uart_3_mgr,Network,Password);
	esp_net_manual_connect(UART3_msg,uart_3_mgr,UART2_msg,uart_2_mgr);
*/
	while(1){
		if(uart_2_mgr[1] == 1){ // receive from uart2 and transmits to uart 3
			//UART_SEND(3,UART2_msg);
			esp_setup(UART3_msg,UART2_msg,uart_3_mgr,uart_2_mgr);
			uart_2_mgr[1] = 0;
			str_empty(UART2_msg);
		}
		if(uart_3_mgr[1] == 1){ // receive from uart2 and transmits to uart 3
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

void SysTick_Handler(void){
	systick_int(uart_1_mgr, uart_2_mgr, uart_3_mgr);
}
