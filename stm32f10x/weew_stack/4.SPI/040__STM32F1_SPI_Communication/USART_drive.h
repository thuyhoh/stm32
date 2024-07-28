unsigned short USART_BRR(unsigned short Usart_Channel, unsigned long Baundrate);
void USART_init(unsigned short Usart_Channel,unsigned long Baundrate);
char USART_Rx(unsigned short Usart_Channel);
void USART_Tx(unsigned short Usart_Channel, char chat);
void USART_Send(unsigned short Usart_Channel, char *msg);
void USART_ISR_init(unsigned short Usart_Channel,unsigned long Baundrate);
void USART_ISR(unsigned short Usart_Channel, unsigned short bridge, unsigned short *signal, unsigned short *counter, char *msg);
void empty_str(char* str);
