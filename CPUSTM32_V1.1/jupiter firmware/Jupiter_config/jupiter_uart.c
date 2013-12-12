#include "jupiter_uart.h"

USART_InitTypeDef * g_uartInit;
static uint8_t * g_uart_rev_buffer;

void uart_init(UART_CALLBACK callback)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  g_uartInit = (USART_InitTypeDef*)malloc(sizeof(USART_InitTypeDef));
	AFIO->MAPR   &= ~(1 << 2);                              // clear USART1 remap
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
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
	USART_Init(USART1, g_uartInit);
	// init interrupt
	USART_ITConfig(USART1, USART_IT_TC|USART_IT_RXNE, ENABLE);
	free(g_uartInit);
}

/*
them phan xu ly gui nhieu data
*/ 
uint8_t uart_send(uint16_t sdata)
{
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
  USART_SendData(USART1, sdata);
  return 0;
}

/**
  * @brief  Configures UART1.
		TX			A9
		RX			A10
		Baud		115200
		Parity	no
		Length	8bits
		Stop		1bit
		Follow	none
	*/

/**
  * @brief  Getting data from uart
		return 8bits data to application buffer
	*/
void uart_get_data(void)
{
	static uint16_t char_count = 0;
	switch((uint8_t)USART_ReceiveData(USART1))
	{
		case SET_TIME_CMD:
			break;
		case SET_ALARM_CMD:
			break;
		case SET_EFFECT_CMD:
			break;
		case CHANGE_TIME_CMD:
			break;
		case CHANGE_ALARM_CMD:
			break;
		case CHANGE_EFFECT_CMD:
			break;
		case READ_TIME_CMD:
			break;
		case READ_ALARM_CMD:
			break;
		case START_TRANSFER:
			break;
		case STOP_TRANSFER:
			break;
	}
	g_uart_rev_buffer[char_count] = (uint8_t)USART_ReceiveData(USART1);
//	if(char_count >= (uint16_t)sizeof(CONFIG_MESSAGE))
//		uart_buffer_process(g_uart_buffer);// bufer process callback
}
