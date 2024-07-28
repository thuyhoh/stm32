/*
 * File     : 	systick_time.c
 * Author   :   Nguyen Trong Thuy
 * date     :   17/2/2024
 * update   :   change code 
 * document :   PM0214-datasheet
*/

#include "systick_time.h"
#include "stm32f10x.h"                  // Device header

/*
	Thanh ghi: SysTick_reg
*** SysTick->CTRL (0xE000E010) SysTick control and status register:
		bit 0: ENABLE (Counter enable): bit kich hoat bo dem 
				- Khi duoc set 1, bo dem tai gia tri RELOAD tu thanh ghi SysTick->LOAD va sau do dem nguoc
	    	    khi dem den 0 thi COUNTFLAG(bit 16) = 1; tuy chon xac nhan cua SysTick phu thuoc vao gt TICKINT(bit 1)
				sau do tai lai gt RELOAD va tiep tuc dem lai
			0: Counter disabled
			1: Counter enabled
			
		bit 1: TICKINT (SysTick exception request enable): bit cho phep ngat
			0: Counting down to zero does not assert the SysTick exception request. // dem xuong toi 0 ko can xac nhan yeu cau ngoai le SysTick 
			1: Counting down to zero to asserts the SysTick exception request.      // Ðem nguoc ve 0 can xac nhan yêu cau ngoai le SysTick
			note: phan mem su dung COUNTFLAG xac dinh SysTick co dem den 0 hay ko
			
		bit 2: CLKSOURCE (Clock source selection): bit chon nguon xung clock			
			0: AHB/8					// 	su dung xung stm/8
			1: Processor clock (AHB)	//	su dung xung hoat dong cua stm
			
		bit 16: COUNTFLAG: bit flag dem
			Return 1 neu SysTick->LOAD dem den 0 ke tu khi lan cuoi cung duoc doc

*************************************************************************************************************************************************			

*** SysTick->LOAD (0xE000E014) SysTick reload value register:
		bit 0-23: RELOAD value
				- Thanh ghi LOAD chi dinh gia tri bat dau de tai vao thanh ghi SysTick->VAL khi bo dem duoc kich hoat va khi dem den 0.
				Gia tri RELOAD trong pham vi 0x00000001 - 0x00FFFFFF. note: gt RELOAD co the bang 0 nhung khong co y nghia
				* Caculate RELOAD_value: 
					+ de tao bo dem thoi gian sau N xung nhip thi gia tri RELOAD can la N-1.
					+ de cung cap 1 ngat SysTick sau do tre N xung nhip bo xu ly, gia tri RELOAD can la N
					Ex: muon tao ra do tre la 1ms thi can 72000 xung clock -> gia tri RELOAD = 72000 - 1

*************************************************************************************************************************************************			

*** SysTick->VAL(0xE000E018) SysTick current value register: 
		bit 0-23: CURRENT (Current counter value)
				- thanh ghi chua gia tri hien tai cua bo dem SysTick. Cac lan doc tra ve gia tri hien tai cua bo dem SysTick
				Viec ghi bat cu gia tri nao vao trong thanh ghi cung se xoa truong ve 0 va cung xoa COUNTFLAG(bit 16-SysTick->CTRL) ve 0

*/

#include "stm32f10x.h" 
#include "systick_time.h"

void SysTick_init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
}

void SysTick_ISR(void){
	// reset reg
	SysTick->CTRL = 0; 
	SysTick->LOAD = 0;
	// setup ISR_int
	__disable_irq();
	SysTick->LOAD = 72000;
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;
	/*
		SysTick->CTRL |= 1;
		SysTick->CTRL |= 1 << 2;
		SysTick->CTRL |= 1 << 3;
	*/
	__enable_irq();
}

void DelayMillis(void)
{
	SysTick->LOAD = 0x11940;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
}

void DelayMs(unsigned long t)
{
	for(;t>0;t--)
		{
			DelayMillis();
		}
}




void systick_int(unsigned short uart_1_mgr[], unsigned short uart_2_mgr[], unsigned short uart_3_mgr[]){
	if(uart_1_mgr[0] != 0){
		if(uart_1_mgr[6] == 0){
			uart_1_mgr[0] = 0;
			uart_1_mgr[1] = 1;
			uart_1_mgr[5] = 0;
			Systick_init();
		}else{
			uart_1_mgr[6]--;
		}
	}else if(uart_2_mgr[0] != 0){
		if(uart_2_mgr[6] == 0){
			uart_2_mgr[0] = 0;
			uart_2_mgr[1] = 1;
			uart_2_mgr[5] = 0;
			Systick_init();
		}else{
			uart_2_mgr[6]--;
		}
	}else if(uart_3_mgr[0] != 0){
		if(uart_3_mgr[6] == 0){
			uart_3_mgr[0] = 0;
			uart_3_mgr[1] = 1;
			uart_3_mgr[5] = 0;
			Systick_init();
		}else{
			uart_3_mgr[6]--;
		}
	}
}
	
