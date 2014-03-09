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
#include "stack.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  LSE_FAIL_FLAG  0x80
#define  LSE_PASS_FLAG  0x100
/* Private macro -------------------------------------------------------------*/
/* Private consts ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Delay_ms(uint32_t nTime);
void TimingDelay_Decrement(void);
void delay_test(uint32_t delay);
void led_dim_ti(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  jupiter_cpu_init();
  /* main while */
  while(1)
  {
      //crc_rl = calc_crc8((uint8_t*)&crc_test, 4);
      //nam_count = RTC_GetCounter();
#if 0
		spi_595_send(0xFF00);
		Delay_ms(2000);
		spi_595_send(0x00FF);
		Delay_ms(2000);
#else
		//led_dim_ti();
        effect_run();
#endif
  }
}

void LEDstatus(void)
{
  STM32vldiscovery_LEDToggle(LED1);
}

void led_dim_ti(void)
{
	char i,k;
	for(k=0;k<16;k++)
	{
		for(i=50;i>0;i--){
//			pwm_c[j] = i;
			Delay_ms(100);
		}
		for(i=0;i<50;i++){
//			pwm_c[j] = i;
			Delay_ms(100);
		}
		//DATA_OUT |= 1<<k;
	}
}

/**
  * @}
  */
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
