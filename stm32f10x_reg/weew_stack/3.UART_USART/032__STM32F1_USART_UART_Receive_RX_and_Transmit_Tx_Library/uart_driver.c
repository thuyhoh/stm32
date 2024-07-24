#include "stm32f10x.h"
#include "uart_driver.h"
#include "gp_driver.h"



//------------------- caculation Baud rate of TX/RX--------------------------------//
/*
		BR_TX/RX = fck/(16*USART_DIV) -> tim UART_DIV
			fck: tan so clk dc su dung
			USARTDIV is an unsigned fixed point number that is coded on the USART_BRR register // USART_DIV la gia tri duoc luu vao trong thanh ghi UART_BRR va la so nguyen
			-> can phai lam tron ket qua tim duoc
			UART_BRR : DIV_Mantissa[11:4] : DIV_Fraction[3:0] // phan nguyen : phan thap phan
*/
unsigned long  UART_BRR(unsigned short usart, unsigned long BR){
	unsigned long final;
	unsigned long div = 36000000;
	unsigned long dec;
	double frac = 36000000.00;
	double frac2 = 1.00;
	
	if(usart == 1){
		div = 72000000;
		frac = 72000000.00;
	}
	// DIV_Mantissa
	div = div/(BR*16);
	
	// DIV_Fraction
	frac = 16*((frac/(BR*16)) - div);
	dec = frac;
	frac2 = 100*(frac - div);
	if(frac2 > 50){ // kiem tra frac2 > 0.5 
		dec++; // lam tron 
		if(dec == 16){ // kiem tra tinh trang tran cua dec
			dec = 0;
			div++;
		}
	}
	// UART_BRR : DIV_Mantissa[11:4] : DIV_Fraction[3:0]
	final = (div<<4); 
	final += dec; 
	return final;
}

// --------------- init UART---------------------//
	
	// if using USART1 clock speed 72Mhz else 36Mhz
	// USART3 -> using PB10(TX) AND PB11(RX)
	// USART2 -> using PA2(TX) AND PA3(RX)
	// USART1 -> using PA9(TX) AND PA10(RX)	

void UART_init(unsigned short usart, unsigned long BR){
	
	// enable the alternate function for pins
	RCC->APB2ENR |= 1;
	
	// baund rate val
	unsigned long BR_cal;
	BR_cal	= UART_BRR(usart,BR);
	
	if(usart == 1){
		RCC->APB2ENR |= 0x4000; // enable USART1(bit 14)
		
		// enable Rx/Tx pin
		init_gp(PA,9,OUT50,O_AF_PP); // RX pin
		init_gp(PA,10,IN,I_PP); // TX pin
		
		// BR: baurate
		USART1->BRR = BR_cal;
		// enable uart transmit (bit 3) -> TE
		USART1->CR1 |= 8;
		// enable uart recive (bit 2) -> RE
		USART1->CR1 |= 4;
		// enable uart (bit 13) -> UE
		USART1->CR1 |= 0x2000;
	}
	else if(usart == 2){
		RCC->APB1ENR |= 0x20000;
		init_gp(PA,2,OUT50,O_AF_PP); // rx pin
		init_gp(PA,3,IN,I_PP);
		USART2->BRR = BR_cal;
		// enable uart transmit
		USART2->CR1 |= 8;
		// enable uart recive
		USART2->CR1 |= 4;
		// enable uart
		USART2->CR1 |= 0x2000;
	}
	else if(usart == 3){
		RCC->APB1ENR |= 0x40000;
		init_gp(PB,10,OUT50,O_AF_PP); // rx pin
		init_gp(PB,11,IN,I_PP);
		USART3->BRR = BR_cal;
		// enable uart transmit
		USART3->CR1 |= 8;
		// enable uart recive
		USART3->CR1 |= 4;
		// enable uart
		USART3->CR1 |= 0x2000;
	}
}

char UART_Rx(unsigned short uart){
	char c;
	if(uart == 1){
		while((USART1->SR & 0x20) != 0x20){}
		c = USART1->DR;
	}
	else if(uart == 2){
		while((USART2->SR & 0x20) != 0x20){}
		c = USART2->DR;
	}
	else if(uart == 3){
		while((USART3->SR & 0x20) != 0x20){}
		c = USART3->DR;
	}
	return c;
}

void UART_Tx(unsigned short uart, char c){
	if(uart == 1){
		while((USART1->SR & (1<<6)) == 0x80){}
		USART1->DR =  c;
	}
	else if(uart == 2){
		while((USART2->SR & (1<<6)) == 0x80){}
		USART2->DR = c;
	}
	else if(uart == 3){
		while((USART3->SR & (1<<6)) == 0x80){}
		USART3->DR = c;
	}
}


