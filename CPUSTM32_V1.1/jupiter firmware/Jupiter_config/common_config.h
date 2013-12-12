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



/** 
  * @brief  STM32F100 Button Defines Legacy  
  */ 
#define Mode_GPIO            BUTTON_MODE_GPIO
#define Mode_EXTI            BUTTON_MODE_EXTI

/** @addtogroup STM32vldiscovery_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             10
#define LED1_PIN                         GPIO_Pin_1
#define LED1_GPIO_PORT                   GPIOA
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOA  

#define LED2_PIN                         GPIO_Pin_9
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB  

// software spi io
#if 0
#define SDI_PIN                         GPIO_Pin_5
#define SDI_GPIO_PORT                   GPIOB
#define SDI_GPIO_CLK                    RCC_APB2Periph_GPIOB  
#define CLK_PIN                         GPIO_Pin_6
#define CLK_GPIO_PORT                   GPIOB
#define CLK_GPIO_CLK                    RCC_APB2Periph_GPIOB  
#define STR_PIN                         GPIO_Pin_7
#define STR_GPIO_PORT                   GPIOB
#define STR_GPIO_CLK                    RCC_APB2Periph_GPIOB
#define OE_PIN                          GPIO_Pin_6
#define OE_GPIO_PORT                    GPIOA
#define OE_GPIO_CLK                     RCC_APB2Periph_GPIOA
#else
#define SDI_PIN                         GPIO_Pin_7
#define SDI_GPIO_PORT                   GPIOA
#define SDI_GPIO_CLK                    RCC_APB2Periph_GPIOA
#define CLK_PIN                         GPIO_Pin_5
#define CLK_GPIO_PORT                   GPIOA
#define CLK_GPIO_CLK                    RCC_APB2Periph_GPIOA
#define STR_PIN                         GPIO_Pin_6
#define STR_GPIO_PORT                   GPIOA
#define STR_GPIO_CLK                    RCC_APB2Periph_GPIOA
#define OE_PIN                          GPIO_Pin_4
#define OE_GPIO_PORT                    GPIOA
#define OE_GPIO_CLK                     RCC_APB2Periph_GPIOA
#endif

#define FREQ_TEST_PIN                         GPIO_Pin_8
#define FREQ_TEST_GPIO_PORT                   GPIOA
#define FREQ_TEST_GPIO_CLK                    RCC_APB2Periph_GPIOA  

// config clock source
#define SYSCLK	24000000
#define USE_HSE 0

#define FLASH_START_ADDRESS 		0x8008000
#define FLASH_CHANGE_ADDRESS		4
#define FLASH_OPERATION_SIZE		4
	 
#define EFFECT_SIZE 170

#define LAST_ADD_FLASH(first_add, length)	(FLASH_START_ADDRESS - length/4+1)

// command
#define SET_TIME_CMD			0x8E
#define SET_ALARM_CMD			0xD4
#define SET_EFFECT_CMD		0xE8
#define CHANGE_TIME_CMD		0xF0
#define CHANGE_ALARM_CMD	0x0F
#define CHANGE_EFFECT_CMD	0x71

// header code
#define READ_TIME_CMD		0x33
#define READ_ALARM_CMD	0x96
#define START_TRANSFER	0xC3
#define STOP_TRANSFER		0xB2

typedef void (* UART_CALLBACK)(void*);
/**
  * @}
  */ 

/**
  * @}
  */ 

/** @defgroup STM32vldiscovery_LOW_LEVEL__Exported_Functions
  * @{
  */ 


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
