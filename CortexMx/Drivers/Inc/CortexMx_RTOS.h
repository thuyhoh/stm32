#ifndef __CortexMX_RTOS_H_
#define __CortexMX_RTOS_H_

#include "stdint.h"
#include "CortexMx.h"



typedef struct 
{
	uint32_t psp_value;      			/* The address of top stack */
	uint32_t timeout;							/*  */
	uint8_t  Task_CurrState; 			/* @TASK_CURRENT_STATE */
	void (*task_handler)(void);		/* The address of task */
}RTOS_Task_t;

/* @TASK_CURRENT_STATE */
#define TASK_READY_STATE 	0x00
#define TASK_IDLE_STATE		0x0F
#define TASK_BLOCK_STATE  0xFF


/**/
void PendSV_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler (void);         
void BusFault_Handler  (void);        
void UsageFault_Handler(void); 

/* Function */
void RTOS_SetCycleMs(void);
void RTOS_SetCycleUs(void);
void RTOS_Config(void);
void RTOS_Init(void);
void RTOS_Start(void);


#endif	/* __CortexMX_RTOS_H_ */
