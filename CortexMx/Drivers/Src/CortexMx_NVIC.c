#include "CortexMx_NVIC.h"

/* IRQ Configuration and ISR handling */
void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	int IRQ_offset, IRQ_index;
	IRQ_offset = IRQNumber / 32;
	IRQ_index  = IRQNumber % 32;
	if(EnorDi == IRQ_ENABLE)
	{
		*(NVIC_ISER_BASE + IRQ_offset) |= (1<<IRQ_index);
	}else
	{
		*(NVIC_ICER_BASE + IRQ_offset) |= (1<<IRQ_index);
	}
}

void NVIC_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	// find position of the IRQPriority 
	uint8_t IPR_offset  = IRQNumber / 4;
	uint8_t IPR_section = IRQNumber % 4;
	
	// Clear NVIC_IPR
	*(NVIC_IPR_BASE + IPR_offset) &=  (uint32_t)~(0xff << (IPR_section*8));
	
	// Set Priority of IRQNumber
	uint8_t shift_amount = (IPR_section*8) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_IPR_BASE + IPR_offset) |=  (uint32_t)(IRQPriority << shift_amount );
}

uint8_t NVIC_IRQGetPriority(uint8_t IRQNumber)
{
	// find position of the IRQPriority 
	uint8_t IPR_offset  = IRQNumber / 4;
	uint8_t IPR_section = IRQNumber % 4;
	
	uint8_t shift_amount = (IPR_section*8) + (8 - NO_PR_BITS_IMPLEMENTED);
	// Read the value in NVIC_IPR_BASE + offset
	uint32_t RegVal = (*(NVIC_IPR_BASE + IPR_offset) & 0xffffffff)>>(shift_amount);
	
	return (uint8_t)RegVal;
}
