#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "systick_drive.h"
#include "SPI_drive.h"
#include "nokia5110lcd.h"

/*	nokia 5110 lcd pin
	1 RST reset pin  	-> PA0
	2 CE 	chip set   	-> PA4
	3 DC 	data/comand	-> PA1
	4 DIN	data in			-> PA7 MOSI
	5 CLK clock				-> PA5 SCLK
	6 VCC							
	7 BL blik pin			-> PA2
	8 GND
*/

void n5110_init(unsigned short Spi_Channel){
	systick_init();

// setup reset pin
	GPIOx_init(PA,0,OUT50,O_GP_PP);
// set RST HIGH and wait 10ms set low and 
	GPIOx_W(PA,0,HIGH);
	DelayMs(10);
	GPIOx_W(PA,0,LOW); // reset of screem
	DelayMs(10);
	GPIOx_W(PA,0,HIGH);
// setup DC pin and set low
	GPIOx_init(PA,1,OUT50,O_GP_PP);
	GPIOx_W(PA,1,LOW);
// setup screenlight pin and test ligh with tonggle
	GPIOx_init(PA,2,OUT50,O_GP_PP);

// setup spi
	SPI_init(Spi_Channel);
	
// extended instruction set and set voltage
	SPI_Tx(Spi_Channel,0x21);	// -> funtion set: extended instruction
	SPI_Tx(Spi_Channel,0xC0); // -> set voltage tang do tuong phan  
// basic instruction set and config display controll
	SPI_Tx(Spi_Channel,0x20);	// -> funtion set: basic set
	SPI_Tx(Spi_Channel,0x0C); // -> display normal mode 
}
/*
void n5110(n5110_t n5110_mgr){
	// setup reset pin
	GPIOx_init(n5110_mgr.RST.Port,n5110_mgr.RST.Pin,OUT50,O_GP_PP);
	// set RST HIGH and wait 10ms set low and 
	GPIOx_W(n5110_mgr.RST.Port,n5110_mgr.RST.Pin,HIGH);
	DelayMs(10);
	GPIOx_W(n5110_mgr.RST.Port,n5110_mgr.RST.Pin,LOW); // reset of screem
	DelayMs(10);
	GPIOx_W(n5110_mgr.RST.Port,n5110_mgr.RST.Pin,HIGH);
	// setup DC pin and set low
	GPIOx_init(n5110_mgr.DC.Port,n5110_mgr.DC.Pin,OUT50,O_GP_PP);
	GPIOx_W(n5110_mgr.DC.Port,n5110_mgr.DC.Pin,LOW);
	// setup screenlight pin and test ligh with tonggle
	GPIOx_init(n5110_mgr.BL.Port,n5110_mgr.BL.Pin,OUT50,O_GP_PP);
	
	// setup spi
	SPI_init(n5110_mgr.Spi_Channel);
	// extended instruction set and set voltage
	SPI_Tx(n5110_mgr.Spi_Channel,0x21);	// -> funtion set: extended instruction
	SPI_Tx(n5110_mgr.Spi_Channel,0xC0); // -> set voltage tang do tuong phan  
// basic instruction set and config display controll
	SPI_Tx(n5110_mgr.Spi_Channel,0x20);	// -> funtion set: basic set
	SPI_Tx(n5110_mgr.Spi_Channel,0x0C); // -> display normal mode 
}
*/
void n5110_print(unsigned short Spi_Channel,short Ypos, short Xpos, char str[]){
	// clear display
	n5110_pos(Spi_Channel,0,0);
	n5110_clear(Spi_Channel);
	// write string into n5110
	n5110_pos(Spi_Channel,Xpos,Ypos);
	int i,j;
	i = 0;
	GPIOx_W(PA,1,HIGH);
	while(str[i]){
		for(j = 0; j<5;j++){
			SPI_Tx(Spi_Channel,charset[(int)(str[i]-32)][j]);
		}
		i++;
	}
	GPIOx_W(PA,1,LOW);
	
	
	// clear the string
}

// string positon
void n5110_pos(unsigned short Spi_Channel,short Xpos, short Ypos){
	GPIOx_W(PA,1,LOW);
	SPI_Tx(Spi_Channel,0x20);	// -> funtion set: basic set
	SPI_Tx(Spi_Channel,(char)(0x40 | Ypos)); // -> set vi tri cua thong tin o hang Ypos
	SPI_Tx(Spi_Channel,(char)(0x80 | Xpos)); // -> set vi tri cua thong tin o hang Xpos
	GPIOx_W(PA,1,HIGH);
}


// n5110_clear: clear display
void n5110_clear(unsigned short Spi_Channel){
	GPIOx_W(PA,1,HIGH);
	int i;
	for(i = 0; i< 504;i++){
		SPI_Tx(Spi_Channel,0x00);
	}
}



// clear buffer
void clear_buffer(unsigned char scream_buffer[][84]){
	int i , j;
	for(i = 0; i < 6;i++){
		for(j = 0; j< 84;j++){
			scream_buffer[i][j] = 0;
		}
	}
}

//
void print_buffer(unsigned char scream_buffer[][84]){
	n5110_clear(1);
	n5110_pos(1,0,0);
	int i,j;
	GPIOx_W(PA,1,HIGH);// data and command
	for(i = 0; i < 6;i++){
		for(j = 0; j< 84; j++){
			SPI_Tx(1,scream_buffer[i][j]);
		}
	}
	GPIOx_W(PA,1,LOW);
}

// update buffer
void update_buffer(ImgType img, unsigned short img_nums, unsigned char scream_buffer[][84]){
	int x_cnt, y_cnt, endx, endy,cnt;
	// endx
	if((img.W + img.X_pos) > 84){
		endx = 83;
	}else{
		endx = img.W + img.X_pos - 1;
	}
	// endy
	if((img.H + img.Y_pos) > 5){
		endy = 5;
	}else{
		endy = img.H + img.Y_pos - 1;
	}
	//
	cnt = 0;
	for(y_cnt = img.Y_pos; y_cnt <= endy; y_cnt++){
		for(x_cnt = img.X_pos; x_cnt <= endx; x_cnt++){
			cnt = (y_cnt - img.Y_pos)*img.W + (x_cnt - img.X_pos); // phan tu thu bao nhieu cua mang
			scream_buffer[y_cnt][x_cnt] = img.image[img_nums][cnt];// img thu may trong struct;
			
		}			
	}
}

// chen them srting bao trong buffer
void update_str_buffer(short Ypos, short Xpos, char str[], unsigned char screen_buffer[][84]){
	int i,j, cnt_col, cnt_row;
	cnt_col = Xpos;
	cnt_row = Ypos;
	i = 0;
	while(str[i]){
		if(cnt_row > 5) break;
		for(j = 0; j< 5;j++){
			screen_buffer[cnt_row][cnt_col] = charset[str[i] - 32][j];
			if(cnt_col + 1> 83){
				if((cnt_row + 1)>5) break;
				else{
					cnt_row++;
					cnt_col = Xpos;
				}
			}else{
				cnt_col++;
			}
		}
		i++;
	}
}
