#include "jupiter_uart.h"

USART_InitTypeDef * g_uartInit;
static STRUCT_TRANSACTION transfer_struct;
static TRANSFER_STT status_transfer;
static uint8_t data_counter;
static uint8_t *temp;
static fpncallback uart_callback;
static uint8_t error_counter = 0;

void uart_init(fpncallback callback)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	g_uartInit = (USART_InitTypeDef*)malloc(sizeof(USART_InitTypeDef));
	AFIO->MAPR &= ~(1 << 2); // clear USART1 remap
	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure TX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure RX */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//enable clock for uart
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//enable clock for alternate function
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// khoi tao tham so cho uart
	USART_StructInit(g_uartInit);
	// init uart
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // enable clock for Alternate Function

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Init(J_UART, g_uartInit);
	// init interrupt
	USART_ITConfig(J_UART, USART_IT_RXNE, ENABLE);
	free(g_uartInit);
    status_transfer = TRANSFER_IDLE;
    data_counter = 0;
    uart_callback = callback;
}

/*
them phan xu ly gui nhieu data
*/
uint8_t uart_send(uint8_t sdata)
{
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
	USART_SendData(USART1, sdata);
	return 0;
}

/**
* @brief Configures UART1.
TX A9
RX A10
Baud 115200
Parity no
Length 8bits
Stop 1bit
Follow none
*/

/**
* @brief Getting data from uart
return 8bits data to application buffer
*/
void uart_get_data(void)
{
	switch((uint8_t)USART_ReceiveData(USART1))
	{
	case HDR_SOF:
		status_transfer = START_OF_FRAME;
        return;
		break;
	case HDR_EOF:
        // transfer done, check crc
        if((data_counter == transfer_struct.length) && (calc_crc8(transfer_struct.data, transfer_struct.length) == transfer_struct.crc))
        {
            // call process data function
            uart_callback(transfer_struct.data, transfer_struct.length);
            status_transfer = TRANSFER_DONE;
        }
        else
        {
            status_transfer = TRANSFER_ERROR;
        }
        data_counter = 0;
		break;
	default:
		break;
	}
    switch(status_transfer)
    {
        case START_OF_FRAME:
            transfer_struct.length = (uint8_t)USART_ReceiveData(USART1);
            if(transfer_struct.length > FRAME_SIZE)
            {
                out_char(0xFF);
                status_transfer = TRANSFER_ERROR;
                break;
            }
            transfer_struct.data = (uint8_t*)malloc(transfer_struct.length);
            memset(transfer_struct.data, 0x00, transfer_struct.length);
            status_transfer = CRC_WAIT;
            return;
            break;
        case CRC_WAIT:
            transfer_struct.crc = (uint8_t)USART_ReceiveData(USART1);
            status_transfer = DATA_IN;
            temp = transfer_struct.data;
            return;
            break;
        case DATA_IN:
            if(data_counter < transfer_struct.length)
            {
                *temp = (uint8_t)USART_ReceiveData(USART1);
                temp++;
                data_counter++;
            }
            break;
        case TRANSFER_ERROR:
            out_char(0xFF);
            error_counter++;
            break;
        case TRANSFER_DONE:
            out_char(0xFE);
            error_counter = 0;
            break;
    }
    if((status_transfer == TRANSFER_DONE) || (status_transfer == TRANSFER_ERROR))
    {
        if(transfer_struct.data != NULL)
            free(transfer_struct.data);
    }
}

void out_char(char ch)
{
	uart_send(ch);
}
