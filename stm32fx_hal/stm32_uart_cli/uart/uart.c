#include "uart.h"
#include <string.h>

extern UART_HandleTypeDef huart1;

uint8_t data_rx;
uint8_t buff_uart[BUFFER_UART];
uint16_t index_uart = 0;
uint8_t signal = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == huart1.Instance)
	{
		signal = 0;
		buff_uart[index_uart] = data_rx;
		if(data_rx == '\n')
		{
			signal = 1;
		}
		index_uart++;
		HAL_UART_Receive_IT(&huart1,&data_rx,1);
	}
}

void uart_init(void)
{
	HAL_UART_Receive_IT(&huart1, &data_rx, 1);
}

void uart_handler()
{
	if(signal == 1)
	{
		memset(buff_uart,0, index_uart);
		signal = 0;
		index_uart = 0;
		commnand_excute((char*)buff_uart);
	}
}

