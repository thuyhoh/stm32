#include "button.h"



/*--------------bnt function--------------*/
__weak void btn_pressing_callback(Button_Typdef *buttonx){
	
}
__weak void btn_release_callback(Button_Typdef *buttonx){
	// nha button
	
}

__weak void btn_press_short_callback(Button_Typdef *buttonx){
	// nhan nha nhanh button
	
}

__weak void btn_pressing_timeout_callback(Button_Typdef *buttonx){
	// nhan giu button
	
}	

void button_handler(Button_Typdef *buttonx){
	/*		loc nhieu 		*/
	uint8_t sta = HAL_GPIO_ReadPin(buttonx->GPIOx,buttonx->GPIO_Pin	);
	if(sta != buttonx->btn_filter){
		buttonx->btn_filter = sta;
		buttonx->is_debouncing = 1;
		buttonx->time_deboune = HAL_GetTick();
	}
	/*		 xac nhan			*/
	if(buttonx->is_debouncing && (HAL_GetTick() - buttonx->time_deboune) >= 15){
		buttonx->is_debouncing = 0;
		buttonx->btn_current = buttonx->btn_filter;
	}
	/*			xu li	nhan nha		*/
	if(buttonx->btn_current != buttonx->btn_last){
		if(buttonx->btn_current == 0){
			buttonx->is_press_timeout = 1;
			btn_pressing_callback(buttonx);
			buttonx->time_start_press = HAL_GetTick();
		}else{
			if(HAL_GetTick() - buttonx->time_start_press <= 1000){
				btn_press_short_callback(buttonx);
				buttonx->is_press_timeout = 0;
			}
			btn_release_callback(buttonx);
		}
		buttonx->btn_last = buttonx->btn_current;
	}
	
	/*			xu li nhanh giu			*/
	if(buttonx->is_press_timeout &&HAL_GetTick() - buttonx->time_start_press >= 3000){
		btn_pressing_timeout_callback(buttonx);
		buttonx->is_press_timeout = 0;
	}
}

void Button_Init(Button_Typdef *buttonx,GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	buttonx->GPIOx = GPIOx;
	buttonx->GPIO_Pin = GPIO_Pin;
}
