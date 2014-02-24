/**
******************************************************************************
* @file stm32vldiscovery.c
* @author MCD Application Team
* @version V1.0.0
* @date 09/13/2010
* @brief STM32VLDISCOVERY abstraction layer.
* This file should be added to the main application to use the provided
* functions that manage the Leds LD3 and LD4 and the USER push-button.
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
void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_langth);
void MCO_config(void);
void rtc_init(void);
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, FREQ_TEST_GPIO_PORT, LED2_GPIO_PORT, SDI_GPIO_PORT, CLK_GPIO_PORT, STR_GPIO_PORT, OE_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, FREQ_TEST_PIN, LED2_PIN, SDI_PIN, CLK_PIN, STR_PIN, OE_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, FREQ_TEST_GPIO_CLK, LED2_GPIO_CLK, SDI_GPIO_CLK, CLK_GPIO_CLK, STR_GPIO_CLK, OE_GPIO_CLK};

extern uint8_t* g_led_effect_ptr;

extern CONFIG_MESSAGE_PTR g_uart_buffer;
extern TIME g_app_config_time;
extern ALARM g_app_config_alarm;
extern LED_EFFECT *g_app_led_effect;
extern uint32_t g_app_crc_code;
extern uint16_t g_app_length;
extern uint32_t g_app_header_code;
extern uint16_t g_effect_length;
extern flashcallback fcallback;

uint8_t pwm_c[8];
uint8_t pwm_num;
volatile uint16_t DATA_OUT;
UART_CALLBACK uart_process_callback;
static STRUCT_PACKET_EFFECT *packet_effect;
static PACKET_STATUS packet_stt = PK_IDLE;
static uint16_t data_count = 0;
static uint8_t *temp;
static uint8_t *effect_data_ptr;

void jupiter_cpu_init(void)
{
        uint8_t test = 200;
	/* Initialise LEDs LD3&LD4, both off */
	STM32vldiscovery_LEDInit(LED1);
	// cablirate HSI
	jupiterHSICab_init();

	/* Initialise LEDs LD3&LD4, both off */
	//STM32vldiscovery_LEDInit(LED1);
	STM32vldiscovery_LEDOff(LED1);

	// test clock source
	MCO_config();

	// init rtc
	rtc_init();

	// Init UART
	uart_init(uart_buffer_process);
    
    // Init Flash
    flash_init();
	/* Enable GPIOx Clock */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	// Init hardware SPI
	spi_init(); // ok
	// Init sofrware spi
	//spi_595_init();

	/* Setup SysTick Timer for 1 msec interrupts */

	if (SysTick_Config(SystemCoreClock / 10000))
	{
	/* Capture error */
	 while (1);
	}

	// init lcd
	//lcd_Init();

	/* Enable access to the backup register => LSE can be enabled */
	// PWR_BackupAccessCmd(ENABLE);
//    fcallback(&test, 1);
}

void jupiter_adj_init(void)
{

}

/**
* @brief parse data from uart_buffer
*/
void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_langth)
{
    uint8_t index;
    uint8_t *add_temp_ptr;
    uint8_t data_length;
    uint16_t length;
    //if(packet_stt == )
    packet_effect = (STRUCT_PACKET_EFFECT*)pk_ptr;
    if((packet_stt == PK_IDLE) || (packet_stt == PK_DONE))
    {
        length  = packet_effect->length_h<<8 | packet_effect->length_l;
        //if((length - 5) <= DATASIZE_PER_FRAME)
            data_length = length - 4;
        //else
        //    data_length = length - 4;
    }
    if(packet_stt == PK_REMAIN)
    {
    	effect_data_ptr = packet_effect->data;
    	data_length = length;
    }

    effect_data_ptr = (uint8_t*)malloc(data_length);
	memset(effect_data_ptr, 0, data_length);
	memcpy(effect_data_ptr, &packet_effect->data_type + 1, data_length);
	// call write to flash
	fcallback(effect_data_ptr, data_length, (uint8_t)packet_stt);
	// free mem
	free(effect_data_ptr);

    add_temp_ptr = pk_ptr;
	if(add_temp_ptr[f_langth - 1] == EOP)
	{
		packet_stt = PK_DONE;
	}
	else
	{
		packet_stt = PK_REMAIN;
	}
}

/**
* @brief store data in flash
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
* @brief get data from flash
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
* @brief Configures LED GPIO.
* @param Led: Specifies the Led to be configured.
* This parameter can be one of following parameters:
* @arg LED1
* @retval None
*/
void STM32vldiscovery_LEDInit(Led_TypeDef Led)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the GPIO_LED Clock */
	RCC_APB2PeriphClockCmd(GPIO_CLK[Led], ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

/**
* @brief Turns selected LED On.
* @param Led: Specifies the Led to be set on.
* This parameter can be one of following parameters:
* @arg LED3
* @arg LED4
* @retval None
*/
void STM32vldiscovery_LEDOn(Led_TypeDef Led)
{
	GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
* @brief Turns selected LED Off.
* @param Led: Specifies the Led to be set off.
* This parameter can be one of following parameters:
* @arg LED3
* @arg LED4
* @retval None
*/
void STM32vldiscovery_LEDOff(Led_TypeDef Led)
{
	GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

/**
* @brief Toggles the selected LED.
* @param Led: Specifies the Led to be toggled.
* This parameter can be one of following parameters:
* @arg LED3
* @arg LED4
* @retval None
*/
void STM32vldiscovery_LEDToggle(Led_TypeDef Led)
{
	GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/*
LED PWM over software SPI
*/
void SoftPWM(void)
{
	spi_595_send((pwm_c[0] > pwm_num) ? 0:DATA_OUT);
	if(++pwm_num==50){			
		pwm_num=0;
	}
}

/*
LED PWM over hardware SPI
*/
void HardLEDPWM(void)
{
	hard_spi_send_595((pwm_c[0] > pwm_num) ? 0:DATA_OUT);
	if(++pwm_num==50){			
		pwm_num=0;
	}
}

// config MCO A8
void MCO_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	AFIO->MAPR &= 0; // clear remap
	/* Enable GPIOA clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure MCO output pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//enable clock for alternate function
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	// select clock source
	RCC_MCOConfig(RCC_MCO_SYSCLK);// SYSTEMCLK selected
	// RCC_MCOConfig(RCC_MCO_HSI);// HSI selected
	// RCC_MCOConfig(RCC_MCO_HSE);// HSE selected
	// RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);// SYSTEMCLK selected
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