#include "i2c_drive.h"
// 0x00 send cmd
// 0x40 send data

void oled_cmd_1byte(char i2c, int data);
void oled_cmd_2byte(char i2c, int data[]);
