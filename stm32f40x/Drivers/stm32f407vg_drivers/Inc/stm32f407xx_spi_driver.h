/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#ifndef __STM32F407XX_SPI_DRIVER_H_
#define __STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"

typedef struct
{
	uint8_t SPI_DeviceMode; /* @SPI_DEVICE_MODE */
	uint8_t SPI_BusConfig;  /* @SPI_BUS_CONGIG */
	uint8_t SPI_SclkSpeed;	/* @SPI_BUS_CLKSPEED */
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
	uint8_t  *pTxBuffer;
	uint8_t  *pRxBuffer;
	uint32_t 	Txlen;
	uint32_t 	Rxlen;
	uint8_t		TxState;
	uint8_t		RxState;
}SPI_Handle_t;

/* @SPI_DEVICE_MODE */
#define SPI_DEVICE_MASTER_MODE		1
#define SPI_DEVICE_SLAVE_MODE		  0

/* @SPI_BUS_CONGIG */
#define SPI_BUS_CONFIG_FD						 			 1	/* FULL DUPLEX */
#define SPI_BUS_CONFIG_HD						 			 2	/* HALF DUPLEX */
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY			 3	/* SIMPLEX RECEIVE ONLY */
//#define SPI_BUS_CONFIG_SIMPLEX_TXONLY		 	 4	/* SIMPLEX TRANSMIT ONLY */ (UNNECESSARY) -> FULL DUPLEX AND REMOVE RX LINE

/* @SPI_BUS_CLKSPEED */
#define SPI_SCLK_SPEED_DIV2								0
#define SPI_SCLK_SPEED_DIV4								1
#define SPI_SCLK_SPEED_DIV8								2
#define SPI_SCLK_SPEED_DIV16							3
#define SPI_SCLK_SPEED_DIV32							4
#define SPI_SCLK_SPEED_DIV64							5
#define SPI_SCLK_SPEED_DIV128							6
#define SPI_SCLK_SPEED_DIV256							7

/* @SPI_DFF */
#define SPI_DFF_8BITS											0
#define SPI_DFF_16BITS										1

/* @SPI_CPOL */
#define SPI_CPOL_HIGH		1
#define SPI_CPOL_LOW		0

/* @SPI_CPHA */
#define SPI_CPHA_HIGH		1
#define SPI_CPHA_LOW		0

/* @SPI_SSM */
#define SPI_SSM_EN		1
#define SPI_SSM_DI		0

/* BIT POSITION */
	// SPI_CR1
#define SPI_CR1_DFF		11
#define SPI_CR1_SPE		6

	// SPI_CR2
#define SPI_CR2_TXEIE 7
#define SPI_CR2_RXEIE 6
#define SPI_CR2_ERRIE 5
#define SPI_CR2_FRF		4

	// SPI_SR
#define SPI_SR_BUSY		7
#define SPI_SR_OVR    6
#define SPI_SR_TXE		1
#define SPI_SR_RXNE		0
/* FLAG NAME */
#define SPI_TXE_FLAG		( 1 << SPI_SR_TXE  )
#define SPI_RXNE_FLAG		( 1 << SPI_SR_RXNE  )
#define SPI_BUSY_FLAG   ( 1 << SPI_SR_BUSY )
/**/
#define SPI_PERI_ENABLE		ENABLE	
#define SPI_PERI_DISABLE	DISABLE

/* SPI Application states */
#define SPI_READY					0
#define SPI_BUSY_IN_TX		1
#define SPI_BUSY_IN_RX		2

/* SPI Application events */
#define SPI_EVENT_TX_CMPLT		1
#define SPI_EVENT_RX_CMPLT		2
#define SPI_EVENT_OVR_ERR			3

/*
 * BIT POSITION OF RCC
 */
// RCC_APB1ENR 
#define RCC_APB1ENR_SPI2ENR			14
#define RCC_APB1ENR_SPI3ENR			15
// RCC_APB1RSTR
#define RCC_APB1RSTR_SPI2RST			14
#define RCC_APB1RSTR_SPI3RST			15
// RCC_APB2ENR
#define RCC_APB2ENR_SPI1ENR			12
//#define RCC_APB2ENR_SPI4ENR		13
// RCC_APB2RSTR
#define RCC_APB2RSTR_SPI1RST			12
//#define RCC_APB2RSTR_SPI4RST		13
/****************************************************************************

					APIs

******************************************************************************/
/*
 * Clock and Reset Control of GPIO
 */
/* Enable Clock for SPIx */
#define SPI1_PCLK_EN()					RCC_BASE->APB2ENR |= (1 << RCC_APB2ENR_SPI1ENR)
#define SPI2_PCLK_EN()					RCC_BASE->APB1ENR |= (1 << RCC_APB1ENR_SPI2ENR)
#define SPI3_PCLK_EN()					RCC_BASE->APB1ENR |= (1 << RCC_APB1ENR_SPI3ENR)
//#define SPI4_PCLK_EN()					RCC_BASE->APB2ENR |= (1 << 13)

/* Disable Clock for SPIx */
#define SPI1_PCLK_DIS()				RCC_BASE->APB2ENR &= (uint32_t)~(1 << RCC_APB2ENR_SPI1ENR)
#define SPI2_PCLK_DIS()				RCC_BASE->APB1ENR &= (uint32_t)~(1 << RCC_APB1ENR_SPI2ENR)
#define SPI3_PCLK_DIS()				RCC_BASE->APB1ENR &= (uint32_t)~(1 << RCC_APB1ENR_SPI3ENR)
//#define SPI4_PCLK_DIS()				RCC_BASE->APB2ENR &= (uint32_t)~(1 << 13)

/* Reset Register for SPIx */

/* Peripheral Clock setup */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDI);

/* GPIO Init and DeInit */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/* Data send */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len);

/* Receive data */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t len);

/* IRQ Configuration and ISR handling */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/*
 * Other Peripheral Control APIs
 */

void SPI_Start(SPI_RegDef_t *pSPIx);
void SPI_Stop(SPI_RegDef_t *pSPIx);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx);

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle);
void SPI_CloseReceiption(SPI_Handle_t *pSPIHandle);

/*
 * Static Function
*/

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_interrupt_handle(SPI_Handle_t *pSPIHandle);
#endif /* __STM32F407XX_SPI_DRIVER_H_ */
