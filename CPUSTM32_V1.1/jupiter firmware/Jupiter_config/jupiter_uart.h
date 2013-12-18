#include <stm32f10x.h>
#include "stm32f10x_usart.h"
#include "common_config.h"
#include <stdlib.h>

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
	UART_READ_ID,
	UART_FRAME_START,
	UART_FRAME_END,
	UART_SUB_FRAME_START,
	UART_SUB_FRAME_END
}UART_RECV_STATUS;

typedef struct _uart_frame_write_time
{
  uint8_t test;
}UART_FRAME_WRITE_TIME, * UART_FRAME_WRITE_TIME_PTR;

typedef struct _uart_frame_read_time
{
  uint8_t test;
}UART_FRAME_READ_TIME, * UART_FRAME_READ_TIME_PTR;

typedef struct _uart_frame_write_alarm
{
  uint8_t test;
}UART_FRAME_WRITE_ALARM, * UART_FRAME_WRITE_ALARM_PTR;

typedef struct _uart_frame_read_alarm
{
  uint8_t test;
}UART_FRAME_READ_ALARM, * UART_FRAME_READ_ALARM_PTR;

void uart_init(UART_CALLBACK callback);
uint8_t uart_send(uint8_t sdata);
void uart_get_data(void);
