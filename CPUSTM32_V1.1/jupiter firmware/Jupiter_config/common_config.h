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

#include "stm32f10x.h"                  // Device header

#define printf printf_kinetis
#define sprintf sprintf_kinetis


/** 
  * @brief  STM32F100 Button Defines Legacy  
  */ 
#define Mode_GPIO            BUTTON_MODE_GPIO
#define Mode_EXTI            BUTTON_MODE_EXTI

/** @addtogroup STM32vldiscovery_LOW_LEVEL_LED
  * @{
  */
/* Define Error code */
#define JUPITER_OK 0
#define JUPITER_FAIL -1
#define JUPITER_FLASH_FAIL -2
	
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
/* Uncomment this line to activate demo 1: calibration with fixed Error */
/* Comment this line to activate demo 2: calibration with minimum Error found */
#define USE_HSI_Fixed_Error  0

#define FLASH_START_ADDRESS     0x08007C00
#define FLASH_END_ADDRESS       0x08008400

#define EFFECT_AVAL_ADDRESS FLASH_START_ADDRESS
#define EFFECT_AVAL_MASK    EFFCT_DT_BRIGHT
#define EFFECT_BEGIN_ADD    FLASH_START_ADDRESS
#define EFFECT_END_ADD      FLASH_END_ADDRESS
#define FLASH_PAGE_SIZE     ((uint16_t)0x400)
#define FLASH_NUMPAGE       (FLASH_END_ADDRESS - FLASH_START_ADDRESS)/FLASH_PAGE_SIZE



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
//#define READ_TIME_CMD		0x33
#define READ_ALARM_CMD	0x96
#define START_TRANSFER	0xC3
#define STOP_TRANSFER		0xB2

#define EFFCT_DT_STARTFOR 0x80
#define EFFCT_DT_ENDTFOR  0x81
#define EFFCT_DT_BRIGHT   0x82

// UART
#define J_UART	USART1

typedef void (* UART_CALLBACK)(void*);
typedef void (*fpncallback)(uint8_t *, uint8_t );
typedef int8_t (*flashcallback)(uint8_t *, uint8_t , uint8_t );
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
