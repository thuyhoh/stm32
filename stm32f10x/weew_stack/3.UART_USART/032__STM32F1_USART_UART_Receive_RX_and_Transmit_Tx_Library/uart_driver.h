
unsigned long  UART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_Rx(unsigned short uart);
void UART_Tx(unsigned short uart, char c);
