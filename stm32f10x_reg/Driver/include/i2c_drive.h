#ifndef __I2C_DRIVE_H
#define __I2C_DRIVE_H
#include "stm32f10x.h"
#include "gpio_drive.h"
#include "stdint.h"
typedef enum{
    I2C_CHANNE_1 = 1,
    I2C_CHANNE_2
}I2C_CHANNEL_typedef;

typedef enum{
  I2C_TRANSMIT_MODE = 0,
	I2C_RECEIVE_MODE = 1
	
}R_T_typedef;

typedef enum{
    I2C_FM = 0x2d,
    I2C_SM = 0xB4
}I2C_SPEED_MODE_typedef;

typedef enum
{
	SLAVE_10BIT_ADDRESS,
	SLAVE_7BIT_ADDRESS
}Slave_xbit_Address;

typedef enum
{
	I2C1_CLOCK_ENABLE = 0x200000,
	I2C2_CLOCK_ENABLE = 0x400000
}Enable_Clock_I2C;

#define RESET_I2C 0x8000

void I2C_Master_Init(I2C_TypeDef *i2c, I2C_SPEED_MODE_typedef speed_mode);

void I2C_Master_Transmit(I2C_TypeDef *i2c, Slave_xbit_Address Xbit, uint16_t Slave_Address, uint8_t *Data);

uint8_t I2C_Master_Receive(I2C_TypeDef *i2c, Slave_xbit_Address Xbit, uint16_t Slave_Address);

#endif
