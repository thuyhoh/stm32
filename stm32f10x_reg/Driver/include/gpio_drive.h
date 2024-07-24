#ifndef __GPIO_DRIVE_H
#define __GPIO_DRIVE_H
#include "stm32f10x.h" 
#include "stdint.h"

// define 
#define __IO  volatile

#define RCC_APBENR       (*((volatile unsigned long *) 0x40021018))

#define GPIO_A       		 (*((volatile unsigned long *) 0x40010800))
#define GPIO_B       		 (*((volatile unsigned long *) 0x40010C00))
#define GPIO_C       		 (*((volatile unsigned long *) 0x40011000))


#define PA          1           
#define PB          2           
#define PC          3          


#define HIGH       1
#define LOW        0

#define  IN        0
#define  OUT10     1
#define  OUT2      2
#define  OUT50     3


#define I_AN 0
#define I_F  1
#define I_PP 2

#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3

#define AFIO_Clock_Enable 1

typedef enum
{
	INPUT_MODE         = 0U,
	OUTPUT_10MHZ_MODE  = 1U,
	OUTPUT_2MHZ_MODE   = 2U,
	OUTPUT_50MHZ_MODE  = 3U
}Mode_config;

typedef enum 
{
	OUTPUT_GP_PUSH_PULL 	= 0U,
	OUTPUT_GP_OPEN_DRAIN 	= 1U,
	OUTPUT_AF_PUSH_PULL 	= 2U,
	OUTPUT_AF_OPEN_DRAIN 	= 3U
}OutPut_config_Mode;

typedef enum 
{
	INPUT_ANALOG = 0U,
	INPUT_FLOAT  = 1U,
	INPUT_PP		 = 3U
}InPut_config_Mode;

typedef enum
{
    EXTI_IQR_Falling_Edge = 0U,
    EXTI_IQR_Rising_Edge 
}GPIO_IQR_Sellect_Edge;

// define inline function
#define set_bit(reg, index)     (reg) |= 1<<(index)
#define clear_bit(reg, index)   (reg) &= ~(1<<(index))

#define EXTI_IQR_RFlag(EXTI_Line)    EXTI->PR   |= 1<<(EXTI_Line)
#define EXTI_IQR_RTSR(EXTI_Line)     EXTI->RTSR |= 1<<(EXTI_Line)
#define EXTI_IQR_FTSR(EXTI_Line)     EXTI->FTSR |= 1<<(EXTI_Line)

// GPIO function
void GPIO_Init(uint8_t PORT,uint8_t PIN,uint8_t DIR,uint8_t OPT);
int GPIO_Read(uint8_t PORT,uint8_t pin);
void GPIO_Write(uint8_t PORT,uint8_t pin, uint8_t STATUS);
void GPIO_Toggle_Pin(uint8_t Port, uint8_t Pin);

// interrupt function
void EXTI_IQR_Init(uint8_t Port, uint8_t Pin, GPIO_IQR_Sellect_Edge RF);
/*	EXTIx_IRQHandler function
	void EXTI0_IRQHandler(){};
	void EXTI1_IRQHandler(){};
	void EXTI2_IRQHandler(){};
	void EXTI3_IRQHandler(){};
	void EXTI4_IRQHandler(){};
	void EXTI9_5_IRQHandler(){};
	void EXTI15_10_IRQHandler(){};
*/
#endif
