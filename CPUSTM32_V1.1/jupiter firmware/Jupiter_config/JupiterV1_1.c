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
#include "timer_delay.h"

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
static STRUCT_PACKET_EFFECT *packet_effect_ptr;
static PACKET_STATUS packet_stt = PK_IDLE;
static uint16_t data_count = 0;
static uint16_t total_frame = 0;
static uint16_t frame_count = 0;
static uint16_t remain = 0;
static uint16_t num_left = 0;
static uint8_t *temp;
static uint8_t *effect_data_ptr;
static uint8_t packet_type;
static uint32_t effect_data_counter;
static BUFFSTACK *SF_Stack;
static EF_STT parse_stt;
static SFOR_STRUCT sfor_loop;
static uint32_t effect_length;

void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_length);
void write_to_flash(uint8_t *pk_ptr, uint8_t f_length);
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
extern void jupiter_write_stt(uint32_t buff, uint32_t address);

uint8_t pwm_c[8];
uint8_t pwm_num;
volatile uint16_t DATA_OUT;
UART_CALLBACK uart_process_callback;


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

	/* Enable access to the backup register => LSE can be enabled */
	// PWR_BackupAccessCmd(ENABLE);
    
    SF_Stack = StackInit(200); // TODO
    // load backup data
    effect_length = BKP_ReadBackupRegister(BKP_DR2) + FLASH_START_ADDRESS;
}

/**
* @brief parse data from uart_buffer
*/
uint8_t remain_counter = 0;
void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_length)
{
    if((packet_stt == PK_IDLE) || (packet_stt == PK_DONE))
    {
        packet_effect_ptr = (STRUCT_PACKET_EFFECT*)pk_ptr;
        if(packet_effect_ptr->data_type == DAT_EFFECT)
        {
            packet_type = LDATA;
            write_to_flash(pk_ptr, f_length);
            return;
        }
    }
    
    if(packet_stt == PK_REMAIN)
    {
        remain_counter++;
        if(remain_counter == 2)
            remain_counter = 0;
        if(packet_type == LDATA)
        {
            write_to_flash(pk_ptr, f_length);
        }
    }
}

/**
* @brief store data in flash
*/
void write_to_flash(uint8_t *pk_ptr, uint8_t f_length)
{
    uint8_t index;
    uint8_t *add_temp_ptr;
    uint8_t data_length;
    uint16_t length;
    uint16_t bkp_val;
    //if(packet_stt == )
    packet_effect_ptr = (STRUCT_PACKET_EFFECT*)pk_ptr;
    add_temp_ptr = pk_ptr;
    if((packet_stt == PK_IDLE) || (packet_stt == PK_DONE))
    {
        length  = packet_effect_ptr->length_h<<8 | packet_effect_ptr->length_l;
        effect_length = length + FLASH_START_ADDRESS;
        BKP_WriteBackupRegister(BKP_DR2, length);
        num_left = length;
        length += 5;
	    if(length > DATASIZE_PER_FRAME)
	    {
	    	data_length = 28;
	    }
        else
            data_length = length - 5;
            
        effect_data_ptr = (uint8_t*)malloc(data_length);
        memset(effect_data_ptr, 0, data_length);
        memcpy(effect_data_ptr, &packet_effect_ptr->data_type + 1, data_length);
    }
    
    if(packet_stt == PK_REMAIN)
    {
        if(remain > DATASIZE_PER_FRAME)
            data_length = DATASIZE_PER_FRAME;
        else
            data_length = remain;
        
        effect_data_ptr = (uint8_t*)malloc(32);
        memset(effect_data_ptr, 0, 32);
        memcpy(effect_data_ptr, pk_ptr, data_length);
    }

	// call write to flash
	fcallback(effect_data_ptr, data_length, (uint8_t)packet_stt);
	// free mem
	free(effect_data_ptr);
    
    num_left -= data_length;
    remain = num_left;
    
	if((add_temp_ptr[f_length - 1] == EOP) && (remain == 0))
	{
        packet_stt = PK_DONE;
        bkp_val = BKP_ReadBackupRegister(BKP_DR1);
        bkp_val |= BKP_EFFECT_AVAL;
        BKP_WriteBackupRegister(BKP_DR1, (uint16_t)bkp_val);
	}
	else
	{
		packet_stt = PK_REMAIN;
        bkp_val = BKP_ReadBackupRegister(BKP_DR1);
        bkp_val &= ~BKP_EFFECT_AVAL;
        BKP_WriteBackupRegister(BKP_DR1, (uint16_t)bkp_val);
	}
}

/**
* @brief get data from flash
*/
uint8_t read_from_flash(uint32_t Address)
{
	if(Address < FLASH_START_ADDRESS)
        return 0;
    return (uint8_t)*(uint32_t*)Address;
}

void effect_run(void)
{
    uint8_t temp;
    uint8_t loop_remain;
    uint8_t loop;
    uint8_t shift_val = 0;
    uint16_t delay_val;
    uint8_t *temp1;
    if(BKP_ReadBackupRegister(BKP_DR1) == (uint8_t)BKP_EFFECT_AVAL)
    {
    effect_data_counter = EFFECT_BEGIN_ADD;
    while(effect_data_counter < effect_length)
    {
        temp = read_from_flash(effect_data_counter);
        effect_data_counter++;
        switch(temp)
        {
            case EFFCT_DT_STARTFOR:
                parse_stt = EF_STT_STARTFOR;
                continue;
                break;
            case EFFCT_DT_ENDTFOR:
                parse_stt = EF_STT_ENDFOR;
                break;
            case EFFCT_DT_BRIGHT:
                parse_stt = EF_STT_DELAY;
                continue;
                break;
        }
        
        switch(parse_stt)
        {
            case EF_STT_STARTFOR:
                sfor_loop.loop_times = temp;
                sfor_loop.sfor_add = effect_data_counter;
                PushStack(SF_Stack, &sfor_loop, sizeof(sfor_loop));
                parse_stt = EF_STT_IDLE;
                break;
            case EF_STT_ENDFOR:
                loop_remain = (uint8_t)*SF_Stack->top;
                temp1 = SF_Stack->top;
                if(loop_remain <= 1)
                {
                    PopStack(SF_Stack, &loop, sizeof(sfor_loop));
                    memcpy(&sfor_loop.loop_times, SF_Stack->top, sizeof(sfor_loop));
                    parse_stt = EF_STT_IDLE;
                }
                else
                {
                    // quay lai startfor
                    effect_data_counter = sfor_loop.sfor_add;
                    *temp1 -= 1;
                    parse_stt = EF_STT_IDLE;
                }
                break;
            case EF_STT_DELAY:
                if(shift_val < 8)
                {
                    delay_val = temp;
                    shift_val += 8;
                    parse_stt = EF_STT_DELAY;
                }
                else
                {
                    delay_val <<= shift_val;
                    delay_val |= temp;
                    parse_stt = EF_STT_LED;
                    shift_val = 0;
                    Delay_ms(delay_val);
                }
                 break;
            case EF_STT_LED:
                pwm_c[0] = temp;
                parse_stt = EF_STT_DELAY;
                break;
            default:
                break;
        }
    }
    }
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