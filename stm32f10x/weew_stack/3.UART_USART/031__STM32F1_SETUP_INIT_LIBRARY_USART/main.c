#include "stm32f10x.h"                  // Device header
#include "gp_driver.h"
#include "systick_time.h"
#include "uart_driver.h"


int main(void){
	UART_init(3,9600);
	UART_init(2,9600);
	UART_init(1,9600);
	while(1){
		
	}
}
