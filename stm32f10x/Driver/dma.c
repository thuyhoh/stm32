#include "dma.h"

/*  configure a DMA channelx ( x is the channel number ) sequence
		0. Enable clock for DMA
		1. Set the peripheral register address in the DMA_CPARx register. The data will be 
		moved from/ to this address to/ from the memory after the peripheral event.
		2. Set the memory address in the DMA_CMARx register. The data will be written to or 
		read from this memory after the peripheral event.
		3. Configure the total number of data to be transferred in the DMA_CNDTRx register. 
		After each peripheral event, this value will be decremented.
		4. Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register
		5. Configure data transfer direction, circular mode, peripheral & memory incremented 
		mode, peripheral & memory data size, and interrupt after half and/or full transfer in the 
		DMA_CCRx register
		6. Activate the channel by setting the ENABLE bit in the DMA_CCRx register
*/

__WEAK void DMA_Setup(DMA_Channel_TypeDef *DMA_Channel)
{
	// Enable clock for DMA
	RCC->AHBENR |= 1; // clock enable DMA1
	/*	- Configure the channel priority using the PL[1:0] bits in the DMA_CCRx register
		- Configure data transfer direction, circular mode, peripheral & memory incremented 
		mode, peripheral & memory data size, and interrupt after half and/or full transfer in the 
		DMA_CCRx register
	*/
	DMA_Channel->CCR; // config
}

void DMA_Transfer(DMA_Channel_TypeDef *DMA_Channel, volatile void* Mem_ptr, volatile void* Peri_ptr, uint32_t lenght)
{
	DMA_Channel->CCR &= (uint32_t)~1;
	// Configure the total number of data to be transferred in the DMA_CNDTRx register
	DMA_Channel->CNDTR = lenght;
	// Set the memory address in the DMA_CMARx register
	DMA_Channel->CMAR = (uint32_t)Mem_ptr;
	// Set the peripheral register address in the DMA_CPARx register
	DMA_Channel->CPAR = (uint32_t)Peri_ptr;
	//setting the ENABLE bit in the DMA_CCRx register
	DMA_Channel->CCR |= 1;
}
