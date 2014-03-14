/**
******************************************************************************
* @file    Demo/src/stm32f10x_it.c 
* @author  MCD Application Team
* @version V1.0.0
* @date    09/13/2010
* @brief   Main Interrupt Service Routines.
*          This file provides template for all exceptions handler and peripherals
*          interrupt service routine.
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
#include "stm32f10x_it.h"
void TimingDelay_Decrement(void);
void uart_get_data(void);
void LEDstatus(void);
void SoftPWM(void);
void HardLEDPWM(void);
void HSI_FreqMeasure(void);
void alarm_check(void);
void CalculateTime(void);
/** @addtogroup Demo
* @{
*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO int16_t *outBuffer;

uint8_t AlarmStatus;
uint8_t AlarmDate=0;
uint8_t sec_count = 0;
static uint32_t sysTick = 0;
/* Private function prototypes -----------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
* @brief  This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}

/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
* @brief  This function handles Memory Manage exception.
* @param  None
* @retval None
*/
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
* @brief  This function handles Bus Fault exception.
* @param  None
* @retval None
*/
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
* @brief  This function handles Usage Fault exception.
* @param  None
* @retval None
*/
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
* @brief  This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  This function handles PendSV_Handler exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
	if(sysTick++ == 10000)
	{
		sysTick = 0;
		LEDstatus();
	}
	//SoftPWM();
	HardLEDPWM();
	TimingDelay_Decrement();
}

void USART1_IRQHandler(void)
{
//	printf("\nTest %d %x %f", RTC_GetCounter(), RTC_GetCounter(), 1.2);
    if(USART_GetITStatus(J_UART, USART_IT_RXNE))
	{
        USART_ClearFlag(J_UART, USART_FLAG_RXNE);
        uart_get_data();
	}
}


/**
* @brief  This function handles TIM3 interrupt request.
* @param  None
* @retval : None
*/
void TIM3_IRQHandler(void)
{
	/* Mesure the current HSI frequency corresponding to HSITRIM value */
	HSI_FreqMeasure();
	if(sysTick++ == 10)
	{
		LEDstatus();
		sysTick = 0;
	}
}

/**
  * @brief  This function handles RTC_IRQHandler .
  * @param  None
  * @retval : None
  */
void RTC_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(RTC_IRQn);
    RTC_ClearITPendingBit(RTC_IT_SEC);
    
    if(sec_count++ == 60)
    {
        sec_count = 0;
        CalculateTime();
        alarm_check();
    }
    /* If counter is equal to 86399: one day was elapsed */
    /* This takes care of date change and resetting of counter in case of
    power on - Run mode/ Main supply switched on condition*/
    if(RTC_GetCounter() == 86399)
    {
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
        /* Reset counter value */
        RTC_SetCounter(0x0);
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();

        /* Increment the date */
        DateUpdate();
    }
}

/**
  * @brief  This function handles RTCAlarm_IRQHandler .
  * @param  None
  * @retval : None
  */
void RTCAlarm_IRQHandler(void)
{
   /* Clear the Alarm Pending Bit */
   RTC_ClearITPendingBit(RTC_IT_ALR);
   printf("\nALARM");
   if(((uint8_t)(BKP_ReadBackupRegister(BKP_DR8) >> 8) == (uint8_t)(BKP_ReadBackupRegister(BKP_DR4) >> 8)) &&   // check phut
     ((uint8_t)BKP_ReadBackupRegister(BKP_DR9) == (uint8_t)BKP_ReadBackupRegister(BKP_DR4))) // check gio
   {
     AlarmStatus = 1;
   }
}

void FLASH_IRQHandler(void)
{
    while(1)
    {}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
