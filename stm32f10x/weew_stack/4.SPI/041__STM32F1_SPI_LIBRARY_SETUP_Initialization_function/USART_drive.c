#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "systick_drive.h"
#include "USART_drive.h"


//------------------- caculation Baud rate of TX/RX--------------------------------//
/*
		BR_TX/RX = fck/(16*USART_DIV) -> tim UART_DIV
			fck: tan so clk dc su dung
			USARTDIV is an unsigned fixed point number that is coded on the USART_BRR register // USART_DIV la gia tri duoc luu vao trong thanh ghi UART_BRR va la so nguyen
			-> can phai lam tron ket qua tim duoc
			UART_BRR : DIV_Mantissa[11:4] : DIV_Fraction[3:0] 
*/

/*
Ex1: stm32fx_rf_mn 799
Ex2:
Ex3:
*/
unsigned short USART_BRR(unsigned short Usart_Channel, unsigned long Baundrate){
	unsigned short USART_BRR;
	double			 	 DIV_Frac = 36000000.00;
	unsigned int 	 DIV_Man  = 36000000;
	unsigned short Frac_Dec;
	
	if(Usart_Channel == 1){
		DIV_Frac = 72000000.00;
		DIV_Man  = 72000000;
	}
	
	DIV_Man  = DIV_Man  / (16*Baundrate);
	DIV_Frac = 16*(DIV_Frac / (16*Baundrate) - DIV_Man);
	
	Frac_Dec = (unsigned short)DIV_Frac;
	
	Frac_Dec += ((DIV_Frac - Frac_Dec) >= 0.5)? 1:0;
	
	if(Frac_Dec == 16){
		Frac_Dec = 0;
		DIV_Man += 1;
	}
	
	USART_BRR = (unsigned short)(DIV_Man << 4) | Frac_Dec;
	return USART_BRR;
}


void USART_init(unsigned short Usart_Channel,unsigned long Baundrate){
	// if using USART1 clock speed 72MHz else 36Mhz
	// USART3 	-> PB10(Tx) PB11(Rx)
	// USART2		-> PA2 (Tx) PA3 (Rx)
	// USART1 	-> PA9 (Tx) PA10(Rx)
	
	// USART_Pin     				 Configure
	//   Tx				OUTPUT : Alternate function push-pull
	//	 Rx				INPUT	 : Input floating / Input pull-up
	
	// enable alternative pin
	RCC->APB2ENR |= 1;
	
	// configure Usart Pin: Tx and Rx
	// enable Usart clock
	// calcular Baundrate speed
	unsigned short BRR_Cal = USART_BRR(Usart_Channel, Baundrate);
	// setup Baundrate speed
	// enable Transmit and Receive
	// enable Usart
	
	if(Usart_Channel == 1){
		// configure Usart Pin: Tx and Rx
		GPIOx_init(PA,9,OUT50,O_AF_PP);  	// Tx
		GPIOx_init(PA,10,IN,I_PP);			 	// Rx
		RCC->APB2ENR 	|= 0x4000;					// enable Usart clock
		USART1->BRR 	 = BRR_Cal;					// setup Baundrate speed
		// enable Transmit and Receive
		USART1->CR1 	|= 0x8;							// Enable Transmit
		USART1->CR1 	|= 0x4;							// Enable Receive
		USART1->CR1 	|= 0x2000;					// Usart Enable
	}
	else if(Usart_Channel == 2){
		GPIOx_init(PA,2,OUT50,O_AF_PP);
		GPIOx_init(PA,3,IN,I_PP);
		RCC->APB1ENR 	|= 0x20000;
		USART2->BRR 	 = BRR_Cal;
		USART2->CR1 	|= 0x8;
		USART2->CR1 	|= 0x4;
		USART2->CR1 	|= 0x2000;
	}
	else if(Usart_Channel == 3){
		GPIOx_init(PB,10,OUT50,O_AF_PP);
		GPIOx_init(PB,11,IN,I_PP);
		RCC->APB2ENR 	|= 0x40000;
		USART3->BRR 	 = BRR_Cal;
		USART3->CR1 	|= 0x8;
		USART3->CR1 	|= 0x4;
		USART3->CR1 	|= 0x2000;
	}
}



char USART_Rx(unsigned short Usart_Channel){
	char chat;
	if(Usart_Channel == 1){
		while((USART1->SR & 0x20) == 0x00);
		chat = (char)USART1->DR;
	}
	else if(Usart_Channel == 2){
		while((USART2->SR & 0x20) == 0x00);
		chat = (char)USART2->DR;
	}
	else if(Usart_Channel == 3){
		while((USART3->SR & 0x20) == 0x00);
		chat = (char)USART3->DR;
	}else{
		return 10;
	}
	return chat;
}

void USART_Tx(unsigned short Usart_Channel, char chat){
	if(Usart_Channel == 1){
		while((USART1->SR &(1<<6)) == 0x00);
		USART1->DR = chat;
	}
	else if(Usart_Channel == 2){
		while((USART2->SR & (1<<6)) == 0x00);
		USART2->DR = chat;
	}
	else if(Usart_Channel == 3){
		while((USART3->SR & (1<<6)) == 0x00);
		USART3->DR = chat;
	}
}

void USART_Send(unsigned short Usart_Channel, char *msg){
	int i = 0;
	while(*(msg+i) != '\0'){
		USART_Tx(Usart_Channel,*(msg+i));
		i++;
	}
}

// = USART_int + interrupt setup
void USART_ISR_init(unsigned short Usart_Channel,unsigned long Baundrate){
	
	RCC->APB2ENR |= 1;
	
	unsigned short BRR_Cal = USART_BRR(Usart_Channel, Baundrate);
	
	if(Usart_Channel == 1){
		__disable_irq();
		GPIOx_init(PA,9,OUT50,O_AF_PP);  	// Tx
		GPIOx_init(PA,10,IN,I_PP);			 	// Rx
		RCC->APB2ENR 	|= 0x4000;					// enable Usart clock
		USART1->BRR 	 = BRR_Cal;					// setup Baundrate speed
		// enable Transmit and Receive
		USART1->CR1 	|= 0x8;							// Enable Transmit
		USART1->CR1 	|= 0x4;							// Enable Receive
		USART1->CR1 	|= 0x2000;					// Usart Enable
		// enable interrupt transmit and receive
		USART1->CR1 	|= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);
		__enable_irq();
	}
	else if(Usart_Channel == 2){
		__disable_irq();
		GPIOx_init(PA,2,OUT50,O_AF_PP);
		GPIOx_init(PA,3,IN,I_PP);
		RCC->APB1ENR 	|= 0x20000;
		USART2->BRR 	 = BRR_Cal;
		USART2->CR1 	|= 0x8;
		USART2->CR1 	|= 0x4;
		USART2->CR1 	|= 0x2000;
		USART2->CR1 	|= 0x20;
		NVIC_EnableIRQ(USART2_IRQn);
		__enable_irq();
	}
	else if(Usart_Channel == 3){
		GPIOx_init(PB,10,OUT50,O_AF_PP);
		GPIOx_init(PB,11,IN,I_PP);
		RCC->APB2ENR 	|= 0x40000;
		USART3->BRR 	 = BRR_Cal;
		USART3->CR1 	|= 0x8;
		USART3->CR1 	|= 0x4;
		USART3->CR1 	|= 0x2000;
		USART3->CR1 	|= 0x20;
		NVIC_EnableIRQ(USART3_IRQn);
		__enable_irq();
	}
}


void USART_ISR(unsigned short Usart_Channel, unsigned short bridge, unsigned short *signal, unsigned short *counter, char *msg){
	if(bridge == 0){// du lieu can duoc xu li 
		msg[*counter] = USART_Rx(Usart_Channel);
		if(msg[*counter] == '\n'){
			*counter = 0;
			*signal  = 1; 
		}
		else{
			*counter = *counter + 1;
		}
	}
	else{
		USART_Tx(bridge, USART_Rx(Usart_Channel));
	}
}

void empty_str(char * str){
	int i = 0;
	while(*(str+i)!= '\0'){
		*(str+i) = '\0';
		i++;
	}
}
