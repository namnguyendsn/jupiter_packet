/**
  ******************************************************************************
  * @file    	lcd.c
  * @author  	ARMVN Application Team
  * @version 	V1.0.0
  * @date    	28/02/2010
  * @brief   	This file provides firmware functions to manage LCD on STM32 GEM3M Boards from ARMVietNam.
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
  * <h2><center>&copy; COPYRIGHT 2010 ARMVietNam</center></h2>
  */ 
  
/*
*************************************************************************************************************************************
*															INCLUDED FILES															*
*************************************************************************************************************************************
*/
#include "lcd_4.h"

/* define macro for debug-------------------------------------------------------------------*/
#define DEBUG_LCD
extern void Delay_ms(uint32_t nTime);
static void LCD_command(uint8_t command);
static void lcd_Init_HW(void);
static void LCD_enable(void);
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
  * @brief  	initializes I/O pins connected to LCD.
  * @param  	None
  * @retval 	None
  */
static void lcd_Init_HW(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO clocks for LCD control pins */
	RCC_APB2PeriphClockCmd(LCD_RS_GPIO_CLK | LCD_EN_GPIO_CLK, ENABLE);

	/* initialize LCD control lines to output */
	GPIO_InitStructure.GPIO_Pin 	= LCD_RS_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(LCD_RS_GPIO_PORT, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin 	= LCD_EN_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_Init(LCD_EN_GPIO_PORT, &GPIO_InitStructure); 

	/* Enable GPIO clocks for LCD data pins */
	RCC_APB2PeriphClockCmd(LCD_DATA_GPIO_CLK, ENABLE);

	/* initialize LCD data port to output */
	GPIO_InitStructure.GPIO_Pin 	= LCD_DATA_GPIO_PINS;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(LCD_DATA_GPIO_PORT, &GPIO_InitStructure); 
	
}

//Ham cho phep hien thi len LCD
static void LCD_enable()
{
	//LCD_en = 0;
	GPIO_WriteBit(LCD_EN_GPIO_PORT, LCD_EN_GPIO_PIN, Bit_RESET);
  //LCD_delay();
	Delay_ms(1);
  //LCD_en = 1; 
	GPIO_WriteBit(LCD_EN_GPIO_PORT, LCD_EN_GPIO_PIN, Bit_SET);
  //LCD_delay();
	Delay_ms(1);
	//LCD_en = 0;
	GPIO_WriteBit(LCD_EN_GPIO_PORT, LCD_EN_GPIO_PIN, Bit_RESET);
}

//ham xoa man hinh
void LCD_clr()
{
	LCD_command(0x01);
	Delay_ms(5);
}

//ham dua lenh len lcd
static void LCD_command(uint8_t command)
{
	uint32_t temp;
	temp = 0;
	GPIO_Write(LCD_DATA_GPIO_PORT, 0);
	//LCD_rs = 0;
  GPIO_WriteBit(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, Bit_RESET);
  //P0 = (P0 & 0x0F)|((command) & 0xF0);
	temp = (GPIO_ReadOutputData(LCD_DATA_GPIO_PORT)&0x0FFF)|((command << 8)&0xF000);
	GPIO_Write(LCD_DATA_GPIO_PORT, (uint16_t)temp);
	// enable LCD
  LCD_enable();
  //P0 = (P0 & 0x0F)|(command<<4 & 0xF0);
	temp = (GPIO_ReadOutputData(LCD_DATA_GPIO_PORT)&0x0FFF)|((command << 12)&0xF000);
	GPIO_Write(LCD_DATA_GPIO_PORT, (uint16_t)temp);
	// enable LCD
  LCD_enable();
  Delay_ms(10);
}

//Ham viet ky tu len lcd
void LCD_putc(uint8_t ascii)
{
	uint32_t temp;
	GPIO_Write(LCD_DATA_GPIO_PORT, 0);
	temp = 0;
	//LCD_rs = 1;
	GPIO_WriteBit(LCD_RS_GPIO_PORT, LCD_RS_GPIO_PIN, Bit_SET);
  //P0 = (P0 & 0x0F)|((ascii) & 0xF0);
	temp = (GPIO_ReadOutputData(LCD_DATA_GPIO_PORT)&0x0FFF)|((ascii << 8)&0xF000);
	GPIO_Write(LCD_DATA_GPIO_PORT, (uint16_t)temp);
  LCD_enable();
  //P0 = (P0 & 0x0F)|(ascii<<4 & 0xF0);
	temp = (GPIO_ReadOutputData(LCD_DATA_GPIO_PORT)&0x0FFF)|((ascii << 12)&0xF000);
	GPIO_Write(LCD_DATA_GPIO_PORT, (uint16_t)temp);
	// enable LCD
  LCD_enable();
  Delay_ms(10);
}

//Ham viet xau ky tu len lcd
void LCD_puts(uint8_t *lcd_string)
{
	while (*lcd_string) 
	{
		LCD_putc(*lcd_string++);
	}
}


/**
  * @brief  writes a control command to the LCD.
  * @param  data: Specifies the control command to the LCD. 
  *   This parameter can be one of following parameters:
  *     @arg LCD_DD_RAM_PTR		: Address Display Data RAM pointer
  *     @arg LCD_CLEAR_DISPLAY		: Clear entire display and set Display Data Address to 0
  *     @arg LCD_RETRN_HOME		: sets DDRAM address 0 and returns display from being shifted to original position.
  *     @arg LCD_DISP_INIT			: 8 bit data length and 2 lines
  *     @arg LCD_INC_MODE			: Entry mode is display Data RAM pointer incremented after write
  *     @arg LCD_DISP_ON			: Sets entire display on, cursor on and blinking of cursor position character
  *     @arg LCD_DISP_OFF			: Sets entire display off, cursor off
  *     @arg LCD_CURSOR_ON		: turn on cursor
  *     @arg LCD_CURSOR_OFF		: turn off cursor
  *     @arg LCD_CUR_MOV_LEFT		: Cursor move and shift to left
  *     @arg LCD_CUR_MOV_RIGHT	: Cursor move and shift to right
  * @retval None
  */

/*
*************************************************************************************************************************************
*															GLOBAL FUNCTIONS														*
*************************************************************************************************************************************
*/
/**
  * @brief  	Initializes the LCD.
  * @param  	None
  * @retval 	None
  */
void lcd_Init(void)
{
	/* initialize hardware */
	lcd_Init_HW();

  LCD_command(0x28);  //dung 4 duong du lieu,hien thi 2 dong do phan giai 5x7
	Delay_ms(1);
  LCD_command(0x0C);  //che do hien thi ko gach chan,con tro ko nhap nhay 
	Delay_ms(1);
  LCD_command(0x06);
	Delay_ms(1);
//  LCD_command(0x01);   //Lenh xoa man hinh
	Delay_ms(1);
}

//Ham dat con tro LCD vao vi tri mong muon
void LCD_row(uint8_t hang,uint8_t cot)
{ 
  char hangcot=0;
	if(hang==1)
	{
		hangcot=0x80|cot;	
		LCD_command(hangcot);
	}
	if(hang==2)
	{
		hangcot=0xc0|cot;
		LCD_command(hangcot);
	}
}

//ham hien thi mot so  integer len lcd
void display_int(uint32_t number)
{
	int n1,n2,n3,n4,n22,n11;
	n1=number/1000;         //chia lay phan nguyen
	n11=number%1000;    //chhia lay phan du

	n2=n11/100;
	n22=n11%100;	

	n3=n22/10;

	n4=n22%10;

	if((n1==0)&&(n2==0)&&(n3==0))
	{
	//	LCD_putc(0+48);
	//	LCD_putc(0+48);
	//	LCD_putc(0+48);
		LCD_putc(n4+48);
	}
	else if((n1==0)&&(n2==0))
	{
	//	LCD_putc(0+48);
	//	LCD_putc(0+48);
		LCD_putc(n3+48);    //n3+48 la chuyen tu so n2 thanh ky tu so n2
		LCD_putc(n4+48);
	}
	else if(n1==0)
	{
	//	LCD_putc(0+48);
		LCD_putc(n2+48);
		LCD_putc(n3+48);
		LCD_putc(n4+48);
	}
	else
	{
		LCD_putc(n1+48);
		LCD_putc(n2+48);
		LCD_putc(n3+48);
		LCD_putc(n4+48);
	}

}

/******************* (C) COPYRIGHT 2010 ARMVietNam *****END OF FILE****/
