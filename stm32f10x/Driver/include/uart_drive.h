#include "stm32f10x.h" 

#include "stdint.h"
#include "gpio_drive.h"

//#define __weak __attribute__((weak))
enum{
    UART_CHANNEL_1 = 1,
    UART_CHANNEL_2 = 2,
    UART_CHANNEL_3 = 3
}UART_Channel;


void UART_Init(uint8_t uart, uint64_t BR);

void UART_Tx(uint8_t uart, char c);
void UART_Tx_Msg(uint8_t uart, char *msg);
char UART_Rx(uint8_t uart);
void UART_RX_Msg(uint8_t uart, uint8_t *signal, uint16_t *counter, char endl, char msg[]);
