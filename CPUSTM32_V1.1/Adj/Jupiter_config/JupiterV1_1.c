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

/** @defgroup STM32vldiscovery_Private_Variables
* @{
*/
static STRUCT_PACKET_EFFECT *packet_effect_ptr;
static PACKET_STATUS packet_stt = PK_IDLE;
static uint16_t remain = 0;
static uint16_t num_left = 0;
static uint8_t *effect_data_ptr;
static uint8_t packet_type;
static uint32_t effect_data_counter;
static BUFFSTACK *SF_Stack;
static EF_STT parse_stt;
static SFOR_STRUCT sfor_loop;
static uint32_t effect_length;
static uint8_t alarms_num;
static SET_ALARM_STT alarm_stt;
static uint8_t alarm_n = 0;
static uint8_t * alarm_check_ptr;

void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_length);
void write_to_flash(uint8_t *pk_ptr, uint8_t f_length);
void write_alarm(uint8_t *pk_ptr, uint8_t f_length);
void MCO_config(void);
void rtc_init(void);
uint8_t read_from_flash(uint32_t Address);
void alarm_load(uint8_t * temp);
bool get_alarm(ALARM_STRUCT * alarm_data_buff, uint8_t alarm_index);
void alarm_check(uint8_t * temp);

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, FREQ_TEST_GPIO_PORT, LED2_GPIO_PORT, SDI_GPIO_PORT, CLK_GPIO_PORT, STR_GPIO_PORT, OE_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, FREQ_TEST_PIN, LED2_PIN, SDI_PIN, CLK_PIN, STR_PIN, OE_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, FREQ_TEST_GPIO_CLK, LED2_GPIO_CLK, SDI_GPIO_CLK, CLK_GPIO_CLK, STR_GPIO_CLK, OE_GPIO_CLK};

extern flashcallback fcallback;
extern void jupiter_write_stt(uint32_t buff, uint32_t address);
extern PWM_STRUCT *pwm_data;
extern Time_s systime;

UART_CALLBACK uart_process_callback;
uint16_t on_min_counter = 0;
bool ALARM_START = FALSE;
ALARM_STRUCT alarm_data;
uint8_t * alarm_buffer_ptr = NULL;

void jupiter_cpu_init(void)
{
    // cablirate HSI
    jupiterHSICab_init();

    // test clock source
    MCO_config();

    // Init UART
    uart_init(uart_buffer_process);

    // Init Flash
    flash_init();
    /* Enable GPIOx Clock */
    // RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    // Init hardware SPI
    //spi_init(); // ok
    // Init sofrware spi
    softSPIPWM_init();
    // Led status init
    ledstt_init();

    /* Setup SysTick Timer for 1 msec interrupts */

    if (SysTick_Config(SystemCoreClock / 10000))
    {
        /* Capture error */
        while (1);
    }

    /* Enable access to the backup register => LSE can be enabled */
    // PWR_BackupAccessCmd(ENABLE);
    
    SF_Stack = StackInit(50); // TODO
    // dat tam o day
    pwm_data = (PWM_STRUCT*)malloc(LEDS * sizeof(PWM_STRUCT));
    if(pwm_data == NULL)
        while(1);
    memset(pwm_data, 0, LEDS);
    // load backup data
    effect_length = BKP_ReadBackupRegister(BKP_DR2) + FLASH_START_ADDRESS;
    alarms_num = (uint8_t)(BKP_ReadBackupRegister(BKP_DR5) >> 8);
    
    alarm_buffer_ptr = (uint8_t *)malloc(ALARM_ARRAY_SIZE);
    alarm_check_ptr = alarm_buffer_ptr;
    alarm_load(alarm_buffer_ptr);
    
    // init rtc
	rtc_init();
    
    // khoi tao LCD
    
    LCD1_Init();
    LCD1_Clear();
    LCD1_WriteLineStr(0, "Hello FRDM-KL25K");
    LCD1_WriteLineStr(1, "Led controller");
    LCD1_WriteLineStr(2, "Jupiter V1.2");
    LCD1_WriteLineStr(3, "1234567890ABCDEF");
}

/**
* @brief parse data from uart_buffer
*/
void uart_buffer_process(uint8_t *pk_ptr, uint8_t f_length)
{
    if((packet_stt == PK_IDLE) || (packet_stt == PK_DONE))
    {
        packet_effect_ptr = (STRUCT_PACKET_EFFECT*)pk_ptr;
        switch(packet_effect_ptr->data_type)
        {
            case DAT_EFFECT:
                packet_type = LDATA;
                write_to_flash(pk_ptr, f_length);
                return;
                break;
            case SET_INFO_TIME:
                set_time(&packet_effect_ptr->data_type + 1);
                break;
            case SET_INFO_ALARM:
                write_alarm(pk_ptr, f_length);
                break;
            case SET_INFO_LEDS:
                break;
            case GET_INFO_FIRM_VER:
                out_char(0xD6);
                out_char(VERSION);
                break;
        }
    }
    
    if(packet_stt == PK_REMAIN)
    {
        if(packet_type == LDATA)
        {
            write_to_flash(pk_ptr, f_length);
        }
    }
}

void write_alarm(uint8_t *pk_ptr, uint8_t f_length)
{
    uint8_t * tempx;
    uint8_t bkp_val;
    if(pk_ptr == NULL)
        return;
    tempx = pk_ptr;
    alarms_num = *(tempx + 4);
    bkp_val = (uint8_t)BKP_ReadBackupRegister(BKP_DR5);
    if(alarms_num > MAX_ALARM)
        return;
    BKP_ModifyBackupRegister(BKP_DR5, (alarms_num << 8) | bkp_val);
    fcallback(tempx + 5, f_length - 6, 7, ALARM_BEGIN_ADD, ALARM_END_ADD);
    
    alarm_load(alarm_buffer_ptr);    
    
    alarm_stt = ALARM_LOAD;
    alarm_n = 0;
}
/*
    call while minute elapse
*/

void alarm_load(uint8_t * temp)
{
    uint16_t Start;
    uint16_t Stop;
    uint16_t index__;
    uint8_t i;
    uint8_t * mem_head;

    if(temp == NULL)
        return;
    memset(temp, 0, ALARM_ARRAY_SIZE);
    mem_head = temp;
    for(i = 0; i< alarms_num; i++)
    {
        if(get_alarm(&alarm_data, i) != TRUE)
            break;
        Start = (alarm_data.on_hour * 60 + alarm_data.on_min) / 5;
        if(alarm_data.on_time > MAX_TIME_ON)
            break;
        else
            Stop = Start + alarm_data.on_time;
        index__ = 0;
        temp = mem_head;
        while(1)
        {
            if(((index__ % 8) == 0) && (index__ != 0))
            {
                temp++;
            }

            if((index__ >= Start) && (index__ < Stop))
                *temp |= (SHIFTVAL << (index__ % 8));
            if(index__ >= Stop)
                break;
            index__++;
        }
    }
}

bool get_alarm(ALARM_STRUCT * alarm_data_buff, uint8_t alarm_index)
{
    ALARM_LOAD_STT stt;
    uint8_t temp;
    uint8_t array[2], index = 0;
    uint8_t i;

    if(alarm_data_buff == NULL)
        return FALSE;
    if(alarm_index/ALARM_DATA_SIZE > alarms_num)
    {
        alarm_index = 0;
        return FALSE;
    }
    else
    {
        index = 0;
        alarm_index *= ALARM_DATA_SIZE;
        for(i = 0; i < ALARM_DATA_SIZE; i++)
        {
            temp = read_from_flash(alarm_index + ALARM_BEGIN_ADD);
            alarm_index++;
            if(temp == ALARM_N)
            {
                stt = READ_HOUR;
                continue;
            }
            switch(stt)
            {
                case READ_HOUR:
                    alarm_data_buff->on_hour = temp;
                    stt = READ_MIN;
                    break;
                case READ_MIN:
                    alarm_data_buff->on_min = temp;
                    stt = READ_TIME;
                    break;
                case READ_TIME:
                    array[index] = temp;
                    index++;
                    break;
            }
        }
    alarm_data_buff->on_time = (array[0] << 8) | array[1];
    alarm_stt = CHECK_ALARM;
    return TRUE;
    }
}

void alarm_check(uint8_t * alarm_ptr)
{
    uint8_t shift_count = 0;
    uint16_t alarm_index;

    if(alarm_ptr == NULL)
        return;

    alarm_index = (systime.Hour*60 + systime.Min) / 5;
    alarm_check_ptr = alarm_ptr + (alarm_index / 8);
    shift_count = alarm_index % 8;
    if(alarm_index == 0)
        alarm_check_ptr = alarm_ptr;

    if(*alarm_check_ptr & (SHIFTVAL << shift_count))
        ALARM_START = TRUE;
    else
        ALARM_START = FALSE;
}

/**
* @brief store data in flash
*/
void write_to_flash(uint8_t *pk_ptr, uint8_t f_length)
{
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
        BKP_ModifyBackupRegister(BKP_DR2, length);
        num_left = length;
        length += 5;
        if(length > DATASIZE_PER_FRAME)
        {
            data_length = DATASIZE_PER_FRAME - 4;
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
        
        effect_data_ptr = (uint8_t*)malloc(DATASIZE_PER_FRAME);
        memset(effect_data_ptr, 0, DATASIZE_PER_FRAME);
        memcpy(effect_data_ptr, pk_ptr, data_length);
    }

    // call write to flash
    fcallback(effect_data_ptr, data_length, (uint8_t)packet_stt, EFFECT_BEGIN_ADD, EFFECT_END_ADD);
    // free mem
    free(effect_data_ptr);
    
    num_left -= data_length;
    remain = num_left;
    
    if((add_temp_ptr[f_length - 1] == EOP) && (remain == 0))
    {
        packet_stt = PK_DONE;
        bkp_val = BKP_ReadBackupRegister(BKP_DR1);
        bkp_val |= BKP_EFFECT_AVAL;
        BKP_ModifyBackupRegister(BKP_DR1, (uint16_t)bkp_val);
    }
    else
    {
        packet_stt = PK_REMAIN;
        bkp_val = BKP_ReadBackupRegister(BKP_DR1);
        bkp_val &= ~BKP_EFFECT_AVAL;
        BKP_ModifyBackupRegister(BKP_DR1, (uint16_t)bkp_val);
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
    uint8_t index;
    uint8_t loop_remain;
    uint8_t loop;
    uint16_t delay_val;
    uint8_t *temp1;
    uint8_t ledPosition = 0;
    if(BKP_ReadBackupRegister(BKP_DR1) == (uint8_t)BKP_EFFECT_AVAL)
    {
    effect_data_counter = EFFECT_BEGIN_ADD;
    while(effect_data_counter < effect_length)
    {
        if(ALARM_START == FALSE)
        {
            for(index = 0; index < LEDS; index++)
                pwm_data[index].pwm_ldval = 0;
            return;            
        }

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
                ledPosition = 0;
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
                delay_val = temp * 50;
                parse_stt = EF_STT_LED;
                 break;
            case EF_STT_LED:
                pwm_data[ledPosition].pwm_ldval = temp;
                ledPosition++;
                if(ledPosition >= LEDS)
                    Delay_ms(delay_val);
                break;
            default:
                break;
        }
    }
  }
}
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
