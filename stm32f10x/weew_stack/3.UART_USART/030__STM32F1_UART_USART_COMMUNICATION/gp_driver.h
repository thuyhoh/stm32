/*
 * file		: gp_driver.h
 * author	: Nguyen Trong Thuy
 * date		: 18/22024
 * purpose	: heading file of GPIO_drive
 * update	: 
 * document	: stm32_reference_manual
*/

 
/* define RCC_APB2ENR la gia tri co trong thanh ghi dia chi 0x40021000(RCC->APB2ENR)
**	RCC->APB2ENR(0x40021000): APB2 peripheral clock enable register
	bit 0:AFIOEN(Alternate function IO clock enable): bit cap xung cho AFIO
		0: Alternate Function IO clock disabled
		1: Alternate Function IO clock enable
	
	bit 2:IOPAEN(IO port A clock enable): bit cho phep IO Port A hoat dong
		0: IO port A clock disabled // ngat xung cap cho port A
		1: IO port A clock enabled 	// cho phep xung cap cho port A
	
	bit 3:IOPBEN(IO port B clock enable): bit cho phep IO Port B hoat dong
		0: IO port B clock disabled // ngat xung cap cho port B
		1: IO port B clock enabled 	// cho phep xung cap cho port B
		
	bit 4:IOPCEN(IO port C clock enable): bit cho phep IO Port C hoat dong
		0: IO port C clock disabled // ngat xung cap cho port C
		1: IO port C clock enabled 	// cho phep xung cap cho port C
*/
#define RCC_APB2ENR     (*((volatile unsigned long *) 0x40021018))

	
/* define GPIO_x la gia tri chua trong thanh ghi GPIO_x 
**	boundary address					port
	0x4001 0800 - 0x4001 0BFF     		 A
	0x4001 0C00 - 0x4001 0FFF			 B
	0x4001 1000 - 0x4001 13FF			 C
*/

#define GPIO_A (*((volatile unsigned long*)0x40010800))
#define GPIO_B (*((volatile unsigned long*)0x40010C00))
#define GPIO_C (*((volatile unsigned long*)0x40011000))

// defination port 
#define PA 1 // port A
#define PB 2 // port B
#define PC 3 // port C

/*	GPIOx_reg (x -> A:G)
*** GPIOx->CRL(Port configuration register low): offset = 0x00(address GPIOx->CRL = GPIO_x + offest) : thanh ghi quan li cac PIN LOW(0->7) cua cac PORT
	duoc chia ra lam 8 phan; moi phan gom 4 bit: CNFy[1:0] va MODEy[1:0]. y -> 0:7
	
	MODEy[0:1]: Port x mode bits 
		00: Input mode (reset state)
		01: Output mode, max speed 10 MHz.
		10: Output mode, max speed 2 MHz.
		11: Output mode, max speed 50 MHz
	
	CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
		+ In input mode (MODE[1:0]=00): // input mode
			00: Analog mode
			01: Floating input (reset state)
			10: Input with pull-up / pull-down	
		+ In output mode (MODE[1:0] > 00): // out put mode
			00: General purpose output push-pull
			01: General purpose output Open-drain
			10: Alternate function output Push-pull
			11: Alternate function output Open-drain
	
*** GPIOx->CRH(Port configuration register high): offset = 0x04(address GPIOx->CRL = GPIO_x + offest) : thanh ghi quan li cac PIN HIGH(8->15) cua cac PORT
	tuong tu voi GPIOx->CRL thi GPIOx->CRH cung chia thanh CNFy[1:0] va MODEy[1:0]. y -> 8:15
	
*** GPIOx->IDR(Port input data register): offset = 0x08 : thanh ghi read-only doc trang thai input cua cac pin
	bit 0:15: IDRy (Port input data) (y -> 0:15): tung bit se mang mot trang thai cua tung PIN
	
*** GPOIx->ODR(Port output data register): offset = 0x0C: thanh ghi ghi trang thai output cho cac pin
	bit 0:15: ODRy (Port output data) (y -> 0:15): ghi trang thai ra tung PIN qua tung bit
*/

// MODEy for port 

#define IN 0 		// Input mode (reset state)
#define OUT10 1		// Output mode, max speed 10 MHz.
#define OUT2 2		// Output mode, max speed 2 MHz.
#define OUT50 3		// Output mode, max speed 50 MHz.

// CNFy for input 
#define I_AN 0		// Analog mode
#define I_F 1		// Floating input (reset state)
#define I_PP 2		// Input with pull-up / pull-down

// CNFy for output
#define O_GP_PP 0 	// General purpose output push-pull
#define O_GP_OD 1	// General purpose output Open-drain
#define O_AF_PP 2	// Alternate function output Push-pull
#define O_AF_OD 3	// Alternate function output Open-drain

// status
#define HIGH 1
#define LOW 0

void GPIOx_init(unsigned short port, unsigned short Pin,unsigned short dir, unsigned short opt);

int GPIOx_R(unsigned short Port, unsigned short Pin);

void GPIOx_W(unsigned short Port, unsigned short Pin, unsigned short status);

void GPIOx_ISR(unsigned short Port, unsigned short Pin);

void GPIO_ISR_init(unsigned short Port, unsigned short Pin);
