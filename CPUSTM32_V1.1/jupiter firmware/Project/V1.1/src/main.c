/**
  ******************************************************************************
  * @file    Demo/src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    09/13/2010
  * @brief   Main program body
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
#include "stm32F10x.h"
#include "JupiterV1_1.h"
#include "lcd.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  LSE_FAIL_FLAG  0x80
#define  LSE_PASS_FLAG  0x100
/* Private macro -------------------------------------------------------------*/
/* Private consts ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
u32 LSE_Delay = 0;
u32 count = 0;
u32 BlinkSpeed = 0;

CONFIG_MESSAGE_PTR g_uart_buffer;
uint8_t* g_led_effect_ptr;

TIME 				g_app_config_time;
ALARM 			g_app_config_alarm;
LED_EFFECT *g_app_led_effect;
uint32_t 		g_app_crc_code;
uint16_t		g_app_length;
uint32_t		g_app_header_code;
uint16_t 		g_effect_length;

static __IO uint32_t TimingDelay;
int delay_in_t1;
uint16_t nam_count;
/* Private function prototypes -----------------------------------------------*/
void Delay_ms(uint32_t nTime);
void TimingDelay_Decrement(void);
void delay_test(uint32_t delay);
void led_dim_ti(void);
extern volatile uint16_t DATA_OUT;
extern uint8_t pwm_c[8];
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t crc_test = 0x12345678;
    uint32_t crc_rl;
  jupiter_cpu_init();
  /* main while */
  while(1)
  {
      //crc_rl = calc_crc8((uint8_t*)&crc_test, 4);
      //crc_rl ^= 0xFFFFFFFF;
		//nam_count = RTC_GetCounter();
//		LCD_putc('A');
#if 0
		//hard_spi_send_595(0xFF00);
		spi_595_send(0xFF00);
		Delay_ms(500);
		//hard_spi_send_595(0x00FF);
		spi_595_send(0x00FF);
		Delay_ms(500);
#else
		led_dim_ti();
#endif
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay_ms(uint32_t nTime)
{ 
  TimingDelay = nTime*10;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable and blink led system status
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

void LEDstatus(void)
{
  STM32vldiscovery_LEDToggle(LED1);
}



void led_dim_ti(void)
{
	char i,j,k;
	//DATA_OUT = 0x8181;
	DATA_OUT = 0xFFFF;
	for(k=0;k<16;k++)
	{
		j=0;
		for(i=50;i>0;i--){
			pwm_c[j] = i;
			Delay_ms(50);
		}
		for(i=0;i<50;i++){
			pwm_c[j] = i;
			Delay_ms(50);
		}
		//DATA_OUT |= 1<<k;
		
	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
