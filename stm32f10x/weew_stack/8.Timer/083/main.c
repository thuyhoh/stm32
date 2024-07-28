#include "stm32f10x.h"

int main(void)
{
	int a = 60;
	int volatile b = a/0;
	while(1)
	{
		
	}
	// return 0;
}

void UsageFault_Handler(void)
{
	int a;
}
