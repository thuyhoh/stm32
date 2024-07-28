#include"adc.h"

// Initializing the ADC for the STM32F1
uint8_t ADC_Base_init(uint8_t adc, short port, short pin)
{
	uint8_t channel;
	uint8_t result = 0;
	if(port == PA)
	{
		if(pin < 8)
		{
			result = 1;
			channel = pin;
		}
	}
	else if (port == PB)
	{
		if(pin<2)
		{
		result = 1;
		channel = 8 + pin;
		}
	}
	else if (port == PC)
	{
		if(pin<6)
		{
		result = 1;
		channel = 10 + pin;
		}
	}
	if(result)
	{
		init_GP(port,pin,IN,I_AN);
		if(adc == adc1)
		{
			RCC->APB2ENR |= 0x201;
			ADC1->CR2 = 0;
			ADC1->SQR3 = channel;
			ADC1->CR2 |= 1;
			DelayMs(100);
			ADC1->CR2 |= 1;
			ADC1->CR2 |= 2;
		}
		else if(adc == adc2)
		{
			RCC->APB2ENR |= 0x401;
			ADC2->CR2 = 0;
			ADC2->SQR3 = channel;
			ADC2->CR2 |= 1;
			DelayMs(100);
			ADC2->CR2 |= 1;
			ADC2->CR2 |= 2;
		}
	}
	return result ;
}

// Reading the flag that says the data is ready
uint8_t ADC_Check(uint8_t adc)
{
	uint8_t check = 0;
	if(adc == adc1)
		{
			if(ADC1->SR & 2)
			{
				check  = 1;
			}
		}
		else if(adc == adc2)
		{
			if(ADC2->SR & 2)
			{
				check  = 1;
			}
		}
	
	
	return check;
}

// Reading the ADC value 
int Get_ADCx(uint8_t adc)
{
	int result = 0;
	int data = 0;
	if(adc == adc1)
	{
		data = ADC1->DR;
	} 
	else if(adc == adc2)
	{
		data = ADC2->DR;
	}
	
	result = (data*1000)/0xfff;
	
	
	return result;
}

// 
void ADC_Wd_Init(uint8_t adc, short Port, short Pin, short H_thread, short L_thread)
{
	adc_init(adc, Port, Pin);
	
	if(adc == 1)
	{
		ADC1->CR1 |= 0x800000; // Enable the watchdog
		ADC1->HTR |= H_thread;
		ADC1->LTR |= L_thread;
		ADC1->CR1 |= 0x40;
	}
	else if(adc == 2)
	{
		ADC2->CR1 |= 0x800000; // Enable the watchdog
		ADC2->HTR |= H_thread;
		ADC2->LTR |= L_thread;
		ADC2->CR1 |= 0x40;
	}
	
}

//
void ADC_Mult_Ch_Init(uint8_t adc, uint8_t channel_size, uint8_t *channel_arr)
{
	uint8_t i;
	for(i = 0; i< channel_size; i++)
	{
		if(channel_arr[i] < 8)
		{
			init_GP(PA,channel_arr[i],IN, I_AN);
		}
		else if(channel_arr[i] < 10)
		{
			init_GP(PB, channel_arr[i] - 8, IN, I_AN);
		}
		else if(channel_arr[i] < 16)
		{
			init_GP(PC, channel_arr[i] - 10, IN, I_AN);
		}
	}
	if(adc == adc1)
		{
			RCC->APB2ENR |= 0x201;
			ADC1->CR2 = 0;
			ADC1->SQR1 = channel_arr[0];
			ADC1->CR2 |= 1;
			DelayMs(100);
			ADC1->CR2 |= 1;
			ADC1->CR2 |= 2;
		}
		else if(adc == adc2)
		{
			RCC->APB2ENR |= 0x401;
			ADC2->CR2 = 0;
			ADC1->SQR1 = channel_arr[0];
			ADC2->CR2 |= 1;
			DelayMs(100);
			ADC2->CR2 |= 1;
			ADC2->CR2 |= 2;
		}	
}

// 
void ADC_Mult_Ch_rx(uint8_t adc, uint8_t *channel_arr, uint8_t channel_size, int * analog_rx)
{
	uint8_t i = 0;

	if(adc == adc1)
	{
		while(1)
		{
			if(adc_check(adc1))
			{
				analog_rx[i] = ADC1->DR;
				i++;
			}
			if(i == channel_size)
			{
				ADC1->SQR1 = channel_arr[0];
				break;
			}
			else
			{
				ADC1->SQR1 = channel_arr[i];
			}
		}
	}
	else if(adc == adc2)
	{
		while(1)
		{
			if(adc_check(adc2))
			{
				analog_rx[i] = ADC2->DR;
				i++;
			}
			if(i == channel_size)
			{
				ADC2->SQR1 = channel_arr[0];
				break;
			}
			else
			{
				ADC2->SQR1 = channel_arr[i];
			}
		}
	}
}

//
// interrupt init
void ADC_IT_Init(uint8_t adc, short Port, short Pin)
{
	adc_init(adc, Port, Pin);
	if(adc == adc1){
		ADC1->CR1 |= 0x20;
		ADC1->CR1 |= 0x40;
	}
	else if(adc == 2)
	{
		ADC2->CR1 |= 0x20; // Setting the Interrupt
		ADC2->CR1 |= 0x40;
	}
	__disable_irq();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__enable_irq();
}
//
__WEAK void ADC1_2_IRQHanddler(void)
{
    // thuc hien ngat
}
