

#define PA          1           
#define PB          2           
#define PC          3          

#define HIGH       1
#define LOW        0

#define  IN        0
#define  OUT10     1
#define  OUT2      2
#define  OUT50     3


#define I_AN 0
#define I_F  1
#define I_PP 2

#define O_GP_PP 0
#define O_GP_OD 1
#define O_AF_PP 2
#define O_AF_OD 3





void GPIOx_init(unsigned short port, unsigned short Pin,unsigned short dir, unsigned short opt);

int GPIOx_R(unsigned short Port, unsigned short Pin);

void GPIOx_W(unsigned short Port, unsigned short Pin, unsigned short status);

void GPIOx_ISR(unsigned short Port, unsigned short Pin);

void GPIO_ISR_init(unsigned short Port, unsigned short Pin);

