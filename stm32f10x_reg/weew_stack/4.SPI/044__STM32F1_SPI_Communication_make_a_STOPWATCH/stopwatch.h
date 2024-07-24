#include "stm32f10x.h"                  // Device header
#include "SPI_drive.h"
#include "gpio_drive.h"
#include "systick_drive.h"
#include "nokia5110lcd.h"

void sw_init(void);
void sw_reset(unsigned short *sw_rst, unsigned long *millis);
void sw_stop(unsigned int *counter);
void digit_check(unsigned int time_cst,char number[],char time[]);
void sw_start(unsigned long *millis, unsigned int *counter, char *number, char *time);
	