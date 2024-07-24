#ifndef RTC_DS3231_H
#define RTC_DS3231_H
#include "main.h"

#define RTC_ADDR 0x68<<1

typedef struct{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t date;
}Date_Time;

void rtc_write_time(I2C_HandleTypeDef *hi2c, Date_Time *dt);
void rtc_read_time(I2C_HandleTypeDef *hi2c, Date_Time *dt);
uint8_t BCD2Decimal(uint8_t num_bcd);
uint8_t Decimal2BCD(uint8_t num_dec);
uint16_t rtc_read_temp(I2C_HandleTypeDef *hi2c);

#endif
