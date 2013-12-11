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
int pwm_c[8];
int pwm_num;
int delay_in_t1;
volatile uint16_t DATA_OUT;
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
volatile uint16_t nam_count = 0;
int main(void)
{
  /* Enable GPIOx Clock */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  
  /* Initialise LEDs LD3&LD4, both off */
  STM32vldiscovery_LEDInit(LED1);
	//STM32vldiscovery_LEDInit(LED2);

  STM32vldiscovery_LEDOff(LED1);
	//STM32vldiscovery_LEDOff(LED2);
  
	// Init hardware SPI
	//spi_init(); // ok
	// Init sofrware spi
	//spi_595_init();
	// Init Timer for PWM
	// Init UART
	uart_init();

  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config(SystemCoreClock / 10000))
  {
    /* Capture error */ 
    while (1);
  }
	
  // init lcd
	//lcd_Init();

  /* Enable access to the backup register => LSE can be enabled */
//  PWR_BackupAccessCmd(ENABLE);
  
  /* main while */
  while(1)
  {
		uart_send(0x41);

//		LCD_putc('A');
#if 0
		spi_595_send(0x5555);
		Delay_ms(500);
		spi_595_send(0xAAAA);
		Delay_ms(500);
#else
//		led_dim_ti();
#endif
//    if(0 == STM32vldiscovery_PBGetState(BUTTON_USER))
//      {
//        if(KeyState == 1)
//        {
//           if(0 == STM32vldiscovery_PBGetState(BUTTON_USER))
//          {
//            /* USER Button released */
//              KeyState = 0;
//            /* Turn Off LED4 */
//              STM32vldiscovery_LEDOff(LED4);
//          }       
//        }
//      }
//    else if(STM32vldiscovery_PBGetState(BUTTON_USER))
//      { 
//        if(KeyState == 0)
//        {
//           if(STM32vldiscovery_PBGetState(BUTTON_USER))
//          {
//            /* USER Button released */
//              KeyState = 1;
//            /* Turn ON LED4 */
//            STM32vldiscovery_LEDOn(LED4);
//            Delay(1000);
//            /* Turn OFF LED4 */
//            STM32vldiscovery_LEDOff(LED4);
//            /* BlinkSpeed: 0 -> 1 -> 2, then re-cycle */    
//              BlinkSpeed ++ ; 
//          }
//        }
//      }
//        count++;
//        Delay(100);
//      /* BlinkSpeed: 0 */ 
//      if(BlinkSpeed == 0)
//          {
//            if(4 == (count % 8))
//            STM32vldiscovery_LEDOn(LED3);
//            if(0 == (count % 8))
//            STM32vldiscovery_LEDOff(LED3);
//         }
//           /* BlinkSpeed: 1 */ 
//           if(BlinkSpeed == 1)
//          {
//            if(2 == (count % 4))
//            STM32vldiscovery_LEDOn(LED3);
//            if(0 == (count % 4))
//            STM32vldiscovery_LEDOff(LED3);
//          }  
//          /* BlinkSpeed: 2 */        
//          if(BlinkSpeed == 2)
//          {
//            if(0 == (count % 2))
//            STM32vldiscovery_LEDOn(LED3);
//            else
//            STM32vldiscovery_LEDOff(LED3);     
//          }     
//          /* BlinkSpeed: 3 */ 
//          else if(BlinkSpeed == 3)
//        BlinkSpeed = 0;
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

void SoftPWM(void)
{
	spi_595_send((pwm_c[0] > pwm_num) ? 0:DATA_OUT);
	if(++pwm_num==50){			
		pwm_num=0;
	}
}

void led_dim_ti(void)
{
	char i,j,k;
	DATA_OUT = 0x8181;
	for(k=0;k<16;k++)
	{
		j=0;

//		printf("\n\n\n", i);
		for(i=50;i>0;i--){
			pwm_c[j] = i;
//			pwm_num = 0;
//			printf("%d \n", i);
			Delay_ms(50);
		}
//		printf("\n\n\n", i);
		for(i=0;i<50;i++){
			pwm_c[j] = i;
//			pwm_num = 0;
//			printf("%d \n", i);
			Delay_ms(50);
		}
		DATA_OUT |= 1<<k;
		
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
