#include "stm32f10x.h"                  // Device header

#include "gpio_drive.h"
#include "systick_drive.h"

#define adc1 1
#define adc2 2

char adc_init(char adc, short port, short pin);
char adc_check(char adc);
int adc_rx(char adc);

void ADC_Wd_Init(char adc, short Port, short Pin, short H_thread, short L_thread);

void ADC_Mult_Ch_Init(char adc, char channel_size, char *channel_arr);
void ADC_Mult_Ch_rx(char adc, char *channel_arr, char channel_size, int * analog_rx);

// interrupt function
void ADC_IT_Init(char adc, short Port, short Pin);
__WEAK void ADC1_2_IRQHanddler(void);
