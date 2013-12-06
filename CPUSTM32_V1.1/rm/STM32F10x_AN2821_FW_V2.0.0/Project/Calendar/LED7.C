#include <stdio.h>
#include "main.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_it.h"
extern GPIO_InitTypeDef GPIO_InitStructure;



void Innit_Timer2(void)
{

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 // TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM2 configuration */
  TIM_TimeBaseStructure.TIM_Period =2;            // 3 s = 0xE0F
  TIM_TimeBaseStructure.TIM_Prescaler = 16000;     // dem buoc 1  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;    
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);        

  
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
  

  /* Immediate load of TIM2 Precaler value */
//  TIM_PrescalerConfig(TIM2, 0xEA5F, TIM_PSCReloadMode_Immediate);

  

  /* Clear TIM2 update pending flag */
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);

  

  /* Enable TIM2 Update interrupt */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  


}


// ****** Low-level functions ******
// the following functions are the only ones which deal with the CPU
// memory or port pins directly.  If you decide to use a fundamentally
// different hardware interface to your LCD, only these functions need
// to be changed, after which all the high-level functions will
// work again.
void Write3_Bit(u8 data)
{
	// Write only the lowest 3 bits!
	GPIO_Write(GPIOB ,( GPIO_ReadOutputData(GPIOB ) & 0xFFF8 ) | (u8)data);
}


void Chon_Led(u8 vt)
{
	  switch (vt)
  	{
     		case 1:
		SELECT_A_L(); 		
		SELECT_B_L();
		SELECT_C_L();
        	break;
     		case 0:
		SELECT_A_H(); 		
		SELECT_B_L();
		SELECT_C_L();
        	break;
     		case 3:
		SELECT_A_L(); 		
		SELECT_B_H();
		SELECT_C_L();
        	break;
     		case 2:
		SELECT_A_H(); 				
		SELECT_B_H();
		SELECT_C_L();		
		break;	
     		case 5:
		SELECT_A_L(); 		
		SELECT_B_L();
		SELECT_C_H();
        	break;
		case 4:
		SELECT_A_H(); 		
		SELECT_B_L();
		SELECT_C_H();
        	break;				
	
	
     
  	}
 


}






void Init_LED(void)
{

	/* Configure LED 7 push-pull */
	GPIO_InitStructure.GPIO_Pin = SELECT_A | SELECT_B |  SELECT_C| LED_CK | LED_DATA|LED_LAUCH | LED_OE ;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 
	 OE_L();  

}


void Shift_1byte(u8 data)
{  
	u8  i,tmp;
	tmp=data;


		
	for(i=0;i<8;i++)
	{
		if (tmp & 0x80) DATA_H(); else  DATA_L();

		
		
		CK_H();
		CK_L();
		tmp=tmp<<1;
	
	}

	
	


}


u8 Dem_quet;
u8 LED[6];
u8 LED1[6];
u8 LED2[6];

const u8 Font[]={
				63,
				6,
				91,
				79,
				102,
				109,
				125,
				7,
				127,
				111,
				0,
				};

u8 Cham;
void QUET_LED(void)
{
	u8 tam;
	  OE_H();  
	  Chon_Led(Dem_quet);
	  //Dem_quet=5;
	  tam=Font[LED2[Dem_quet]];
	  if ((Timer_2_En==1)&&(Cham))tam=tam|0x80;
	  Shift_1byte(tam);

	  tam=Font[LED1[Dem_quet]];
	  if ((Timer_1_En==1)&&(Cham))tam=tam|0x80;
	  Shift_1byte(tam);  
	   tam=Font[LED[Dem_quet]];
	  if (Cham)tam=tam|0x80;
	  Shift_1byte(tam);  
	  LAUCH_L();
	  LAUCH_H();
	  OE_L(); 
	 if (Dem_quet<5)Dem_quet++;else Dem_quet=0;



}


u8 BCD[3];
void BCD_LED(u16  SO)
{
 unsigned long tmp;
 tmp=SO%1000;
 BCD[2]=tmp%1000/100;
 BCD[1]=tmp%100/10;
 BCD[0]=tmp%10/1;
 
}
