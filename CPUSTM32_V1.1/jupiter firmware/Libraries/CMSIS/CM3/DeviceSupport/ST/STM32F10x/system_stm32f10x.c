/**
  ******************************************************************************
  * @file    system_stm32f10x.c
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  ******************************************************************************  
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f10x_system
  * @{
  */  
  
/** @addtogroup STM32F10x_System_Private_Includes
  * @{
  */

#include "stm32f10x.h"
#include "common_config.h"

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_Defines
  * @{
  */

/*!< Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)
   
   IMPORTANT NOTE:
   ============== 
   1. After each device reset the HSI is used as System clock source.

   2. Please make sure that the selected System clock doesn't exceed your device's
      maximum frequency.
      
   3. If none of the define below is enabled, the HSI is used as System clock
    source.

   4. The System clock configuration functions provided within this file assume that:
        - For Low and Medium density Value line devices an external 8MHz crystal 
          is used to drive the System clock.
        - For Low, Medium and High density devices an external 8MHz crystal is
          used to drive the System clock.
        - For Connectivity line devices an external 25MHz crystal is used to drive
          the System clock.
     If you are using different crystal you have to adapt those functions accordingly.
    */
/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_Variables
  * @{
  */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
uint32_t SystemCoreClock         = SYSCLK;        /*!< System Clock Frequency (Core Clock) */

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_FunctionPrototypes
  * @{
  */

void SetSysClock(void);
static void SetSysClockHSE24MHz(void);
static void SetSysClockHSI24MHz(void);

/**
  * @}
  */

/** @addtogroup STM32F10x_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
	// clear RCC_CR
	RCC->CR &= 0;
	
  /* Reset HSION, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)~RCC_CR_PLLON |
	                     ~RCC_CR_CSSON |
	                     ~RCC_CR_HSEON |
	                     ~RCC_CR_HSEBYP|
	                     ~RCC_CR_HSION;

	// clear RCC_CR
	RCC->CFGR &= 0;
  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
  RCC->CFGR &= (uint32_t)(~RCC_CFGR_MCO) | 
	                        ~RCC_CFGR_PLLMULL |
	                        ~RCC_CFGR_PLLXTPRE |
	                        ~RCC_CFGR_PLLSRC;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = RCC_CIR_CSSC |
	           RCC_CIR_PLLRDYC |
						 RCC_CIR_HSERDYC |
						 RCC_CIR_HSIRDYC|
						 RCC_CIR_LSERDYC|
						 RCC_CIR_LSIRDYC;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;      
    
  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock();
	/* MCO as HSI */
	RCC->CFGR |= RCC_CFGR_MCO_HSI;
}

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  * @note   None
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0;
  uint32_t prediv1factor = 0;
    
  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
  
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      SystemCoreClock = HSI_Value;
      break;
    case 0x04:  /* HSE used as system clock */
      SystemCoreClock = HSE_Value;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
      
      pllmull = ( pllmull >> 18) + 2;
      
      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        SystemCoreClock = (HSI_Value >> 1) * pllmull;
      }
      else
      {
       prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
       /* HSE oscillator clock selected as PREDIV1 clock entry */
       SystemCoreClock = (HSE_Value / prediv1factor) * pllmull; 
      }

      break;

    default:
      SystemCoreClock = HSI_Value;
      break;
  }
  
  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;  
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
	work around
  */
void SetSysClock(void)
{
#if USE_HSE
  SetSysClockHSE24MHz();
#else
  SetSysClockHSI24MHz();
#endif
 
 /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

/**
  * @brief  Selects HSE as System clock source and configure HCLK, PCLK2
  *          and PCLK1 prescalers. 24MHz
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockHSE24MHz(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
	// clear CR
	RCC->CR &= 0;
  /* Enable HSE */
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
	RCC->CR &= ((uint32_t)~RCC_CR_HSION);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
//  } while((HSEStatus == 0) && (StartUpCounter != HSEStartUp_TimeOut));
		} while(HSEStatus == 0);

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
		// hse ok
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  
  // clesr CFGR
	RCC->CFGR &= 0;
	// config CFGR
  if (HSEStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
    
		/* select PLL MUL */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PLLMULL6;
		
		// select PREDIV1
		RCC->CFGR2 |= (uint32_t)RCC_CFGR2_PREDIV1_DIV2;

		// select PLL source
		RCC->CFGR |= (uint32_t)RCC_CFGR_PLLSRC;
		
    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL ;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
		while(1); // loop forever
  }  
}

/**
  * @brief  Sets System clock frequency to 24MHz and configure HCLK, PCLK2 
  *          and PCLK1 prescalers.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClockHSI24MHz(void)
{
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSI */    
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
 
  /* Wait till HSI is ready and if Time out is reached exit */
  do
  {
    HSIStatus = RCC->CR & RCC_CR_HSIRDY;
    StartUpCounter++;  
  } while((HSIStatus == 0) && (StartUpCounter != HSIStartUp_TimeOut));

  if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
  {
		// hsi ok
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }  

  if (HSIStatus == (uint32_t)0x01)
  {
    /* HCLK = SYSCLK (AHB div 1)*/
    RCC->CFGR |= (uint32_t)0;
      
    /* PCLK2 = HCLK (APB2 div 1)*/
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK (APB1 div 1)*/
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;
    
    /*  PLL configuration:  = (HSI / 2) * 6 = 24 MHz */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)RCC_CFGR_PLLMULL6;

    /* Enable PLL */
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }

    /* Select PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
		while(1); // loop forever
  } 
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
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
