#include "rtc_ds3231.h"

uint8_t BCD2Decimal(uint8_t num_bcd)
{
	return (num_bcd&0x0f) + (num_bcd >> 4)*10;
}

uint8_t Decimal2BCD(uint8_t num_dec)
{
	return (num_dec / 10) | (num_dec % 10)<<4;
}

void rtc_write_time(I2C_HandleTypeDef *hi2c, Date_Time *dt)
{
	uint8_t timeout = 100;
	uint8_t size = 8;
	uint8_t buff[8]; 
	// buff[0]-> dia chi/ buf[>0] -> data
	buff[0] = Decimal2BCD(0x00);
	buff[1] = Decimal2BCD(dt->second);
	buff[2] = Decimal2BCD(dt->minute);
	buff[3] = Decimal2BCD(dt->hour);
	buff[4] = Decimal2BCD(dt->day);
	buff[5] = Decimal2BCD(dt->date);
	buff[6] = Decimal2BCD(dt->month);
	buff[7] = Decimal2BCD(dt->year);

	HAL_I2C_Master_Transmit(hi2c, RTC_ADDR, buff, size, timeout); 
}

void rtc_read_time(I2C_HandleTypeDef *hi2c, Date_Time *dt)
{
	uint8_t data[7];
	uint8_t add_reg = 0x00;
	// transmit addres
	HAL_I2C_Master_Transmit(hi2c, RTC_ADDR, &add_reg, 1, 100);
	// receive	
	HAL_I2C_Master_Receive(hi2c, RTC_ADDR, data, 7, 100);
	dt->second 	= BCD2Decimal(data[0]);
	dt->minute 	= BCD2Decimal(data[1]);
	dt->hour 		= BCD2Decimal(data[2]);
	dt->day 		= BCD2Decimal(data[3]);
	dt->date 		= BCD2Decimal(data[4]);
	dt->month 	= BCD2Decimal(data[5]);
	dt->year 		= BCD2Decimal(data[6]);
}

uint16_t rtc_read_temp(I2C_HandleTypeDef *hi2c)
{
	uint8_t add_reg = 0x11;
	uint8_t data[2];
	// transmit addres
	HAL_I2C_Master_Transmit(hi2c, RTC_ADDR, &add_reg, 1, 100);
	HAL_I2C_Master_Receive(hi2c, RTC_ADDR, data, 2, 100);
	uint16_t temp = (uint16_t)((data[0]<<2) | (data[1]>>6));
	return temp;
}
