/*
 *  file name  : stm32f407xx_gpio_driver.h
 *  Created on : Aug 27, 2024
 *  Author     : THUY
 */

#ifndef __STM32F407XX_I2C_DRIVER_H_
#define __STM32F407XX_I2C_DRIVER_H_

#include "stm32f407xx.h"
#include "stm32f407xx_rcc_driver.h"
#include "stm32f407xx_gpio_driver.h"

typedef struct
{
	
}I2C_Config_t;

typedef struct
{
	I2C_Config_t I2C_Config;
	I2C_RegDef_t *pI2Cx;
}I2C_Handle_t;

/* BIT POSITION */
// CR1 Register
#define I2C_CR1_PE					0
#define I2C_CR1_SMBUS				1
#define I2C_CR1_SMBTYPE			3
#define I2C_CR1_ENARP				4
#define I2C_CR1_ENPEC				5
#define I2C_CR1_ENGC				6
#define I2C_CR1_NOSTRETCH		7
#define I2C_CR1_START				8	
#define I2C_CR1_STOP				9
#define I2C_CR1_ACK					10
#define I2C_CR1_POS					11
#define I2C_CR1_PEC					12
#define I2C_CR1_ALERT				14
#define I2C_CR1_SWRST				15

// CR2 Register
#define I2C_CR2_FREQ /*[5:0]*/		0
#define I2C_CR2_ITERREN						8
#define I2C_CR2_ITEVTEN						9
#define I2C_CR2_ITBUFEN						10	
#define I2C_CR2_DMAEN							11
#define I2C_CR2_LAST							12

// SR1 Register
#define I2C_SR1_SB							0
#define I2C_SR1_ADDR						1
#define I2C_SR1_BTF							2
#define I2C_SR1_ADD10						4
#define I2C_SR1_STOPF						5	
#define I2C_SR1_RxNE						6
#define I2C_SR1_TxE							7
#define I2C_SR1_BERR						8
#define I2C_SR1_ARLO						9
#define I2C_SR1_AF							10
#define I2C_SR1_OVR							11
#define I2C_SR1_PECERR					12
#define I2C_SR1_TIMEOUT					14
#define I2C_SR1_SMBALERT				15

// SR2 Register
#define I2C_SR2_MSL							0
#define I2C_SR2_BUSY						1
#define I2C_SR2_TRA							2
#define I2C_SR2_GENCALL					3
#define I2C_SR2_SMBDEFAULT			4
#define I2C_SR2_SMBHOST					5
#define I2C_SR2_DUALF						6
#define I2C_SR2_PEC	/*[15:7]*/	7

// CCR Register
#define I2C_CCR_DUTY						14
#define I2C_CCR_FS							15

/****************************************************************

****************************************************************/
/* Peripheral Clock setup */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t ENorDI);

/* GPIO Init and DeInit */
void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);

/* Receive and Transmit Data  */
void I2C_SendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t len);
void I2C_ReceiveData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t len);


/* IRQ Configuration and ISR handling */
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void I2C_IRQHandling(I2C_Handle_t *pI2CHandle);

#endif /* __STM32F407XX_I2C_DRIVER_H_ */
