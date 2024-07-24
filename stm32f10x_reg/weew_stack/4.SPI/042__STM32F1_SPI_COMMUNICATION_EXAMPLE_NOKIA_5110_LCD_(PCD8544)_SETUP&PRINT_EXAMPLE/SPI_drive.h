
enum SPI_errol{
	ERROL_PRARAMETER
		
};

void SPI_init(unsigned short Spi_Channel);
void SPI_Tx(unsigned Spi_Channel, char Tx_char);
void SPI_Msg(unsigned short Spi_Channel, char const* msg);
