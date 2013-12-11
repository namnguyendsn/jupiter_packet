#include "jupiter_uart.h"

USART_InitTypeDef * g_uartInit;
USART_TypeDef * uart_handle;
#define __USART_SETUP             1                       //  0
#define __USART_USED              0x01                    //  1
#define __USART_DETAILS           0x00					  //  2
#define __USART_INTERRUPTS        0x01					  //  3
#define __USART1_BAUDRATE         100				  //  4
#define __USART1_DATABITS         0x00000000
#define __USART1_STOPBITS         0x00000000
#define __USART1_PARITY           0x00000000
#define __USART1_FLOWCTRL         0x00000000
#define __USART1_REMAP            0x00000000
#define __USART1_CR1              0x000000A0
#define __USART1_CR2              0x00000000
#define __USART1_CR3              0x00000000
/*----------------------------------------------------------------------------
 Define  Baudrate setting (BRR) for USART1 
 *----------------------------------------------------------------------------*/
#define __DIV(__PCLK, __BAUD)       ((__PCLK*25)/(4*__BAUD))
#define __DIVMANT(__PCLK, __BAUD)   (__DIV(__PCLK, __BAUD)/100)
#define __DIVFRAQ(__PCLK, __BAUD)   (((__DIV(__PCLK, __BAUD) - (__DIVMANT(__PCLK, __BAUD) * 100)) * 16 + 50) / 100)
#define __USART_BRR(__PCLK, __BAUD) ((__DIVMANT(__PCLK, __BAUD) << 4)|(__DIVFRAQ(__PCLK, __BAUD) & 0x0F))

#define __RCC_CFGR_VAL             0x001D8402
#define __HSI 8000000UL
//#define __HSE 8000000UL
#define __PLLMULL (((__RCC_CFGR_VAL & CFGR_PLLMULL_MASK) >> 18) + 2)

  #define __SYSCLK   __HSI                        // HSI is used as system clock

#define __HCLKPRESC  ((__RCC_CFGR_VAL & CFGR_HPRE_MASK) >> 4)
#if (__HCLKPRESC & 0x08)
  #define __HCLK        (__SYSCLK >> ((__HCLKPRESC & 0x07)+1))
#else
  #define __HCLK        (__SYSCLK)
#endif
#define __PCLK2PRESC  ((__RCC_CFGR_VAL & CFGR_PRE2_MASK) >> 11)
#if (__PCLK2PRESC & 0x04)
  #define __PCLK2       (__HCLK >> ((__PCLK2PRESC & 0x03)+1))
#else
  #define __PCLK2       (__HCLK)
#endif
void uart_init(void)
{
	#if 0
  GPIO_InitTypeDef GPIO_InitStructure;
  g_uartInit = (USART_InitTypeDef*)malloc(sizeof(USART_InitTypeDef));
		/* Enable GPIOB clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure SPI2 pins: NSS, SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//enable clock for uart
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	// khoi tao tham so cho uart
	USART_StructInit(g_uartInit);
	// init uart
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
	USART_Init(USART1, g_uartInit);
	// init interrupt
	USART_ITConfig(USART1, USART_IT_TC|USART_IT_RXNE, ENABLE);
	#endif
	    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
    AFIO->MAPR   &= ~(1 << 2);                              // clear USART1 remap

      RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;                   // enable clock for GPIOA
      GPIOA->CRH   &= ~(0xFFUL  << 4);                      // Clear PA9, PA10
      GPIOA->CRH   |=  (0x0BUL  << 4);                      // USART1 Tx (PA9)  alternate output push-pull
      GPIOA->CRH   |=  (0x04UL  << 8);                      // USART1 Rx (PA10) input floating

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;                   // enable clock for USART1
        
    USART1->BRR  = __USART_BRR(__PCLK2, __USART1_BAUDRATE); // set baudrate
    USART1->CR1  = __USART1_DATABITS;                       // set Data bits
    USART1->CR2  = __USART1_STOPBITS;                       // set Stop bits
    USART1->CR1 |= __USART1_PARITY;                         // set Parity
    USART1->CR3  = __USART1_FLOWCTRL;                       // Set Flow Control

    USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);           // RX, TX enable

    if (__USART_INTERRUPTS & 0x01) {                        // interrupts used
      USART1->CR1 |= __USART1_CR1;
      USART1->CR2 |= __USART1_CR2;
      USART1->CR3 |= __USART1_CR3;
//      NVIC->ISER[1] |= (1 << (USART1_IRQChannel & 0x1F));   // enable interrupt
    }

    USART1->CR1 |= USART_CR1_UE;                            // USART enable
}

/*
them phan xu ly gui nhieu data
*/ 
uint8_t uart_send(uint16_t sdata)
{
//	GPIO_WriteBit(GPIOA, GPIO_Pin_9|GPIO_Pin_10, 1);
//	GPIO_WriteBit(GPIOA, GPIO_Pin_9|GPIO_Pin_10, 0);
	if(USART_GetFlagStatus(USART1, USART_FLAG_TC))
	{
    USART_SendData(USART1, sdata);
	}
	else
	{
     return 0;
  }
}

/*
them phan xu ly nhan nhieu data
*/
uint8_t uart_recv(void)
{
  if(!USART_GetFlagStatus(uart_handle, USART_FLAG_RXNE))
	{
//    switch(uart_stt)
//		{
//    }
  }
}
