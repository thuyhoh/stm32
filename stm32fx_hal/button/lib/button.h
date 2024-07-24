#ifndef BUTTON_H
#define BUTTON_H
#include "main.h"
typedef struct {
	uint8_t 			btn_current;
	uint8_t 			btn_last;
	uint8_t 			btn_filter;
	uint8_t 			is_debouncing;
	uint8_t 			is_press_timeout;
	uint32_t 			time_deboune;
	uint32_t 			time_start_press;
	GPIO_TypeDef 	*GPIOx;
	uint16_t 			GPIO_Pin;
}Button_Typdef;
void Button_Init(Button_Typdef *buttonx,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void button_handler(Button_Typdef *buttonx);
#endif
