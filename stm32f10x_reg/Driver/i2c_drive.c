#include "i2c_drive.h"


/*      i2c pin
    I2C2
    PB10 -> SCL OUTPUT_ALTERNATIVE_FUNCTION_OPEN_DRAW
    PB11 -> SDA OUTPUT_ALTERNATIVE_FUNCTION_OPEN_DRAW

    I2C1
    PB6 -> SCL OUTPUT_ALTERNATIVE_FUNCTION_OPEN_DRAW
    PB7 -> SDA OUTPUT_ALTERNATIVE_FUNCTION_OPEN_DRAW   
*/

void I2C_Master_Init(I2C_TypeDef *i2c, I2C_SPEED_MODE_typedef speed_mode)
{
	
	/* Configure the clock control registers */ // Enable i2c Clock
	// Config i2c pins
	RCC->APB2ENR |= AFIO_Clock_Enable;
	if(i2c == I2C1)			
	{
		RCC->APB1ENR |= I2C1_CLOCK_ENABLE;
		GPIO_Init(PB,10,OUTPUT_50MHZ_MODE,OUTPUT_GP_OPEN_DRAIN); // -> SCL pin
		GPIO_Init(PB,11,OUTPUT_50MHZ_MODE,OUTPUT_GP_OPEN_DRAIN); // -> SDA pin
	}
	else if(i2c == I2C2) 
	{
		RCC->APB1ENR |= I2C2_CLOCK_ENABLE;
		GPIO_Init(PB,6,OUTPUT_50MHZ_MODE,OUTPUT_GP_OPEN_DRAIN); // -> SCL pin
		GPIO_Init(PB,7,OUTPUT_50MHZ_MODE,OUTPUT_GP_OPEN_DRAIN); // -> SDA pin
	}
	
	/* Reset the I2C: CR1_SWRST: Software reset */
	i2c->CR1 |= RESET_I2C;
	i2c->CR1 &= ~(RESET_I2C); //
	
	/*Program the peripheral input clock in I2C_CR2 register in order to generate correct timings */
	i2c->CR2 = 50; // 50Mhz
	
	/* set the i2c clock */
	float T_PCLK = 1000/(i2c->CR2 & 0xff);
	uint16_t Tr = 1000, Tw = 4000;
	uint16_t T = Tr + Tw;
	uint16_t CCR = (uint16_t)(T/T_PCLK);
	i2c->CCR |= CCR;
	i2c->CCR |= speed_mode<<14;
	/* Config Maximum rise time in Fm/Sm mode  */
	uint16_t TRISE = (uint16_t)((uint16_t)Tr/T_PCLK + 1);
	i2c->TRISE |= TRISE;
	
	/* i2c Peripheral enable */
	i2c->CR1 |= 1; 
}

//
static void I2C_Start(I2C_TypeDef *i2c)
{
	// set the start bit in SPI_CR1
	i2c->CR1 |= 0x100;
	// waiting the SB bit is cleared
	while(!(i2c->SR1 & 1));
}

//
static void I2C_Transmit_7bit_Slave_Address(I2C_TypeDef *i2c, uint16_t Address, R_T_typedef R_T)
{
	
	__IO uint32_t tmp;
// the LSB bit of Slave addres is set -> receive/ is reset -> trasmit
	i2c->DR |= Address|R_T;
	while((i2c->SR1 & 2) == 0);
// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(i2c->SR1 & 2)
	{
		tmp = i2c->SR1;
		tmp = i2c->SR2;
	}
}
//
static void I2C_Transmit_10bit_Slave_Address(I2C_TypeDef *i2c, uint16_t Address, R_T_typedef R_T)
{

// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address 
	__IO uint32_t tmp = i2c->SR1;
	__IO uint16_t header = (uint16_t)(0xF0 | ((Address>>14)<<2)); // header = 11110xx0 (xxx denotes the two most significant bits of the address)
// sending the header
	i2c->DR = header;
// waiting the ADD10 bit is set	
	while((i2c->SR1 & (1<<4)) == 0);
// EV9: clear the ADD10 bit is clear followed by 
	while((i2c->SR1 & (1<<4)) == 1)
	{
// reading SR1 
		tmp = i2c->SR1;
// writing to DR with the slave address byte
		i2c->DR = Address;
	}
// waiting ADDR bit is set
	while((i2c->SR1 & 2) == 0);
/*  
	In 10-bit master receiver mode, this sequence should be followed by writing CR1 with START = 1. */ 
	while((i2c->SR1 & 2) == 2)
	{
// reading SR1 then SR2 regsister
		tmp = i2c->SR1;
		tmp = i2c->SR2;
	}
 
	if(R_T == I2C_RECEIVE_MODE) // recive mode	
	{
	// repeat start
		I2C_Start(i2c);
	// send the header = 11110xx1
		i2c->DR = header|1;
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	// waiting the ADDR is set
		while(!(i2c->SR1 & 2));
	
		while((i2c->SR1 & 2) == 2)
		{
			// reading SR1 then SR2 regsister
			tmp = i2c->SR1;
			tmp = i2c->SR2;
		}
	}
}

//
static void I2C_Transmit_Slave_Address(I2C_TypeDef *i2c, uint16_t Slave_Address, R_T_typedef R_T, Slave_xbit_Address Xbit)
{
	
	switch (Xbit)
	{
		case SLAVE_10BIT_ADDRESS : 
			I2C_Transmit_10bit_Slave_Address(i2c,Slave_Address, R_T); 
		break;
		case SLAVE_7BIT_ADDRESS  : 
			I2C_Transmit_7bit_Slave_Address(i2c,Slave_Address, R_T);
		break;
	}
}	

//
static void I2C_Write(I2C_TypeDef *i2c, uint8_t Data)
{

// EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR
	while(!(i2c->CR1 & 0x80));
	i2c->DR = Data;
// waiting BTF is set
	while (!(i2c->SR1 & (1<<2)));
}

//
static void I2C_Stop_Transmit(I2C_TypeDef *i2c)
{
	
	__IO uint16_t tmp;
	// Clear the ACK bit 
	I2C1->CR1 &= ~(1<<10);
	// EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	// either TxE or BTF is set
	while((i2c->SR1 & 0x80) | (i2c->SR1 & 0x4))
	{
		// clear TxE or BTF by software
		tmp = i2c->SR1;
	}
	// the STOP bit is set by software
	i2c->CR1 |= 0x200;
}
//
void I2C_Master_Transmit(I2C_TypeDef *i2c, Slave_xbit_Address Xbit, uint16_t Slave_Address, uint8_t *Data)
{
	I2C_Start(i2c);
	I2C_Transmit_Slave_Address(i2c, Slave_Address, I2C_TRANSMIT_MODE, Xbit);
	uint16_t i = 0;
	while(*(Data+i) != '\0')
	{
		I2C_Write(i2c,*(Data+i));
		i++;
	}
	I2C_Stop_Transmit(i2c);
}


//
uint8_t I2C_Read(I2C_TypeDef *i2c)
{
	
}
//
static void I2C_Stop_Recive(I2C_TypeDef *i2c)
{
	
}
//
uint8_t I2C_Master_Receive(I2C_TypeDef *i2c, Slave_xbit_Address Xbit, uint16_t Slave_Address)
{
	
}
