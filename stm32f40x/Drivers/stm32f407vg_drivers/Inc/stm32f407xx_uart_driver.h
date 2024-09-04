/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#ifndef __STM32F407XX_SPI_DRIVER_H_
#define __STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t USART_Mode;					/*@UART_MODE*/
	uint32_t USART_Baud;				/*@UART_BAUD*/
	uint8_t USART_NoOfStopBits;	/*@UART_NUMBER_OF_STOP_BITS*/
	uint8_t USART_WordLenght;		/*@UART_WORD_LENGHT*/
	uint8_t USART_ParityControl;/*@UART_PARITY_CONTROL*/
	uint8_t USART_HWFlowControl;/*@UART_HARDWARE_FLOW_CONTROL*/
}USART_Config_t;

typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t USART_Config;
}USART_Handle_t;

/*@UART_MODE*/
#define USART_MODE_ONLY_TX 	0
#define USART_MODE_ONLY_RX 	1
#define USART_MODE_TXRX  		2

/*
 *@USART_BAUD
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_1200					1200
#define USART_STD_BAUD_2400					400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define SUART_STD_BAUD_3M 					3000000

/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE   0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1			/*CTS :  To Send */
#define USART_HW_FLOW_CTRL_RTS    	2			/*RTS : Receip To Send */
#define USART_HW_FLOW_CTRL_CTS_RTS	3

/*
 * BIT POSITION OF UART
 */
// USART_SR
#define USART_SR_PE				0
#define USART_SR_FE				1
#define USART_SR_NF				2
#define USART_SR_ORE			3
#define USART_SR_IDLE			4
#define USART_SR_RXNE			5
#define USART_SR_TC				6
#define USART_SR_TXE			7
#define USART_SR_LBD			8
#define USART_SR_CTS			9



// USART_CR1
#define USART_CR1_SBK					0
#define USART_CR1_RWU					1	
#define USART_CR1_RE					2
#define USART_CR1_TE					3
#define USART_CR1_IDLEIE			4
#define USART_CR1_RXNEIE			5
#define USART_CR1_TCIE				6
#define USART_CR1_TXEIE				7
#define USART_CR1_PEIE				8
#define USART_CR1_PS					9
#define USART_CR1_PCE					10
#define USART_CR1_WAKE				11
#define USART_CR1_M						12
#define USART_CR1_UE					13
#define USART_CR1_OVER8				15

// USART_CR2
#define USART_CR2_LBDL			5
#define USART_CR2_LBDIE			6
#define USART_CR2_LBCL			8
#define USART_CR2_CPHA			9
#define USART_CR2_CPOL			10
#define USART_CR2_CLKEN			11
#define USART_CR2_LINEN			14

// USART_CR3
#define USART_CR3_EIE					0
#define USART_CR3_IREN				1
#define USART_CR3_IRLP				2
#define USART_CR3_HDSEL				3
#define USART_CR3_NACK				4
#define USART_CR3_SCEN				5
#define USART_CR3_DMAR				6
#define USART_CR3_DMAT				7
#define USART_CR3_RTSE				8
#define USART_CR3_CTSE				9
#define USART_CR3_CTSIE				10
#define USART_CR3_ONEBIT			11


/*
 * BIT POSITION OF RCC
 */
// RCC_APB1ENR
#define RCC_APB2ENR_USART1ENR		4
#define RCC_APB1ENR_USART2ENR		17
#define RCC_APB1ENR_USART3ENR		18
#define RCC_APB1ENR_UART4ENR		19
#define RCC_APB1ENR_UART5ENR		20
#define RCC_APB2ENR_USART6ENR		5

/* FLAG NAME */
#define USART_CTS_FLAG		(1 << USART_SR_CTS)
#define USART_TXE_FLAG		(1 << USART_SR_TXE)
#define USART_TC_FLAG			(1 << USART_SR_TC)	
#define USART_RXNE_FLAG		(1 << USART_SR_RXNE)
#define USART_ORE_FLAG		(1 << USART_SR_ORE)
#define USART_FE_FLAG			(1 << USART_SR_FE)
#define USART_PE_FLAG			(1 << USART_SR_PE)

/******************************************************************************************
 *								APIs supported by this driver
 *		 For more information about the APIs check the function definitions
 ******************************************************************************************/
/*
 * Clock and Reset Control of GPIO
 */

/* Enable Clock for USARTx */
#define USART1_PCLK_EN()			RCC_BASE->APB2ENR |= (1<< RCC_APB2ENR_USART1ENR)	
#define USART2_PCLK_EN()			RCC_BASE->APB1ENR |= (1<< RCC_APB1ENR_USART2ENR)
#define USART3_PCLK_EN()			RCC_BASE->APB1ENR |= (1<< RCC_APB1ENR_USART3ENR)
#define UART4_PCLK_EN()		    RCC_BASE->APB1ENR |= (1<< RCC_APB1ENR_UART4ENR)
#define UART5_PCLK_EN()				RCC_BASE->APB1ENR |= (1<< RCC_APB1ENR_UART5ENR)
#define USART6_PCLK_EN()			RCC_BASE->APB2ENR |= (1<< RCC_APB2ENR_USART6ENR)

/* Disable Clock for USARTx */
#define USART1_PCLK_DIS()			RCC_BASE->APB2ENR &= (uint32_t)~(1<< RCC_APB2ENR_USART1ENR)	
#define USART2_PCLK_DIS()			RCC_BASE->APB1ENR &= (uint32_t)~(1<< RCC_APB1ENR_USART2ENR)
#define USART3_PCLK_DIS()			RCC_BASE->APB1ENR &= (uint32_t)~(1<< RCC_APB1ENR_USART3ENR)
#define UART4_PCLK_DIS()		  RCC_BASE->APB1ENR &= (uint32_t)~(1<< RCC_APB1ENR_UART4ENR)
#define UART5_PCLK_DIS()			RCC_BASE->APB1ENR &= (uint32_t)~(1<< RCC_APB1ENR_UART5ENR)
#define USART6_PCLK_DIS()			RCC_BASE->APB2ENR &= (uint32_t)~(1<< RCC_APB2ENR_USART6ENR)

/* Reset Register for USART*/
/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);


/*
 * Data Send and Receive
 */
void USART_SendData(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

/*
 * Application callback
 */
 void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv);
#endif /* __STM32F407XX_SPI_DRIVER_H_ */
