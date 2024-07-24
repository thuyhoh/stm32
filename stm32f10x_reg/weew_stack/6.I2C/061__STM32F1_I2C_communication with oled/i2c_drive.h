#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"

#define i2c_FM 0x2d
#define i2c_SM 0xB4

void i2c_init(char i2c, unsigned int speed_mode);
void i2c_write(char i2c, char address, char *data);
