/**
  ******************************************************************************
  * @file    stm32vldiscovery.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   STM32VLDISCOVERY abstraction layer. 
  *          This file should be added to the main application to use the provided
  *          functions that manage the Leds LD3 and LD4 and the USER push-button.
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
  
/* Includes ------------------------------------------------------------------*/
#include "JupiterV1_1.h"

/** @defgroup STM32vldiscovery_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32vldiscovery_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32vldiscovery_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM32vldiscovery_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT};

const uint16_t GPIO_PIN[LEDn] = {LED1_PIN};
static UART_APPLICATION_INIT_PTR uart_app_init;
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK};
static uint8_t * uart_rev_buffer;
extern uint8_t* g_led_effect_ptr;

extern CONFIG_MESSAGE_PTR g_uart_buffer;
extern TIME 				g_app_config_time;
extern ALARM 				g_app_config_alarm;
extern LED_EFFECT 	*g_app_led_effect;
extern uint32_t 		g_app_crc_code;
extern uint16_t			g_app_length;
extern uint32_t			g_app_header_code;
extern uint16_t 		g_effect_length;

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
void Jupiter_UART_Init()
{
	g_uart_buffer = (CONFIG_MESSAGE_PTR)malloc(sizeof(CONFIG_MESSAGE));
	uart_rev_buffer = (uint8_t *)g_uart_buffer;
	
	uart_app_init = (UART_APPLICATION_INIT_PTR)malloc(sizeof(UART_APPLICATION_INIT_PTR));
	uart_app_init->UART_Index = (USART_TypeDef*)USART1_BASE;
	USART_StructInit(uart_app_init->UART_Init_Par);
	USART_Init(uart_app_init->UART_Index, uart_app_init->UART_Init_Par);
	USART_ITConfig(uart_app_init->UART_Index, USART_IT_RXNE, ENABLE);
}

/**
  * @brief  Getting data from uart
		return 8bits data to application buffer
	*/
void uart_get_data(void)
{
	static uint16_t char_count = 0;
	switch((uint8_t)USART_ReceiveData(uart_app_init->UART_Index))
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
	uart_rev_buffer[char_count] = (uint8_t)USART_ReceiveData(uart_app_init->UART_Index);
	if(char_count >= (uint16_t)sizeof(CONFIG_MESSAGE))
		uart_buffer_process(g_uart_buffer);
}

/**
  * @brief  parse data from uart_buffer
	*/
void uart_buffer_process(CONFIG_MESSAGE_PTR buffer)
{
	uint32_t crc_code;
	g_app_header_code = (uint32_t)g_uart_buffer->header_code;
	g_app_crc_code = (uint32_t)g_uart_buffer->crc_code;
	g_app_length = (uint16_t)g_uart_buffer->config_length;
	g_app_config_time = g_uart_buffer->config_time;
	g_app_config_alarm = g_uart_buffer->config_alarm;
	g_app_led_effect = (LED_EFFECT *)g_uart_buffer->led_effect;
	// CRC check
	// write to flash
	write_to_flash(FLASH_START_ADDRESS, g_uart_buffer);
}

/**
  * @brief  store data in flash
	*/
void write_to_flash(uint32_t address, CONFIG_MESSAGE_PTR data)
{
	uint16_t num_left;
	uint16_t data_length;
	uint32_t next_add;
	FLASH_Status flash_status;
	uint32_t * header_ptr;
	
	next_add = address;
	header_ptr = (uint32_t *)data;
	data_length = (uint16_t)strlen((uint8_t*)data);// kiem tra lai cach tinh nay
	num_left = data_length;
	while(num_left)
	{
		address = next_add;
		flash_status = FLASH_ProgramWord(address, (uint32_t)*header_ptr);
		switch(flash_status)
		{
			case FLASH_BUSY:
			case FLASH_TIMEOUT:
				break;
			case FLASH_ERROR_PG:
			case FLASH_ERROR_WRP:
				/* Unlock the Flash Bank1 Program Erase controller */
				FLASH_UnlockBank1();
				break;
			case FLASH_COMPLETE:
				num_left -= FLASH_OPERATION_SIZE;
				next_add -= FLASH_CHANGE_ADDRESS;
				break;
			default:
				break;
		}
	}
}

/**
  * @brief  get data from flash
	*/
void read_from_flash(uint32_t Address)
{
	uint32_t end_address;
	uint32_t start_address;
	uint32_t *data_out_ptr;
	uint8_t Index = 0;
	uint8_t *pointer;
	
	start_address = FLASH_START_ADDRESS;
	end_address = LAST_ADD_FLASH(FLASH_START_ADDRESS, g_uart_buffer->config_length);
	while(Address > end_address)
	{
    data_out_ptr[Index] = *(__IO uint32_t*)Address;
    Address += 4;
		Index += 4;
	}
	(void)memcpy(g_led_effect_ptr, data_out_ptr, EFFECT_SIZE); // kiem tra lai
	// g_uart_buffer = (CONFIG_MESSAGE_PTR)FLASH_START_ADDRESS;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  * @retval None
  */
void STM32vldiscovery_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_APB2PeriphClockCmd(GPIO_CLK[Led], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM32vldiscovery_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];   
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void STM32vldiscovery_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];   
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM32vldiscovery_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @}
  */ 

/**
  * @}
  */ 


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
