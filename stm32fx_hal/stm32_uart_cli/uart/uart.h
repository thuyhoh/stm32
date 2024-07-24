#ifndef __UART_H_
#define __UART_H_

#include "main.h"
#include "command..h"

#define BUFFER_UART 128
void uart_init(void);
void uart_handler(void);

#endif
