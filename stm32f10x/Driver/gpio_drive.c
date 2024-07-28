#include "gpio_drive.h"

void GPIO_Init(uint8_t PORT,uint8_t PIN,uint8_t DIR,uint8_t OPT)
{
	__IO uint64_t * CR;
	uint8_t tPin = PIN;
	uint8_t offset = 0x00;
	
	if(PIN > 7)
	{
		tPin -=8;
		offset = 0x01;
	}
		

	if(PORT == 1)
		{
			RCC_APBENR |= 0x4;

			CR = (__IO uint64_t *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		RCC_APBENR |= 0x8;
		CR = (__IO uint64_t *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		RCC_APBENR |= 0x10;
		CR = (__IO uint64_t *)(&GPIO_C + offset);
		}

	*CR &= ~(0xf<<(tPin)*4);
	*CR |= ((DIR<<(tPin*4)) | (OPT<<(tPin*4+2)));
}

int GPIO_Read(uint8_t PORT,uint8_t pin)
{
	__IO uint64_t * IDR;
	uint64_t offset = 0x02;
	int state;
	
	if(PORT == 1)
		{
			IDR = (__IO uint64_t *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		IDR = (__IO uint64_t *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		IDR = (__IO uint64_t *)(&GPIO_C+ offset);
		}
		state =  ((*IDR & (1<<pin))>>pin)  ;
		
		return state;
}

void GPIO_Write(uint8_t PORT,uint8_t pin, uint8_t STATUS)
{
	__IO uint64_t * ODR;
	uint64_t offset = 0x03;
	if(PORT == 1)
		{
			ODR = (__IO uint64_t *)(&GPIO_A + offset);
		}
	else if(PORT == 2)
		{
		ODR = (__IO uint64_t *)(&GPIO_B+ offset);
		}
	else if(PORT == 3)
		{
		ODR = (__IO uint64_t *)(&GPIO_C+ offset);
		}
	STATUS ? (*ODR |= (STATUS<<pin)) : (*ODR &= ~(1<<pin));
}

void GPIO_Toggle_Pin(uint8_t Port, uint8_t Pin)
{
	if(GPIO_Read(Port, Pin))
	{
		GPIO_Write(Port, Pin, 0);
	}
	else
	{
		GPIO_Write(Port, Pin, 1);
	}
}

void Blink_Led(void)
{
	GPIO_Write(PB, 2, 0);
}

//

static void Get_IQR_line(uint8_t Port, uint8_t Pin, uint8_t *EXTI_Px_PIN, uint8_t *EXTIx_IRQn)
{
	switch (Port)
	{
	case PA: *EXTI_Px_PIN = 0;  break;
	case PB: *EXTI_Px_PIN = 1;  break;
	case PC: *EXTI_Px_PIN = 2;  break;
	default: break;
	}

	switch (Pin)
	{
		case 0:  *EXTIx_IRQn  = EXTI0_IRQn;       break;
		case 1:  *EXTIx_IRQn  = EXTI1_IRQn;       break;
		case 2:  *EXTIx_IRQn  = EXTI2_IRQn;       break;
		case 3:  *EXTIx_IRQn  = EXTI3_IRQn;       break;
		case 4:  *EXTIx_IRQn  = EXTI4_IRQn;       break;
		case 5:  *EXTIx_IRQn  = EXTI9_5_IRQn;     break;
		case 6:  *EXTIx_IRQn  = EXTI9_5_IRQn;     break;
		case 7:  *EXTIx_IRQn  = EXTI9_5_IRQn;     break;
		case 8:  *EXTIx_IRQn  = EXTI9_5_IRQn;     break;
		case 9:  *EXTIx_IRQn  = EXTI9_5_IRQn;     break;
		default: *EXTIx_IRQn = EXTI15_10_IRQn; 	  break;
	}
}

void EXTI_IQR_Init(uint8_t Port, uint8_t Pin, GPIO_IQR_Sellect_Edge RF)
{
	GPIO_Init(Port, Pin, IN, I_PP);
	uint8_t EXTIx_IRQn; 
	uint8_t EXTI_Px_PIN;
	Get_IQR_line(Port,Pin,&EXTI_Px_PIN, &EXTIx_IRQn);
	// Alternate function IO clock enable
	RCC->APB2ENR |= 1;
	__disable_irq();
	// Activating the interrupts for the Port
	AFIO->EXTICR[(uint8_t)Pin/4] = EXTI_Px_PIN;  
	// Enable the interrupt 
	EXTI->IMR |= 1<<(Pin); 
 	// Generate a system interrupt at the rising edge
	if(RF == EXTI_IQR_Falling_Edge)		EXTI_IQR_FTSR(Pin);
	else EXTI_IQR_RTSR(Pin);
	// Enable the global interrupt function
	NVIC_EnableIRQ(EXTIx_IRQn); 
	__enable_irq();
}

