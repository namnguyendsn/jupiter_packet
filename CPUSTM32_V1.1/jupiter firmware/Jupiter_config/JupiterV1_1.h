/**
  ******************************************************************************
  * @file    STM32vldiscovery.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   Header file for STM32vldiscovery.c module.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "STM32f10x.h"
#include "common_config.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_bkp.h"
#include "jupiter_spi.h"
#include "jupiter_595.h"
#include "jupiter_uart.h"
#include "jupiterHSICab.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
	
// flash config
/* ghi data vao flash theo kieu heap/stack
	 main code ghi vao dia chi tang tu 0x8000000 len, 
	 data ghi vao dia chi 0x8008000 xuong
	 */

/* packet format
|SOP|Length|CRC|DATA|EOP|
SOP: 1 byte
Length: 2 bytes
CRC: 2 bytes
DATA: length bytes
EOP: 1 bytes
*/
#define CNT_xxx             0xD0
#define DAT_TIME            0xD0
#define DAT_ALARM           0xD1
#define DAT_EFFECT_BRIGHT   0xD2
#define DAT_EFFECT_SFOR     0xD3
#define DAT_EFFECT_EFOR     0xD4
#define DAT_EFFECT          0xD5
//#define 
#define DATASIZE_PER_FRAME  32

// data types
#define CDATA   0x89
#define LDATA   0x88

// backup
#define BKP_EFFECT_AVAL     0x0001
#define BKP_EFFECT_AVAL1     0x0002
#define BKP_EFFECT_AVAL2     0x0004
#define BKP_EFFECT_AVAL3     0x0008
#define BKP_EFFECT_AVAL4     0x0010
#define BKP_EFFECT_AVAL5     0x0020
#define BKP_EFFECT_AVAL6     0x0040
#define BKP_EFFECT_AVAL7     0x0080
#define BKP_EFFECT_AVAL8     0x0100
#define BKP_EFFECT_AVAL9     0x0200
#define BKP_EFFECT_AVAL10     0x0400
#define BKP_EFFECT_AVAL11     0x0800
#define BKP_EFFECT_AVAL12     0x1000
#define BKP_EFFECT_AVAL13     0x2000
#define BKP_EFFECT_AVAL14     0x4000
#define BKP_EFFECT_AVAL15     0x8000

typedef struct _packet_format
{
#define SOP 0xE0
    uint8_t reserved;
    uint8_t length_h;
    uint8_t length_l;
    uint8_t data_type;
    uint8_t *data;
#define EOP 0xE1
}STRUCT_PACKET_EFFECT;

typedef enum
{
    PK_SOP = 0,
    PK_EOP,
    PK_LWAIT,
    PK_CWAIT,
    PK_DWAIT,
    PK_DTWAIT,
    PK_EWAIT,
    PK_DONE,
    PK_IDLE,
    PK_REMAIN,
    PK_CFAIL,
}PACKET_STATUS;

typedef enum 
{
  EF_STT_STARTFOR = 0,
  EF_STT_ENDFOR,
  EF_STT_BRIGHT,
  EF_STT_DELAY,
  EF_STT_LED,
  EF_STT_IDLE
}EF_STT;

typedef struct sfor_
{
  uint8_t loop_times;
  uint8_t reserved[3];
  uint32_t sfor_add;
}SFOR_STRUCT;

// UART init struct
typedef struct _user_init_uart
{
    USART_InitTypeDef *UART_Init_Par;
    USART_TypeDef			*UART_Index;
}UART_APPLICATION_INIT, *UART_APPLICATION_INIT_PTR;

// time configuration
typedef struct _config_time
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t days;
    uint8_t dates;
    uint8_t months;
    uint16_t years;
}TIME, *TIME_PTR;

// alarm configuration (on/off time)
typedef struct _config_alarm
{
    uint8_t alarm_hour;
    uint8_t alarm_minute;
}ALARM, *ALARM_PTR;
// led effect
typedef struct _led_effect
{
    uint32_t	led_index; // 0 .. 32
    uint16_t	led_delay; // 0 .. 65535ms 
}LED_EFFECT, *LED_EFFECT_PTR;
// configuration message
/*
|header_code|crc_code|config_length|change_thing|                  config_time                 |     config_alarm      |effect_length|led_effect|
|           |        |             |            |hours|minutes|seconds|days |dates|months|years|alarm_hour|alarm_minute|             |          |
|     0-3   |   4-7  |    8-9      |    10-11   |12-12| 13-13 | 14-14 |15-15|16-16|17-17 |18-19|   20-20  |    21-21   |   22-23     |    N     |
|     1     |    2   |               3          |             4             |          5       |                  6                  |      n   |

ten truong cha:
ten truong con:
thu tu bytes:
thu tu word(4bytes):
	*/
typedef struct _config_message_struct
{	// 0x4A4C4444 (JLD: Jupiter Led Driver Data)
	// 0x4A4C444C (JLL: Jupiter Led Driver Length)
	uint32_t		header_code; 
	uint32_t		crc_code;
	uint16_t		config_length; // length of led effects
	uint16_t		change_thing;// luu nhung gi can thay doi: thoi gian on/off hay rtc hay led effect
	TIME				config_time;// config internal rtc
	ALARM				config_alarm;// config on/off time
	uint16_t 		effect_length;
	LED_EFFECT	led_effect[EFFECT_SIZE];// led effect
}CONFIG_MESSAGE, *CONFIG_MESSAGE_PTR;
/**
  * @}
  */ 

typedef enum 
{
  LED1 = 0,
	FREQ_TEST,
	LED2,
	SDI,
	CLK,
	STR,
	OE
}Led_TypeDef;



/**
  * @}
  */ 

/** @defgroup STM32vldiscovery_LOW_LEVEL__Exported_Functions
  * @{
  */ 
void STM32vldiscovery_LEDInit(Led_TypeDef Led);
void STM32vldiscovery_LEDOn(Led_TypeDef Led);
void STM32vldiscovery_LEDOff(Led_TypeDef Led);
void STM32vldiscovery_LEDToggle(Led_TypeDef Led);
void uart_get_data(void);
void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_langth);
void write_to_flash(uint8_t *pk_ptr, uint8_t f_length);
void jupiter_cpu_init(void);
void effect_run(void);

/**
  * @}
  */ 
    
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */  

/**
  * @}
  */
  
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
