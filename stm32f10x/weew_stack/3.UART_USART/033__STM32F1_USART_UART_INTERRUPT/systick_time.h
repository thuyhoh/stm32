#define SysTick_CTRL (*(volatile unsigned long *)0xE000E010)
#define SysTick_LOAD (*(volatile unsigned long *)0xE000E014)
#define SysTick_VAL (*(volatile unsigned long *)0xE000E018)

void Systick_init(void);
void DelayMilis(void);
void Delayms(unsigned long time);
