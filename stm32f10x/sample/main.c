#include "main.h"
#include "CortexM3.h"


int main(void)
{
	NVIC_RegDef_t *pNVIC = NVIC_BASEPTR;
	pNVIC->IABR[0] = 0x01;

	while(1)
	{
		
	}
// return 0; 
}
