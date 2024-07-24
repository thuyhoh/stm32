/*
typedef struct uart_manager{
	unsigned short count;
	unsigned short signal;
	unsigned short bridge;
	unsigned char final_char;
	
}UART_mgr;

UART_mgr uart_1_mgr = {1,0,1,'\n'};
*/

unsigned long  UART_BRR(unsigned short usart, unsigned long BR);
void UART_init(unsigned short usart, unsigned long BR);
char UART_Rx(unsigned short uart);
void UART_Tx(unsigned short uart, char c);
void UART_SEND(unsigned short uart, char* srt);
void UART_ISR(unsigned short uart, unsigned short uart_mgr[], char msg[]);
void str_empty(char str[]);
void UART_MSG(unsigned short uart, char msg[], unsigned short uart_mgr[]);
