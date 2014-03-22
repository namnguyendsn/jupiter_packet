/**
  ******************************************************************************
  * @file    	LCD/LCD_16x2/main.c
  * @author  	ARMVN Application Team
  * @version 	V1.0.0
  * @date    	02/28/2010
  * @brief   	Main program body.
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
  * <h2><center>&copy; COPYRIGHT 2009 ARMVietNam</center></h2>
  */ 

  
/*
*************************************************************************************************************************************
*															INCLUDED FILES															*
*************************************************************************************************************************************
*/
#include <stdio.h>
#include "main.h"
#include "lcd.h"

/** @addtogroup STM32F10x_GEM3M_Examples
  * @{
  */

/** @addtogroup LCD_16X2
  * @{
  */  

  
/*
*************************************************************************************************************************************
*															PRIVATE DEFINE															*
*************************************************************************************************************************************
*/


/*
*************************************************************************************************************************************
*														 	DATA TYPE DEFINE															*
*************************************************************************************************************************************
*/


/*
*************************************************************************************************************************************
*													   		PRIVATE VARIABLES														*
*************************************************************************************************************************************
*/ 

/*
*************************************************************************************************************************************
*							  								LOCAL FUNCTIONS															*
*************************************************************************************************************************************
*/
/**
  * @brief  	Configures the different system clocks.
  * @param  	None
  * @retval 	None
  */
void RCC_Configuration(void)
{
	/* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
	initialize the PLL and update the SystemFrequency variable. */
	//SystemInit();
}

/**
  * @brief  	Inserts a delay time with resolution is 10 milisecond..
  * @param  	nCount: specifies the delay time length.
  * @retval 	None
  */
void Delay(__IO uint32_t num)
{
	__IO uint32_t index = 0;

	/* default system clock is 72MHz */
	for(index = (72000 * num); index != 0; index--)
	{
	}
}

/*
*************************************************************************************************************************************
*															GLOBAL FUNCTIONS														*
*************************************************************************************************************************************
*/
/**
  * @brief  	Main program.
  * @param  	None
  * @retval 	None
  */
int main(void)
{
	/* Configure the system clocks */
	RCC_Configuration();	
	
	/* initialize LCD */
	lcd_Init();		

	lcd_Clear();
	/* print message on LCD */
	lcd_GotoXY(0,0);
	printf("Sharing Tech in");
	lcd_GotoXY(1,0);
	printf("=> ARM Viet Nam");

	while (1)
	{	
		/* Insert delay */
		Delay(100);	
	}
}


#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
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

/******************* (C) COPYRIGHT 2009 ARMVietNam *****END OF FILE****/

