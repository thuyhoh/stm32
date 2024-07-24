//#define SysTick_CTRL (*(volatile unsigned long *)0xE000E010)
//#define SysTick_LOAD (*(volatile unsigned long *)0xE000E014)
//#define SysTick_VAL (*(volatile unsigned long *)0xE000E018)

void Systick_init(void);
void DelayMilis(void);
void Delayms(unsigned long time);
void systick_int_start(void);
void systick_int(unsigned short uart_1_mgr[], unsigned short uart_2_mgr[], unsigned short uart_3_mgr[]);
