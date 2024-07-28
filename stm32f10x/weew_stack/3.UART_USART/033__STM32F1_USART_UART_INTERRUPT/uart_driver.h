
unsigned long  UART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_Rx(unsigned short uart);
void UART_Tx(unsigned short uart, char c);
void UART_SEND(unsigned short uart, char* srt);
void UART_ISR(unsigned short uart, unsigned short bridge, unsigned short* signal, unsigned short* counter, char msg[]);
void str_empty(char str[]);
