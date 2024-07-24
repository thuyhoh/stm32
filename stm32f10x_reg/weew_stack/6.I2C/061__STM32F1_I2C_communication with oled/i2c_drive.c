#include "i2c_drive.h"

// find the peripheric
// activate Pins

// I2C pin
/*
I2C2
	SDA: PB11
	SCL: PB10	
I2C1:
	SDA: PB7
	SCL: PB6
*/

// setup and  activate i2c
// i2c_init();

void i2c_init(char i2c, unsigned int speed_mode){
	RCC->APB2ENR |= 1;
	
	if(i2c == 1){
		RCC->APB1ENR |= 0x200000;
		GPIOx_init(PB,6,OUT50,O_AF_OD);
		GPIOx_init(PB,7,OUT50,O_AF_OD);

		I2C1->CR1 |= 0x8000;
		I2C1->CR1 &= ~0x8000;
		
		I2C1->CR2 = 0x8;
		
		I2C1->CCR = speed_mode;
		
		I2C1->CR1 |= 1;
		
	}else{
		RCC->APB1ENR |= 0x400000;
		RCC->APB1ENR |= 0x200000;
		GPIOx_init(PB,10,OUT50,O_AF_OD);
		GPIOx_init(PB,11,OUT50,O_AF_OD);

		I2C2->CR1 |= 0x8000;
		I2C2->CR1 &= ~0x8000;
		
		I2C2->CR2 = 0x8;
		
		I2C2->CCR = speed_mode;
		
		I2C2->CR1 |= 1;
	}
}

// start step
void i2c_start(char i2c){
	if(i2c == 1){
		I2C1->CR1 |= 0x100;
		while(!(I2C1->SR1 & 1));
	}
	else{
		I2C2->CR1 |= 0x100;
		while(!(I2C2->SR1 & 1));
	}
}
// sending the address + R or W
void i2c_add(char i2c, char address, char RW){
	volatile int tmp;
	if(i2c == 1){
		I2C1->DR = (address|RW);
		while((I2C1->SR1 & 2) == 0);
		while(I2C1->SR1 & 2){
			tmp = I2C1->SR1;
			tmp = I2C1->SR2;
			if((I2C1->SR1 & 2) == 0){
				break;
			}
		}
	}
	else{
		volatile int tmp;
		if(i2c == 1){
		I2C2->DR = (address|RW);
		while((I2C2->SR1 & 2) == 0);
		while(I2C2->SR1 & 2){
			tmp = I2C2->SR1;
			tmp = I2C2->SR2;
			if((I2C2->SR1 & 2) == 0){
				break;
			}
		}
	}
	}
}
// sending data step
void i2c_data(char i2c, char data){
	if(i2c == 1){
		while((I2C1->SR1 & 0x80) == 0);
		I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0);
	}
	else{
		while((I2C2->SR1 & 0x80) == 0);
		I2C2->DR = data;
		while((I2C2->SR1 & 0x80) == 0);
	}
}
// stop step
void i2c_stop(char i2c){
	volatile int tmp;
	if(i2c == 1){
		tmp = I2C1->SR1;
		tmp = I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}
	else{
		tmp = I2C2->SR1;
		tmp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}
// 
void i2c_write(char i2c, char address, char *data){
	int i = 0;
	i2c_start(i2c);
	i2c_add(i2c,address, 0);
	while(data[i]){
		i2c_data(i2c,data[i]);
	}
	i2c_stop(i2c);
}

