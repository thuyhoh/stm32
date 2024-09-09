#ifndef __CORTEXMX_SYSTICK_TIMER_H_
#define __CORTEXMX_SYSTICK_TIMER_H_

#include "CortexMx.h"


#define STK_BASE_MODE																					0
#define STK_IT_MODE																						(1<<1)

#define STK_CLOCK_AHB_DIVIDE_1																(1<<2)
#define STK_CLOCK_AHB_DIVIDE_8																0

#define AHB_CLOCK_MAX																					72000000					

typedef struct
{
	uint8_t  STK_Mode;
	uint8_t  STK_ClockSource;
	uint32_t STK_CountValue;
}SysTick_Config_t;

/* Initialization */
void SysTick_Init(SysTick_Config_t *STK_Config);

/* DeInit */
void SysTick_DeInit(void);

void SysTick_SetCountValue(uint32_t CountValue);
void SysTick_StartCount(void);

/* Delay function */
void SysTick_Delayms(uint32_t ms);
void SysTick_Delayus(uint32_t us);

/* Interrupt Handler */
//void SysTick_Handler(void);

#endif  /* __CORTEXM3_SYSTICK_TIMER_H_ */
