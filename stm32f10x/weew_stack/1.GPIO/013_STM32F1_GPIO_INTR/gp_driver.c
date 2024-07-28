#include "gp_driver.h"

void init_gp(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
 volatile unsigned long * CR;
 unsigned short tPIN = pin;
 unsigned short offset = 0x00;
	
	if(pin > 7)
		{
			tPIN -= 8;
			offset = 0x01;
		}
		
	if(port == 1)
		{
			RCC_APB2ENR |= 4; //// Enabling PORT A
			CR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			RCC_APB2ENR |= 8; //// Enabling PORT A
			CR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
		{
			RCC_APB2ENR |= 0x10; //// Enabling PORT A
			CR = (volatile unsigned long *) (&GPIO_C + offset);
		}
		
		*CR &= ~(0xf<<(tPIN)*4); ///Reset the taget pin
		*CR |= ((dir <<(tPIN*4)) | (opt<<(tPIN*4+2))); //// Set up the direction and the option of the PIN
}

int R_GP(unsigned short port, unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(port == 1)
		{
			IDR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			IDR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
	{
		IDR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	state = ((*IDR & (1<<pin))>>pin);
	return state;
}

void W_GP(unsigned short PORT,unsigned short pin, unsigned short STATUS)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	if(PORT == 1)
		{
			ODR = (volatile unsigned long *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		ODR = (volatile unsigned long *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		ODR = (volatile unsigned long *)(&GPIO_C+ offset);
		}
	STATUS ? (*ODR |= (STATUS<<pin)) : (*ODR &= ~(1<<pin));
}
void toggle_GP(unsigned short port, unsigned short pin)
{
	if (R_GP(port,pin))
		{
			W_GP(port,pin,0);
		}
	else
		{
			W_GP(port,pin,1);
		}
}


/*	
***	AFIO_reg
		note: de su dung cac thanh ghi AIFO, ta can phai cap xung clock cho AIFO: set 1 bit 0 cua APB2ENR
		
		AFIO->EXTICRx(External interrupt configuration register x) x-> 0:4 : thanh ghi cau hinh ngat ngoai
			moi thanh nghi co 4 mang EXTICR[y]: 
			AFIO->EXTICR[y] (y-> 0:15):  EXTI x configuration: mot mang co 4 bit
				0000: PA[x] pin
				0001: PB[x] pin
				0010: PC[x] pin
				0011: PD[x] pin
				0100: PE[x] pin
				0101: PF[x] pin
				0110: PG[x] pin
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
		
*/


//void GPIO_INTR(unsigned short port, unsigned short pin){
	//__disable_irq();// vo hieu hoa toan bo ngat trong he thong
	//AFIO->EXTICR[port] = 0x00; // kich hoat ngat EXTIi
	//EXTI->IMR |= 1; // thanh ghi cho phep bat ngat ngoai vi rieng le: bit0->9: xac dinh muc do uu tien cua cac ngat ngoai vi
	//EXTI->RTSR |= 1; // bat ngat canh len (low -> high)
	//NVIC_EnableIRQ(EXTI0_IRQn); // Kích hoat ngat EXTI0 trong bo dieu khien ngat (NVIC)
	//__enable_irq(); // cho phep toan bo ngat duoc thuc hien
//}


