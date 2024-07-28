#include "stm32f10x.h"                  // Device header
#include "adc.h"

static int adc_val;
int main(void)
{
	
	adc_init(adc1,PA,0);
	while(1)
	{
		if(adc_check(adc1))
		{
				adc_val = adc_rx(adc1);
		}
		
	}
		
	//return 0;
}
