#include "uart_drive.h"
#include "stm32f10x.h"                  // Device header

/*      uart pin:
    - uart1: PA9  (Tx)  PA10 (Rx)
    - uart2: PA2  (Tx)  PA3  (Rx)
    - uart3: PB10 (Tx)  PB11 (Rx)

*/

// set baundrate : tính toán giá trị nạp vào thanh ghi USART->BBR
static uint32_t set_BR(uint8_t uart, uint32_t BR)
{
    uint32_t div = 36000000UL;
    uint32_t dec;
    uint32_t result;
    double frac = 36000000.00;
    double frac2 = 1.00;
    if(uart == 1)
    {
        div = 72000000UL;
        frac = 72000000.00;
    }
    div = div / (BR * 16);
    frac = 16*((frac / (BR*16))- div);
    dec = frac;
    frac2 = 100*(frac - dec);
    if(frac2 > 50)
    {
        dec++;
        if(dec == 16)
        {
            dec = 0;
            div++;
        }
    }
    result = (div << 4) | dec;

}

//USART_TypeDef* get_UART(UART_Channel UART_Channelx)
//{
//	switch (UART_Channelx)
//	{
//		case :
//	}
//}

// hàm khởi tạo uart 
void UART_Init(uint8_t uart, uint64_t BR)
{
    uint32_t BRR;
    BRR = set_BR(uart,BR);
    // enable alternative option for GPIO
    RCC->APB2ENR |= 1;
    switch (uart)
    {
    case UART_CHANNEL_1:
        __disable_irq(); // using interrupt for Rx
        // Enable UART1
        RCC->APB2ENR |= 0x4000;
        GPIO_Init(PA, 9, OUT50, O_AF_PP);
        GPIO_Init(PA, 10, IN, I_PP);

        // set up the baude rate for BR bps
        USART1->BRR = BRR;
        // Enable UART Transmit
        USART1->CR1 |= 8;
        // Enable UART Recive
        USART1->CR1 |= 4;
        // Enable UART
        USART1->CR1 |= 0X2000; 
        NVIC_EnableIRQ(USART1_IRQn);
		__enable_irq();
        break;
    case UART_CHANNEL_2:
        __disable_irq(); // using interrupt for Rx
        // Enable UART2
        RCC->APB1ENR |= 0x20000;
        GPIO_Init(PA, 2, OUT50, O_AF_PP);
        GPIO_Init(PA, 3, IN, I_PP);

        // set up the baude rate for BR bps
        USART2->BRR = BRR;
        // Enable UART Transmit
        USART2->CR1 |= 8;
        // Enable UART Recive
        USART2->CR1 |= 4;
        // Enable UART
        USART2->CR1 |= 0X2000; 
        NVIC_EnableIRQ(USART2_IRQn);
		__enable_irq();
        break;
    case UART_CHANNEL_3:
        __disable_irq(); // using interrupt for Rx
        // Enable UART3
        RCC->APB1ENR |= 0x40000;
        GPIO_Init(PB, 10, OUT50, O_AF_PP);
        GPIO_Init(PB, 11, IN, I_PP);

        // set up the baude rate for BR bps
        USART3->BRR = BRR;
        // Enable UART Transmit
        USART3->CR1 |= 8;
        // Enable UART Recive
        USART3->CR1 |= 4;
        // Enable UART
        USART3->CR1 |= 0x2000; 
        NVIC_EnableIRQ(USART3_IRQn);
		__enable_irq();
        break;
    default:
        break;
    }
}

// hàm chuyền một ký tự
void UART_Tx(uint8_t uart, char c)
{
    switch (uart)
    {
    case UART_CHANNEL_1:
        while((USART1->SR & (1<<6)) == 0x80);
		USART1->DR = c;
        break;
    case UART_CHANNEL_2:
        while((USART2->SR & (1<<6)) == 0x80);
		USART1->DR = c;
        break;
    case UART_CHANNEL_3:
        while((USART3->SR & (1<<6)) == 0x80);
		USART1->DR = c;
        break;
    default:
        break;
    }
}

// hàm truyền một chuỗi ký tự
void UART_Tx_Msg(uint8_t uart, char *msg)
{
    int i = 0;
    while(*(msg + i) != '\0') 
    {
        UART_Tx(uart, *(msg +i));
        i++;
    }

}

// hàm nhận 1 ký tự 
char UART_Rx(uint8_t uart)
{
    char c;
    switch (uart)
    {
    case UART_CHANNEL_1:
        while((USART1->SR & 0x20) == 0x00);
        c = USART1->DR;
        break;
    case UART_CHANNEL_2:
        while((USART2->SR & 0x20) == 0x00);
        c = USART2->DR;
        break;
    case UART_CHANNEL_3:
        while((USART3->SR & 0x20) == 0x00);
        c = USART3->DR;
        break;
    default:
        break;
    }
    return c;
}

// hàm nhận dữ liệu là một chuỗi 
void UART_RX_Msg(uint8_t uart, uint8_t *signal, uint16_t *counter, char endl, char msg[])
{
    msg[*counter] = UART_Rx(uart);
    if(msg[*counter] == endl)
    {
        *counter = 0;
        *signal = 1;// nếu signal = 1 -> nhận hoàn tất
    }
    else
    {
        *counter = *counter + 1;
    }
}

// hàm thức hiện ngắt
__WEAK void USART2_IRQHandler() 
{
    //UART_RX_Msg(uint8_t uart, uint8_t *signal, uint16_t *counter, char endl; char msg[])
}

void UART_transmit(void)
{
// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
// 2. Program the M bit in USART_CR1 to define the word length.
// 3. Program the number of stop bits in USART_CR2.
// 4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take 
// place. Configure the DMA register as explained in multibuffer communication.
// 5. Select the desired baud rate using the USART_BRR register.
// 6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
// 7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this 
// for each data to be transmitted in case of single buffer.
// 8. After writing the last data into the USART_DR register, wait until TC=1. This indicates 
// that the transmission of the last frame is complete. This is required for instance when 
// the USART is disabled or enters the Halt mode to avoid corrupting the last 
// transmission
}

void UART_RECIEVE(void)
{
// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
// 2. Program the M bit in USART_CR1 to define the word length.
// 3. Program the number of stop bits in USART_CR2.
// 4. Select DMA enable (DMAR) in USART_CR3 if multibuffer communication is to take 
// place. Configure the DMA register as explained in multibuffer communication. STEP 3
// 5. Select the desired baud rate using the baud rate register USART_BRR 
// 6. Set the RE bit USART_CR1. This enables the receiver which begins searching for a 
// start bit
}
