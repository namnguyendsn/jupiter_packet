#include <stm32f10x.h>
#include "stm32f10x_usart.h"
#include <math.h>

typedef enum _uart_stt
{
	// frame header
  UART_IDLE,
	UART_WRITE_TIME,
	UART_WRITE_LED_EFFECT,
	UART_WRITE_ALARM,
	UART_WRITE_TEST_CPU,
	UART_WRITE_TEST_DRIVER,
	UART_READ_TIME,
	UART_READ_ALARM,
	UART_READ_ID
}UART_RECV_STATUS;

void uart_init(void);
uint8_t uart_send(uint16_t sdata);
uint8_t uart_recv(void);
