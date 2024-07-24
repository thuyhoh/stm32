#include "lcd_16x02_drive.h"
/*
	pin setup 
	PA8  -> RS
	PA9  -> RW
	PA10 -> E
	PA0  -> DB0
	PA1  -> DB1
	PA2  -> DB2
	PA3  -> DB3
	PA4  -> DB4
	PA5  -> DB5
	PA6  -> DB6
	PA7  -> DB7	
*/


void setup_lcd_pin(unsigned short Port,	unsigned short Rs,unsigned short Rw,	unsigned short E,	unsigned short DB0,	unsigned short DB1,	unsigned short DB2,	unsigned short DB3,	unsigned short DB4,	unsigned short DB5,	unsigned short DB6,	unsigned short DB7){
	settup_pins = (struct lcd16x2_pins*)malloc(sizeof(struct lcd16x2_pins));
	settup_pins->Port = Port;
	settup_pins->RS = Rs;
	settup_pins->Rw = Rw;
	settup_pins->E = E;
	settup_pins->DB0 = DB0;
	settup_pins->DB1 = DB1;
	settup_pins->DB2 = DB2;
	settup_pins->DB3 = DB3;
	settup_pins->DB4 = DB4;
	settup_pins->DB5 = DB5;
	settup_pins->DB6 = DB6;
	settup_pins->DB7 = DB7;
	

}


void pin_output(unsigned short start, unsigned short end){
	short i;
	for(i = start; i < end; i++){
		GPIOx_init(PA,i,OUT50,O_GP_PP);
	}
}

void lcd_rs(unsigned short HIGH_LOW){
	GPIOx_W(PA,8,HIGH_LOW);
}

void lcd_rw(unsigned short HIGH_LOW){
	GPIOx_W(PA,9,HIGH_LOW);
}

void lcd_e(unsigned short HIGH_LOW){
	GPIOx_W(PA,10,HIGH_LOW);
}

void lcd_data(unsigned char data){
	pin_output(0,11);
	lcd_rs(HIGH);
	lcd_rw(LOW);
	DelayMillis();
	lcd_e(HIGH);
	DelayMillis();
	GPIOA->ODR &= 0xff00;
	GPIOA->ODR |= data;
	DelayMillis();
	lcd_e(LOW);
}

void lcd_cmd(unsigned char cmd){
	pin_output(0,11);
	lcd_rs(LOW);
	lcd_rw(LOW);
	DelayMillis();
	lcd_e(HIGH);
	DelayMillis();
	GPIOA->ODR &= 0xff00;
	GPIOA->ODR |= cmd;
	DelayMillis();
	lcd_e(LOW);
}

void lcd_init(void){
	pin_output(0,11);
	DelayMs(20);
	lcd_cmd(0x3C);// function set display (8bit - 2line - 5x11 dot)
	DelayMs(5);
	lcd_cmd(0x0C);// display on 
	DelayMs(5);
	lcd_cmd(0x01);// clear display 
	DelayMs(5);
	lcd_cmd(0x02);// get back to initial address 
	DelayMs(5);
}

void lcd_send(char* str){
	int i = 0;
	while(*(str+i) != '\0'){
		lcd_data(*(str+i));
		i++;
		DelayMs(1);
	}
}

void lcd_pos(unsigned short xpos, unsigned short ypos){
	xpos = xpos - 1;
	if(ypos == 1){
		lcd_cmd(0x80 | xpos);
	}
	else{
		lcd_cmd(0xC0 | xpos);
	}
}

void lcd_msg(char* str, unsigned short xpos, unsigned short ypos){
	lcd_pos(xpos,ypos);
	lcd_send(str);
}

