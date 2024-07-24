/*
//// Library used to setup GPIOs for more details, visit:

https://youtu.be/e0JfbZEditA

*/



#include "stm32f10x.h"    
#include "gpio_drive.h"


void GPIOx_init(unsigned short Port, unsigned short Pin,unsigned short MODE, unsigned short CRF){
	unsigned short tPin = (Pin > 7)? (Pin - 8) : Pin;
	if(Port == 1){// Port A
		RCC->APB2ENR |= 4;
		if(Pin < 8){
			GPIOA->CRL &= ~(unsigned int)(0xf << (tPin*4));
			GPIOA->CRL |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
		else{
			GPIOA->CRH &= ~(unsigned int)(0xf << (tPin*4));
			GPIOA->CRH |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
	}
	else if(Port == 2){ // Port B
		RCC->APB2ENR |= 8;
		if(Pin < 8){
			GPIOB->CRL &= ~(unsigned int)(0xf << (tPin*4));
			GPIOB->CRL |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
		else{
			GPIOB->CRH &= ~(unsigned int)(0xf << (tPin*4));
			GPIOB->CRH |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
	}
	else if(Port == 3){
		RCC->APB2ENR |= 0x10;
		if(Pin < 8){
			GPIOC->CRL &= ~(unsigned int)(0xf << (tPin*4));
			GPIOC->CRL |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
		else{
			GPIOC->CRH &= ~(unsigned int)(0xf << (tPin*4));
			GPIOC->CRH |=  (unsigned int)(((CRF << 2)| MODE) << (tPin*4));
		}
	}	
}

int GPIOx_R(unsigned short Port, unsigned short Pin){
	unsigned int status;
	if(Port == 1){// Port A
		status = ((GPIOA->IDR & (1<<Pin))>>Pin); 
	}
	else if(Port == 2){
		status = ((GPIOB->IDR & (1<<Pin))>>Pin);
	}
	else if(Port == 3){
		status = ((GPIOC->IDR & (1<<Pin))>>Pin);
	}else{
		status = 7;
	}
	return ((int)status);
}

void GPIOx_W(unsigned short Port, unsigned short Pin, unsigned short Status){
	if(Port == 1){
		(Status != 0) ? (GPIOA->ODR |= (1<<Pin)) : (GPIOA->ODR &= ~(1<<Pin));
	}
	else if(Port == 2){
		(Status != 0) ? (GPIOB->ODR |= (1<<Pin)) : (GPIOB->ODR &= ~(1<<Pin));
	}
	else if(Port == 3){
		(Status != 0) ? (GPIOC->ODR |= (1<<Pin)) : (GPIOC->ODR &= ~(1<<Pin));
	}
}


/*	
***	AFIO_reg
		note: de su dung cac thanh ghi AIFO, ta can phai cap xung clock cho AIFO: set 1 bit 0 cua APB2ENR
		
		AFIO->EXTICRx(External interrupt configuration register x) x-> 0:4 : thanh ghi cau hinh ngat ngoai
			moi thanh nghi co 4 mang EXTICR[y]: 
			AFIO->EXTICR[y] (y-> 0:15):  EXTI x configuration: mot mang co 4 bit
				0000: PA[x] Pin
				0001: PB[x] Pin
				0010: PC[x] Pin
				0011: PD[x] Pin
				0100: PE[x] Pin
				0101: PF[x] Pin
				0110: PG[x] Pin
*** EXTI_reg
		EXTI->IMR(Interrupt mask register): Kiem soat viec cho phép hoac ngan chan tung duong ngat ngoai tao ra mot yeu cau ngat cho CPU
			Bits 0:19 MRx: Interrupt Mask on line x
				0: Interrupt request from Line x is masked
				1: Interrupt request from Line x is not masked // cho phep yeu cau thuc hien ngat tai line x(EXTICR[x])
		
		EXTI_RTSR(Rising trigger selection register): thanh ghi lua chon xung dau vao len 
			Bits 0:19 TRx: Rising trigger event configuration bit of line x
				0: Rising trigger disabled (for Event and Interrupt) for input line // khong cho phep xung input tai line x la xung len(0-1) cua cac su kien hay ngat 
				1: Rising trigger enabled (for Event and Interrupt) for input line	// cho phep xung input tai line x la xung len(0-1) cua cac su kien hay ngat
		
		EXTI_FTSR(Rising trigger selection register): thanh ghi lua chon xung dau vao len 
			Bits 0:19 TRx: Failing trigger event configuration bit of line x
				0: Failing trigger disabled (for Event and Interrupt) for input line // khong cho phep xung input tai line x la xung fail(1-0) cua cac su kien hay ngat 
				1: Failing trigger enabled (for Event and Interrupt) for input line	// cho phep xung input tai line x la xung xuong(1-0) cua cac su kien hay ngat
		EXTI_PD
*/
/*
void GPIO_ISR_init(unsigned short Port, unsigned short Pin){
	RCC->APB2ENR |= 1;
	unsigned int x = (((Port == 2))?1:0) + ((Port == 3)? 2:0);
	__disable_irq();
	AFIO->EXTICR[Pin] = x;
	EXTI->IMR 	|= (1<<Pin);
	EXTI->RTSR	|= (1<<Pin);
	if(Pin <= 3) 											NVIC_EnableIRQ(EXTI0_IRQn);
	else if(Pin >= 4 && Pin <= 7)			NVIC_EnableIRQ(EXTI1_IRQn);
	else if(Pin >= 8 && Pin <= 11) 		NVIC_EnableIRQ(EXTI2_IRQn);
	else if(Pin >= 12 && Pin <= 15) 	NVIC_EnableIRQ(EXTI3_IRQn);
	__enable_irq();
}

*/

//void GPIO_INTR(unsigned short Port, unsigned short Pin){
	//__disable_irq();// vo hieu hoa toan bo ngat trong he thong
	//AFIO->EXTICR[Port] = 0x00; // kich hoat ngat EXTIi
	//EXTI->IMR |= 1; // thanh ghi cho phep bat ngat ngoai vi rieng le: bit0->9: xac dinh muc do uu tien cua cac ngat ngoai vi
	//EXTI->RTSR |= 1; // bat ngat canh len (low -> high)
	//NVIC_EnableIRQ(EXTI0_IRQn); // Kích hoat ngat EXTI0 trong bo dieu khien ngat (NVIC)
	//__enable_irq(); // cho phep toan bo ngat duoc thuc hien
//}

