
unsigned long  UART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_Rx(unsigned short uart);
void UART_Tx(unsigned short uart, char c);
void UART_SEND(unsigned short uart, char* srt);
void UART_ISR(unsigned short uart, unsigned short uart_mnr[], char msg[]);
void UART_MSG(unsigned short uart, char msg[], unsigned short uart_mgr[]);
