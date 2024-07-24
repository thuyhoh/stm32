#include "oled_i2c_drive.h"
#include "i2c_drive.h"


// oled_cmd 1byte
void oled_cmd_1byte(char i2c, int data){
	i2c_start(i2c);
	i2c_add(i2c,0x78, 0);// 0x78 is the primary  address
	i2c_data(i2c,0x00);
	i2c_data(i2c,data);
	i2c_stop(i2c);
}

// oled_cmd 2 byte
void oled_cmd_2byte(char i2c, int data[]){
	int i = 0;	
	i2c_start(i2c);
	i2c_add(i2c,0x78, 0);// 0x78 is the primary  address
	i2c_data(i2c,0x00);
	for(i = 0; i < 2; i++)	i2c_data(i2c,data);
	i2c_stop(i2c);
}
	
// oled_init()
void oled_init(char i2c){
	i2c_init(i2c,i2c_SM);
	char cmd[] = {0x48,0x3F};
	oled_cmd_2byte(i2c,cmd);
	char cmd1[] = {0xD3,0x00};
	oled_cmd_2byte(i2c,cmd1);
	
	oled_cmd_1byte(i2c,0x40);
	
	oled_cmd_1byte(i2c,0xA1);
	
	oled_cmd_1byte(i2c,0xC8);
	
	char cmd2[] = {0xDA,0x02};
	oled_cmd_2byte(i2c,cmd1);
	
	char cmd3[] = {0x81,0x7F};
	oled_cmd_2byte(i2c,cmd3);

	oled_cmd_1byte(i2c,0xA4);
	oled_cmd_1byte(i2c,0xA6);
	
	char cmd4[] = {0xD5,0x80};
	oled_cmd_2byte(i2c,cmd4);
	
	char cmd5[] = {0x8D,0x14};
	oled_cmd_2byte(i2c,cmd5);
	
	oled_cmd_1byte(i2c,0xAF);
	
	char cmd6[] = {0x20,0x10};
	oled_cmd_2byte(i2c,cmd6);
}

void oled_data(char i2c, char data){

}

void oled_pos(char i2c, char Xpos, char Ypos){
	oled_cmd_1byte(i2c,0x00 + (0x0F&Xpos));
	oled_cmd_1byte(i2c,0x10 + (0x0F&(Xpos>>4)));
	oled_cmd_1byte(i2c,0xB0 + Ypos);
}

void oled_blank(char i2c){
	oled_pos(i2c,0,0);
	int i, j;
	for(i = 0; i<128;i++){
		for(j = 0; j<8; j++){
			oled_data(i2c,0x00);
		}
	}
	oled_pos(i2c,0,0);
}
