#include "jupiter_uart.h"

USART_InitTypeDef * g_uartInit;
static uint8_t * g_uart_rev_buffer;

void uart_init(UART_CALLBACK callback)
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
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
	static uint16_t char_count = 0;
	switch((uint8_t)USART_ReceiveData(USART1))
	{
	case SET_TIME_CMD:
		//uart_buffer_process();
		break;
	case SET_ALARM_CMD:
		//uart_buffer_process();
		break;
	case SET_EFFECT_CMD:
		//uart_buffer_process();
		break;
	case CHANGE_TIME_CMD:
		//uart_buffer_process();
		break;
	case CHANGE_ALARM_CMD:
		//uart_buffer_process();
		break;
	case CHANGE_EFFECT_CMD:
		//uart_buffer_process();
		break;
	case READ_TIME_CMD:
		//uart_buffer_process();
		break;
	case READ_ALARM_CMD:
		//uart_buffer_process();
		break;
	case START_TRANSFER:
		//uart_buffer_process();
		break;
	case STOP_TRANSFER:
		//uart_buffer_process();
		break;
	}
	// g_uart_rev_buffer[char_count] = (uint8_t)USART_ReceiveData(USART1);
	// if(char_count >= (uint16_t)sizeof(CONFIG_MESSAGE))
	// uart_buffer_process(g_uart_buffer);// bufer process callback
}

void out_char(char ch)
{
	uart_send(ch);
}
