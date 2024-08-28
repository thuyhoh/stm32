/****************************************************************


****************************************************************/
#include "CortexMx.h"
#include "CortexMx_SysTick_Timer.h"

static SysTick_RegDef_t *pSTK;
static uint32_t CoreClock = 9000000; /* <! f_AHB Max = 72MHz> */


/* Systick Timer */
/****************************************************************************
 * @fn	  				-  SysTick_LoadValue

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
static void SysTick_LoadValue(uint32_t CountValue)
{
	// Reset value in LOAD register
	pSTK->LOAD &= 0x000; 
	// Set value in LOAD register
	pSTK->LOAD  = CountValue;
}

/****************************************************************************
 * @fn	  				-  SysTick_LoadValue

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void SysTick_Init(SysTick_Config_t *STK_Config)
{
	// reset STK->CTRL register
	pSTK->CTRL &= 0x00000000;
	
	// Source of Clock
	if(STK_Config->STK_ClockSource == STK_CLOCK_AHB_DIVIDE_1)
	{
		CoreClock = CoreClock * 8;
		pSTK->CTRL |= STK_CLOCK_AHB_DIVIDE_1;
	}
	// SysTick Mode
	if(STK_Config->STK_Mode == STK_IT_MODE)
	{
		// Interrupt mode
		pSTK->CTRL |= STK_IT_MODE;
	}
	
	SysTick_LoadValue(STK_Config->STK_CountValue);
}

/****************************************************************************
 * @fn	  				-  SysTick_DeInit

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void SysTick_DeInit(void)
{
	// reset STK->CTRL register
	pSTK->CTRL &= 0x00000000;
	
	// Reset value in LOAD register
	pSTK->LOAD &= 0x000;
}

/****************************************************************************
 * @fn	  				-  SysTick_StartCount

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void SysTick_StartCount(void)
{
	// Enable Counter
	pSTK->CTRL |= 1;
}

/****************************************************************************
 * @fn	  				-  Delayms

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
static void Delayms(void)
{
	SysTick_LoadValue((CoreClock - 1) / 1000);
	SysTick_StartCount();
	while((pSTK->CTRL & 0x10000) == 0){}
}

/****************************************************************************
 * @fn	  				-  SysTick_Delayms

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void SysTick_Delayms(uint32_t ms)
{
	while(ms)
	{
		Delayms();
		ms--;
	}
}

/****************************************************************************
 * @fn	  				-  Delayus

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
static void Delayus(void)
{
	SysTick_LoadValue((CoreClock -1) / 1000000);
	SysTick_StartCount();
	while((pSTK->CTRL & 0x10000) == 0){}
}

/****************************************************************************
 * @fn	  				-  SysTick_Delayus

 * @brief  				-  

 * @param[]  			-  
 * @param[]  			- 
 * @param[]  			- 

 * @return 				- 

 * @note	  			- 
****************************************************************************/
void SysTick_Delayus(uint32_t us)
{
	while(us)
	{
		Delayus();
		us--;
	}
}
