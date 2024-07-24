#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "i2c_drive.h"

int main(void){

	i2c_init(2,i2c_FM);
	while(1){
		
	}
	return 0;
}
