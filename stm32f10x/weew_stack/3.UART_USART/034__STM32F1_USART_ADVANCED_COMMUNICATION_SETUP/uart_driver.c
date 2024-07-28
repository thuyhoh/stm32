#include "stm32f10x.h"
#include "uart_driver.h"
#include "gp_driver.h"
#include "systick_time.h"


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
		__disable_irq();
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
		USART1->CR1 |= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);		
		__enable_irq();
	}
	else if(usart == 2){
		__disable_irq();
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
		USART2->CR1 |= 0x20;
		NVIC_EnableIRQ(USART2_IRQn);		
		__enable_irq();
	}
	else if(usart == 3){
		__disable_irq();
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
		USART3->CR1 |= 0x20;
		NVIC_EnableIRQ(USART3_IRQn);		
		__enable_irq();
	}
}

//------------ Receive_data from UASRTx-----------------//

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

//------------ Transmits data from UASRTx-----------------//

void UART_Tx(unsigned short uart, char c){
	if(uart == 1){
		while((USART1->SR & (1<<6)) == 0x00){}
		USART1->DR =  c;
	}
	else if(uart == 2){
		while((USART2->SR & (1<<6)) == 0x00){}
		USART2->DR = c;
	}
	else if(uart == 3){
		while((USART3->SR & (1<<6)) == 0x00){}
		USART3->DR = c;
	}
}

//------------ Sending messange -----------------//

void UART_SEND(unsigned short uart, char* str){
	int i = 0;
	while(*(str+i) != '\0'){
		UART_Tx(uart, *(str+i));
		i++;
	}
}

//------------ comunitcation mupti device (<= 2 device connect with stm32fx)  -----------------//

/*
1 - define my uart
2 - is it bridge or process or both // xem xet den mode cua qua trinh giao tiep bridge(cau noi != 0) hoac process(thuc thi)
if process" strug to fullfill, cnt, signal
*/

/*    UART Manager
	0 - count																						/// bo dem tin nhan gui qua usart
	1 - signal																					/// tin hieu hoan thanh tin nhan
	2 - bridge																					/// kiem tra co thuc hien cau noi hay khon 
	3 - terminator should 1: terminator / 0 : interrupt /// thuc hien ngat hoac khong
	4 - terminator char																	/// ky tu ket thuc
	5 - time cst																				/// thoi gian gui usart
	6 - time counter 																		/// thoi gian dem 
*/

// cau noi chi thuc hien duoc khi 2 thiet bi co cung toc do baudrate //

void UART_ISR(unsigned short uart, unsigned short uart_mgr[], char msg[]){
	// kiem tra brignal = ? -> != 0(thuc hien cau noi)
	if(uart_mgr[2] == 0){ 
		msg[uart_mgr[0]] = UART_Rx(uart); // nhan thong tin tu USARTx
		if(uart_mgr[3]){ // kiem tra co thuc hien ngat hay khon g
			// khong thuc hien ngat
			if(msg[uart_mgr[0]] == uart_mgr[4]){
				uart_mgr[0] = 0;
				uart_mgr[1] = 1;
			}else{
				uart_mgr[0] = uart_mgr[0] + 1;
			}
			
		}else{
			// thuc hen ngat
			// timer strategy
			uart_mgr[0]++;
			uart_mgr[6] = uart_mgr[5];
			systick_int_start();
		}
		
	// khi la cau noi giua hai thiet bi
	}else{
		UART_Tx(uart_mgr[2],UART_Rx(uart)); // truyen du lieu nhan duoc tu chan UASRT den USART(bridge)
	}
	
}

//------------ clear msg  -----------------//

void str_empty(char str[]){
	int i = 0;
	while(str[i] != '\n'){
		str[i] = '\0';
		i++;
	}
}

// send msg after h time

void UART_MSG(unsigned short uart, char msg[], unsigned short uart_mgr[]){
	unsigned long TimeOut = 72000000;
	UART_SEND(uart,msg);
	while(uart_mgr[1] == 0 && TimeOut != 0){
		TimeOut--;
	}
	uart_mgr[1] = 0;
}

