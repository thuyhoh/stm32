/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#include "stm32f407xx_uart_driver.h"
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{	// enable clock
		if(pUSARTx == USART1_BASE)
		{
			USART1_PCLK_EN();
		}else if(pUSARTx == USART2_BASE)
		{
			USART2_PCLK_EN();
		}else if(pUSARTx == USART3_BASE)
		{
			USART3_PCLK_EN();
		}else if(pUSARTx == UART4_BASE)
		{
			UART4_PCLK_EN();
		}else if(pUSARTx == UART5_BASE)
		{
			UART4_PCLK_EN();
		}else if(pUSARTx == USART6_BASE)
		{
			USART6_PCLK_EN();
		}else
		{
			// error
		}
	}else
	{ // diable clock
		if(pUSARTx == USART1_BASE)
		{
			USART1_PCLK_DIS();
		}else if(pUSARTx == USART2_BASE)
		{
			USART2_PCLK_DIS();
		}else if(pUSARTx == USART3_BASE)
		{
			USART3_PCLK_DIS();
		}else if(pUSARTx == UART4_BASE)
		{
			UART4_PCLK_DIS();
		}else if(pUSARTx == UART5_BASE)
		{
			UART4_PCLK_DIS();
		}else if(pUSARTx == USART6_BASE)
		{
			USART6_PCLK_DIS();
		}else
		{
			// error
		}
	
	}
}

void USART_Init(USART_Handle_t *pUSARTHandle)
{
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);
	
	uint32_t temp = 0;
/******************************** Configuration of CR1******************************************/
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
	{ // transmission only
		temp |= (1<< USART_CR1_TE);
		temp &= (uint32_t)~(1<< USART_CR1_RE);
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
	{	// receiver only
		temp &= (uint32_t)~(1<< USART_CR1_TE);
		temp |= (1<< USART_CR1_RE);
	}else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{ // both tx and rx
		temp |= (1<< USART_CR1_TE);
		temp |= (1<< USART_CR1_RE);
	}
	// WORD LENGHT
	if(pUSARTHandle->USART_Config.USART_WordLenght ==		USART_WORDLEN_9BITS)
	{
		temp |= (1 << USART_CR1_M);
	}else
	{
		 temp &= (uint32_t)~(1 << USART_CR1_M);
	}
		// PARITY CONTROL
	if(pUSARTHandle->USART_Config.USART_ParityControl != USART_PARITY_DISABLE)
	{
		// Parity control enable
		temp |= (1 << USART_CR1_PCE); 
		if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
		{ // USART_PARITY_EN_ODD
			temp |= (1 << USART_CR1_PS);
		}else
		{ // USART_PARITY_EN_EVEN
			temp &= (uint32_t)~(1 << USART_CR1_PS);
		}
	}else 
	{ // Parity control disable
		temp &= (uint32_t)~(1<<USART_CR1_PCE); 
	}
	
	// store value into CR1
	pUSARTHandle->pUSARTx->CR1 |= temp;
/******************************** Configuration of CR2******************************************/
	temp = 0;
	// STOP BIT
	// clear stop[1:0] in usart_cr2
	temp &= (uint32_t)~(3<<12);
	temp |= pUSARTHandle->USART_Config.USART_NoOfStopBits;

	// store value into CR2
	pUSARTHandle->pUSARTx->CR2 |= temp;
/******************************** Configuration of CR2******************************************/	
	temp = 0;
	if ( pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		//Implement the code to enable CTS flow control 
		temp |= ( 1 << USART_CR3_CTSE);
		temp &= (uint32_t)~( 1 << USART_CR3_CTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		//Implement the code to enable RTS flow control 
		temp &= (uint32_t)~( 1 << USART_CR3_CTSE);
		temp |= ( 1 << USART_CR3_CTSE);

	}else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control 
		temp |= ( 1 << USART_CR3_CTSE);
		temp |= ( 1 << USART_CR3_CTSE);
	}
	// store value into CR2
	pUSARTHandle->pUSARTx->CR3 |= temp;
}
void USART_DeInit(USART_RegDef_t *pUSARTx)
{
	// disable clock for USART
	// reset USARTx register 
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName)
{
	if(pUSARTx->SR & FlagName) return FLAG_SET;
	return FLAG_RESET;
}

void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{ // enable uart
		pUSARTx->CR1 |= (1 << USART_CR1_UE);
	}else
	{ // disable uart
		pUSARTx->CR1 &= (uint32_t)~(1 << USART_CR1_UE);
	}
}

void USART_Start(USART_RegDef_t *pUSARTx)
{
	USART_PeripheralControl(pUSARTx, ENABLE);
}

void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
	pUSARTx->SR &= (uint32_t)~(StatusFlagName);
}

void USART_SendData(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
  //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE_FLAG));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLenght == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits 
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF); // Load 9 bits into DR regsiter
			
			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice 
				pTxBuffer++; // save data
				pTxBuffer++; // save parity bit
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer 
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);
			
			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TC_FLAG));

}
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_RXNE_FLAG)){} 

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLenght == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x1FF);

				//Now increment the pRxBuffer two times
				(uint16_t*) pRxBuffer++;
				(uint16_t*) pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);
				 
				 //Increment the pRxBuffer
				(pRxBuffer)++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = (uint8_t)pUSARTHandle->pUSARTx->DR;
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0x7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len){}
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len){}


