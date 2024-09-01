/* copy file and run in main.c */
#include "stm32f407vg.h"
#include "string.h"

void SPI2_Config(void);
SPI_Handle_t SPI2Handle;

int main(void)
{
	char data[] = "hello world ";
	SPI2_Config();
	SPI_Start(SPI2Handle.pSPIx);
	SPI_Send(SPI2_BASE, (uint8_t *)data, strlen(data));
	while(1);
}

void SPI2_Config(void)
{
	
	SPI2Handle.pSPIx = SPI2_BASE;
	SPI2Handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MASTER_MODE;
	SPI2Handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI2Handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
	SPI2Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPI_Config.SPI_SSM = SPI_SSM_EN;
	SPI_Init(&SPI2Handle);
}
