/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : LCD1.h
**     Project     : ProcessorExpert
**     Processor   : MKL25Z128VLK4
**     Component   : LCDHTA
**     Version     : Component 01.002, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2012-12-22, 22:18, # CodeGen: 35
**     Abstract    :
**          This component implements a driver for multiple 2x16 character displays.
**     Settings    :
**          Component name                                 : LCD1
**          HW Interface                                   : 
**            LCD Type                                     : generic
**            LCD Lines                                    : 2
**            LCD Enable Signal                            : Disabled
**            Read from Display                            : Enabled
**              R/W signal                                 : CtrlPin
**              Check Busy Flag                            : yes
**            Wait (us)                                    : 0
**            E signal                                     : CtrlPin
**            RS signal                                    : CtrlPin
**            Data/Control Bus                             : 
**              Data/Control Bus Width                     : 4bit
**              DB0..DB3                                   : Disabled
**              DB4..DB7                                   : Enabled
**                DB4                                      : DBpin
**                DB5                                      : DBpin
**                DB6                                      : DBpin
**                DB7                                      : DBpin
**              Bits/Byte Bus                              : Disabled
**          System Interface                               : 
**            Wait                                         : WAIT1
**     Contents    :
**         Write        - void LCD1_Write(char ch);
**         WriteLn      - void LCD1_WriteLn(void);
**         WriteLineStr - void LCD1_WriteLineStr(byte line, char *str);
**         WriteString  - void LCD1_WriteString(char *str);
**         ShiftLeft    - void LCD1_ShiftLeft(void);
**         ShiftRight   - void LCD1_ShiftRight(void);
**         GotoXY       - void LCD1_GotoXY(byte line, byte column);
**         SetEntryMode - void LCD1_SetEntryMode(bool increment, bool shiftLeft);
**         Home         - void LCD1_Home(void);
**         Line         - void LCD1_Line(byte line);
**         Clear        - void LCD1_Clear(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2012, all rights reserved.
**     http      : www.mcuoneclipse.com
**     This an open source software implementing software using Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/

#ifndef __LCD1_H
#define __LCD1_H

/* Include shared modules, which are used for whole project */
#include "stdint.h"
#include "stm32f10x_gpio.h"
/* Include inherited beans */
/* ID's for the soft characters which can be used as first argument for LCD1_LoadSoftChar().
  Note that ID's can start with zero, but if you want to use a zero byte in LCD1_WriteString()
  then this would be the zero delimiter byte, so not very useful. */
#define LCD1_SOFTCHAR_UE 1 /*<! ID for '�' */
#define LCD1_SOFTCHAR_AE 2 /*<! ID for '�' */
#define LCD1_SOFTCHAR_OE 3 /*<! ID for '�' */

/* support for custom soft characters in the display which can be used with LCD1_LoadSoftChar() */
extern const uint8_t LCD1_SoftCharUE[8]; /* � */
extern const uint8_t LCD1_SoftCharAE[8]; /* � */
extern const uint8_t LCD1_SoftCharOE[8]; /* � */

#define LCD1_MAX_LCD_LINE_CHARS 16 /* number of chars of the LCD on a line */

#define LCD_CLK     RCC_APB2Periph_GPIOB
#define LCD_PORT    GPIOB
#define LCD_RS  GPIO_Pin_10
#define LCD_EN  GPIO_Pin_11
#define LCD_D4  GPIO_Pin_12
#define LCD_D5  GPIO_Pin_13
#define LCD_D6  GPIO_Pin_14
#define LCD_D7  GPIO_Pin_15

void LCD1_WriteLCDData(uint8_t ch);
/*
** ===================================================================
**     Method      :  LCD1_WriteLCDData (component LCDHTA)
**
**     Description :
**         Writes data to the display
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void LCD1_Init(void);
/*
** ===================================================================
**     Method      :  LCD1_Init (component LCDHTA)
**
**     Description :
**         Display driver initialization routine.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

void LCD1_Clear(void);
/*
** ===================================================================
**     Method      :  LCD1_Clear (component LCDHTA)
**
**     Description :
**         Clears the display and moves the cursor to the first line.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_Home(void);
/*
** ===================================================================
**     Method      :  LCD1_Home (component LCDHTA)
**
**     Description :
**         Moves the cursor to the beginning of the first line.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_GotoXY(uint8_t line, uint8_t column);
/*
** ===================================================================
**     Method      :  LCD1_GotoXY (component LCDHTA)
**
**     Description :
**         Places the cursor on a specified position on the display.
**     Parameters  :
**         NAME            - DESCRIPTION
**         line            - Line number starting with 1
**         column          - Column number starting with 1
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_ShiftLeft(void);
/*
** ===================================================================
**     Method      :  LCD1_ShiftLeft (component LCDHTA)
**
**     Description :
**         Shifts all characters to the left.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#define LCD1_Write(ch)   LCD1_WriteLCDData((uint8_t)ch)
/*
** ===================================================================
**     Method      :  LCD1_Write (component LCDHTA)
**
**     Description :
**         Write a single character to the display
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - Character to write
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteLn(void);
/*
** ===================================================================
**     Method      :  LCD1_WriteLn (component LCDHTA)
**
**     Description :
**         Writes a new line to the display
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteString(char *str);
/*
** ===================================================================
**     Method      :  LCD1_WriteString (component LCDHTA)
**
**     Description :
**         Writes a string to the display at the current cursor
**         position.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * str             - Pointer to string (zero byte terminated)
**                           to write to the display
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_WriteLineStr(uint8_t line, char *str);
/*
** ===================================================================
**     Method      :  LCD1_WriteLineStr (component LCDHTA)
**
**     Description :
**         Writes a full line to the display (clears the rest of the
**         line).
**     Parameters  :
**         NAME            - DESCRIPTION
**         line            - Line number (starting with 1).
**       * str             - Pointer to the string which should be
**                           shown on the display.
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_Line(uint8_t line);
/*
** ===================================================================
**     Method      :  LCD1_Line (component LCDHTA)
**
**     Description :
**         Sets the current line.
**     Parameters  :
**         NAME            - DESCRIPTION
**         line            - Line number, starting with 1
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_ShiftRight(void);
/*
** ===================================================================
**     Method      :  LCD1_ShiftRight (component LCDHTA)
**
**     Description :
**         Shifts all characters to the right.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void LCD1_SetEntryMode(bool increment, bool shiftLeft);
/*
** ===================================================================
**     Method      :  LCD1_SetEntryMode (component LCDHTA)
**
**     Description :
**         Configures the display entry mode, if the cursor has to
**         shift and/or if the display shall shift content while
**         displaying text.
**     Parameters  :
**         NAME            - DESCRIPTION
**         increment       - Increments (TRUE) or
**                           decrements (FALSE) the display address by 1
**                           when a character code is written into or
**                           read from DDRAM. The cursor or blinking
**                           moves to the right when incremented by 1
**                           and to the left when decremented by 1.
**         shiftLeft       - The display does not shift if
**                           the 'shift' is FALSE. If 'shift' is TRUE,
**                           it will seem as if the cursor does not move
**                           but the display does.
**     Returns     : Nothing
** ===================================================================
*/

#endif
/* ifndef __LCD1_H */
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.0 [05.03]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/