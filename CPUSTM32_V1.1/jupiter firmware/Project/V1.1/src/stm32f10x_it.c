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
/** @addtogroup Demo
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define EXTTRIG_SWSTART      (u32)(0x00500000)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern __IO int16_t IN_Buffer[2][160], OUT_Buffer[2][160];
extern __IO uint8_t Start_Playing;
extern __IO uint8_t Recording;
extern __IO uint8_t Playing;
extern __IO uint8_t Start_Encoding;
extern __IO uint8_t Start_Decoding;
extern uint32_t Encoded_Frames;
extern __IO int16_t *inBuffer;
extern __IO int16_t *outBuffer;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
static uint32_t tick = 0;
void SysTick_Handler(void)
{
	if(tick++ == 10000)
	{		
		tick = 0;
		LEDstatus();
	}
	//SoftPWM();
	HardLEDPWM();
	TimingDelay_Decrement();
}

void USART1_IRQHandler(void)
{
	USART_ClearFlag(J_UART, USART_FLAG_RXNE);
	printf("\nTest %d %x %f", RTC_GetCounter(), RTC_GetCounter(), 1.2);
//	switch(J_UART->SR)
//	{
//	case USART_FLAG_RXNE:
//		uart_get_data();
//		break;
//	case USART_FLAG_ORE:
//		break;
//	case USART_FLAG_TC:
//		break;
//	case USART_FLAG_TXE:
//		break;
//	}

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
	if(tick++ == 10)
	{
		LEDstatus();
		tick = 0;
	}
}

/**
* @brief  This function handles RTC_IRQHandler .
* @param  None
* @retval : None
*/
void RTC_IRQHandler(void)
{
	//  uint8_t Month,Day;
	//  uint16_t Year;
	//  
	//  Month = BKP_ReadBackupRegister(BKP_DR2);
	//  Day = BKP_ReadBackupRegister(BKP_DR3);
	//  Year = BKP_ReadBackupRegister(BKP_DR4);
	//  NVIC_ClearPendingIRQ(RTC_IRQn);
	//  RTC_ClearITPendingBit(RTC_IT_SEC);
	//  
	//  /* If counter is equal to 86399: one day was elapsed */
	//  /* This takes care of date change and resetting of counter in case of
	//  power on - Run mode/ Main supply switched on condition*/
	//  if(RTC_GetCounter() == 86399)
	//  {
	//    /* Wait until last write operation on RTC registers has finished */
	//    RTC_WaitForLastTask();
	//    /* Reset counter value */
	//    RTC_SetCounter(0x0);
	//    /* Wait until last write operation on RTC registers has finished */
	//    RTC_WaitForLastTask();

	//    /* Increment the date */
	//    DateUpdate();
	//  }

	//  if((RTC_GetCounter()/3600 == 1)&&(((RTC_GetCounter()%3600)/60) == 59)&&
	//     (((RTC_GetCounter()%3600)%60) == 59))
	//  {
	//    /* March Correction */
	//    if((Month == 3) && (Day >24))
	//    {
	//      if(WeekDay(Year,Month,Day)==0)
	//      {
	//        if((SummerTimeCorrect & 0x8000) == 0x8000)
	//        {
	//          RTC_SetCounter(RTC_GetCounter() + 3601);
	//         
	//          /* Reset March correction flag */
	//          SummerTimeCorrect &= 0x7FFF;
	//         
	//          /* Set October correction flag  */
	//          SummerTimeCorrect |= 0x4000;
	//          SummerTimeCorrect |= Year;
	//          BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
	//        }
	//      }
	//    }
	//      /* October Correction */
	//    if((Month == 10) && (Day >24))
	//    {
	//      if(WeekDay(Year,Month,Day)==0)
	//      {
	//        if((SummerTimeCorrect & 0x4000) == 0x4000)
	//        {
	//          RTC_SetCounter(RTC_GetCounter() - 3599);
	//          
	//          /* Reset October correction flag */
	//          SummerTimeCorrect &= 0xBFFF;
	//          
	//          /* Set March correction flag  */
	//          SummerTimeCorrect |= 0x8000;
	//          SummerTimeCorrect |= Year;
	//          BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
	//        }
	//      }
	//    }
	//  }
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

	//   if((BKP_ReadBackupRegister(BKP_DR8)==BKP_ReadBackupRegister(BKP_DR2)) && \
	//     (BKP_ReadBackupRegister(BKP_DR9)==BKP_ReadBackupRegister(BKP_DR3)) && \
	//      (BKP_ReadBackupRegister(BKP_DR10)==BKP_ReadBackupRegister(BKP_DR4)))
	//   {
	//     AlarmStatus = 1;
	//   }

	/* Clear the EXTI Line 17 */
	EXTI_ClearITPendingBit(EXTI_Line17);
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
* @brief  This function handles PPP interrupt request.
* @param  None
* @retval None
*/
/*void PPP_IRQHandler(void)
{
}*/


/**
* @}
*/ 

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
