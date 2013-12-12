#include "jupiter_uart.h"

USART_InitTypeDef * g_uartInit;

void uart_init(void)
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
//	GPIO_WriteBit(GPIOA, GPIO_Pin_9|GPIO_Pin_10, 1);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_9|GPIO_Pin_10, 0);
	while(!USART_GetFlagStatus(USART1, USART_FLAG_TC)){}
  USART_SendData(USART1, sdata);
  return 0;
}

/*
them phan xu ly nhan nhieu data
*/
uint8_t uart_recv(void)
{
  if(!USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
	{
//    switch(uart_stt)
//		{
//    }
  }
	return 0;
}
