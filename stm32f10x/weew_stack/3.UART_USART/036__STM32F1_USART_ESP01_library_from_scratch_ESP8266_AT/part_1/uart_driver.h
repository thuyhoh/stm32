
// calculate baudrate transmits speed(BRR)
unsigned long  UART_BRR(unsigned short usart, unsigned long BR);

// initialization UARTx with BRR
void UART_init(unsigned short usart, unsigned long BR);

// return receive character 
char UART_Rx(unsigned short uart);

// transmit data 
void UART_Tx(unsigned short uart, char c);

// send string 
void UART_SEND(unsigned short uart, char* srt);

// interrupt 
void UART_ISR(unsigned short uart, unsigned short uart_mnr[], char msg[]);

// 
void UART_MSG(unsigned short uart, char msg[], unsigned short uart_mgr[]);
