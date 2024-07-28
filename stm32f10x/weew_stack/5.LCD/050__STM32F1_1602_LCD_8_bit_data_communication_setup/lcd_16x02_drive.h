#include "stm32f10x.h"
#include "gpio_drive.h"
#include "systick_drive.h"
#include "stdlib.h"
struct lcd16x2_pins{
	unsigned short Port;
	unsigned short RS;
	unsigned short Rw;
	unsigned short E;
	unsigned short DB0;
	unsigned short DB1;
	unsigned short DB2;
	unsigned short DB3;
	unsigned short DB4;
	unsigned short DB5;
	unsigned short DB6;
	unsigned short DB7;
};

struct lcd16x2_pins *settup_pins;

void setup_lcd_pin(unsigned short Port,	unsigned short RS,unsigned short Rw,	unsigned short E,	unsigned short DB0,	unsigned short DB1,	unsigned short DB2,	unsigned short DB3,	unsigned short DB4,	unsigned short DB5,	unsigned short DB6,	unsigned short DB7);
void pin_output(unsigned short start, unsigned short end);
void lcd_rs(unsigned short HIGH_LOW);
void lcd_rw(unsigned short HIGH_LOW);
void lcd_e(unsigned short HIGH_LOW);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_init(void);
void lcd_send(char* str);
void lcd_pos(unsigned short xpos, unsigned short ypos);
void lcd_msg(char* str, unsigned short xpos, unsigned short ypos);
