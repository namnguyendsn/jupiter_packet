#include <stdio.h>
#include "main.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_it.h"
#include "Led7.h"
#include "Clock.h"
#include "stm32f10x_rtc.h"

 extern u8 Chop;
 Clock Time_Now;
 Clock Time_Set;
 Clock Time_1;
 Clock Time_2;
 u32 TimeDisplay = 0;


u8 New_sec;
u32 Timer_Chop;


/**
  * @brief  Configures the RTC.
  * @param  None
  * @retval None
  */



void Write_u32_BKR(u16 dc,u32 data_w)
{
	u16 tmp;
	tmp=(u16)data_w>>16;
	BKP_WriteBackupRegister(dc, tmp);
	tmp=(u16)data_w&0xffff;
	BKP_WriteBackupRegister(dc+4, tmp);

}


u32 Read_u32_BKR(u16 dc)
{
	u16 tmp;
	u32 data;
	data=BKP_ReadBackupRegister(dc);
	data=data<<16;
	tmp=BKP_ReadBackupRegister(dc+4);
	data=data|tmp;
   return(data);
}



void Blink(u8 Vt)
{
	u8 t;
	t=Vt;	
	switch (t)
		{
		case 1:
			if (Chop==0xff)
			{
				BCD_LED(Time_Set.Hour);
				LED[0]=BCD[1];
				LED[1]=BCD[0];
			}
			else
			{
				LED[0]=10;
				LED[1]=10;
			}
			
			
		break;
		case 2:
			if (Chop==0xff)
			{
				BCD_LED(Time_Set.Min);
				LED[2]=BCD[1];
				LED[3]=BCD[0];
			}
			else
			{
				LED[2]=10;
				LED[3]=10;
			}
			
		break;
		case 3:
			if (Chop==0xff)
			{
				BCD_LED(Time_Set.Sec);
				LED[4]=BCD[1];
				LED[5]=BCD[0];
			}
			else
			{
				LED[4]=10;
				LED[5]=10;
			}	
		break;
		case 4:
			 if (Chop==0xff)
			{
				BCD_LED(Time_1.Hour);
				LED1[0]=BCD[1];
				LED1[1]=BCD[0];
			}
			else
			{
				LED1[0]=10;
				LED1[1]=10;
			}	
		break;				

		case 5:
			 if (Chop==0xff)
			{
				BCD_LED(Time_1.Min);
				LED1[2]=BCD[1];
				LED1[3]=BCD[0];
			}
			else
			{
				LED1[2]=10;
				LED1[3]=10;
			}	
		break;				
		case 6:
			 if (Chop==0xff)
			{
				BCD_LED(Time_1.Sec);
				LED1[4]=BCD[1];
				LED1[5]=BCD[0];
			}
			else
			{
				LED1[4]=10;
				LED1[5]=10;
			}	
		break;				
		case 7:
			 if (Chop==0xff)
			{
				BCD_LED(Time_2.Hour);
				LED2[0]=BCD[1];
				LED2[1]=BCD[0];
			}
			else
			{
				LED2[0]=10;
				LED2[1]=10;
			}	
		break;				

		case 8:
			 if (Chop==0xff)
			{
				BCD_LED(Time_2.Min);
				LED2[2]=BCD[1];
				LED2[3]=BCD[0];
			}
			else
			{
				LED2[2]=10;
				LED2[3]=10;
			}	
		break;				
		case 9:
			 if (Chop==0xff)
			{
				BCD_LED(Time_2.Sec);
				LED2[4]=BCD[1];
				LED2[5]=BCD[0];
			}
			else
			{
				LED2[4]=10;
				LED2[5]=10;
			}	
		break;			

				
				
		}


}
 u8 Menu_Count;
 
 u8 Clock_Chage;
  u8 Timer_Chage;
    u8 New_Press;


void UP_DOWN_PRESSED(void)
{
			if ((Up==Bit_RESET) || (Down==Bit_RESET))New_Press=1;

				switch (Menu_Count)
				{
				case 1:
					if (Up==Bit_RESET)
					{
						if (Time_Set.Hour<23) Time_Set.Hour++; else Time_Set.Hour=0;
						Clock_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_Set.Hour>0) Time_Set.Hour--; else Time_Set.Hour=23;
						Clock_Chage=1;
					}
					
				break;
				case 2:
					if (Up==Bit_RESET)
					{
						if (Time_Set.Min<59) Time_Set.Min++; else Time_Set.Min=0;
						Clock_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_Set.Min>0) Time_Set.Min--; else Time_Set.Min=59;
						Clock_Chage=1;
					}
					
				break;
				case 3:
					if (Up==Bit_RESET)
					{
						if (Time_Set.Sec<59) Time_Set.Sec++; else Time_Set.Sec=0;
						Clock_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_Set.Sec>0) Time_Set.Sec--; else Time_Set.Sec=59;
						Clock_Chage=1;
					}
				
						
				break;
				case 4:
					if (Up==Bit_RESET)
					{
						if (Time_1.Hour<23) Time_1.Hour++; else Time_1.Hour=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_1.Hour>0) Time_1.Hour--; else Time_1.Hour=23;
						Timer_Chage=1;
					}
					
				break;
				case 5:
					if (Up==Bit_RESET)
					{
						if (Time_1.Min<59) Time_1.Min++; else Time_1.Min=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_1.Min>0) Time_1.Min--; else Time_1.Min=59;
						Timer_Chage=1;
					}
					
				break;
				case 6:
					if (Up==Bit_RESET)
					{
						if (Time_1.Sec<59) Time_1.Sec++; else Time_1.Sec=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_1.Sec>0) Time_1.Sec--; else Time_1.Sec=59;
						Timer_Chage=1;
					}
				
						
				break;
				case 7:
					if (Up==Bit_RESET)
					{
						if (Time_2.Hour<23) Time_2.Hour++; else Time_2.Hour=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_2.Hour>0) Time_2.Hour--; else Time_2.Hour=23;
						Timer_Chage=1;
					}
					
				break;
				case 8:
					if (Up==Bit_RESET)
					{
						if (Time_2.Min<59) Time_2.Min++; else Time_2.Min=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_2.Min>0) Time_2.Min--; else Time_2.Min=59;
						Timer_Chage=1;
					}
					
				break;
				case 9:
					if (Up==Bit_RESET)
					{
						if (Time_2.Sec<59) Time_2.Sec++; else Time_2.Sec=0;
						Timer_Chage=1;
					}
					if (Down==Bit_RESET)
					{
						if (Time_2.Sec>0) Time_2.Sec--; else Time_2.Sec=59;
						Timer_Chage=1;
					}
				
						
				break;
				
				case 10:
					
					Menu_Count=0;// thoat
				break;					
				
				}

}

 extern u16 Timer_Key;

void Set_Clock(void)
{
		//u8 Da_Set=0;
				
				Time_Set.Hour=Time_Now.Hour;
				Time_Set.Min=Time_Now.Min;
				Time_Set.Sec=Time_Now.Sec;
			   	Menu_Count=0;
				Chop=0xff;
				Menu_Count++;


			 while (Menu_Count!=0)
			 {

				if (Menu_Count>3)
				{
				 if(Clock_Chage)
				 	{
				 	Clock_Chage=0;
				 	SetTime(Time_Set.Hour,Time_Set.Min,Time_Set.Sec);
				 	}
				CalculateTime();
				Time_Set.Hour=Time_Now.Hour;
				Time_Set.Min=Time_Now.Min;
				Time_Set.Sec=Time_Now.Sec;
				BCD_LED(Time_Set.Hour);
				LED[0]=BCD[1];
				LED[1]=BCD[0];
				BCD_LED(Time_Set.Min);
				LED[2]=BCD[1];
				LED[3]=BCD[0];
				BCD_LED(Time_Set.Sec);
				LED[4]=BCD[1];
				LED[5]=BCD[0];
				if (Time_Now.Sec!=New_sec)
				{
					New_sec=Time_Now.Sec;
					Cham=1;
					Timer_Chop=220;
				}
					

				}
				
			 
			 	while(Seting== Bit_RESET)
			 		{
			 			Blink(Menu_Count);
			 		}
				
			
			  	if(Move== Bit_RESET)
				{
					Menu_Count++;
					BCD_LED(Time_Set.Hour);
					LED[0]=BCD[1];
					LED[1]=BCD[0];
					BCD_LED(Time_Set.Min);
					LED[2]=BCD[1];
					LED[3]=BCD[0];
					BCD_LED(Time_Set.Sec);
					LED[4]=BCD[1];
					LED[5]=BCD[0];
					Timer_Display();																
					
					Delay_MS(100);	 
					 while(Move== Bit_RESET)
			 		{
			 			Blink(Menu_Count);
			 		}
					Delay_MS(100);	 
				}

					Blink(Menu_Count);

					

			
				  UP_DOWN_PRESSED();

				if(New_Press==1)
				{
			   		
					BCD_LED(Time_Set.Hour);
					LED[0]=BCD[1];
					LED[1]=BCD[0];
					BCD_LED(Time_Set.Min);
					LED[2]=BCD[1];
					LED[3]=BCD[0];
					BCD_LED(Time_Set.Sec);
					LED[4]=BCD[1];
					LED[5]=BCD[0];
					Timer_Display();
					New_Press=0;

					
					Timer_Key=800; // nhan giu 1 s
					Delay_MS(100);	
					while(((Up==Bit_RESET)||(Down==Bit_RESET))&&(Timer_Key>0))
					{
						Blink(Menu_Count);
					}
					while((Up==Bit_RESET)||(Down==Bit_RESET))
					{
								UP_DOWN_PRESSED();
			   					BCD_LED(Time_Set.Hour);
								LED[0]=BCD[1];
								LED[1]=BCD[0];
								BCD_LED(Time_Set.Min);
								LED[2]=BCD[1];
								LED[3]=BCD[0];
								BCD_LED(Time_Set.Sec);
								LED[4]=BCD[1];
								LED[5]=BCD[0];
								Timer_Display();																
								Delay_MS(200);	

							  
					}
			 	}
				
			 }
			 
			
			 
			 if (Timer_Chage)
			 {
				Timer_1_Count=Time_1.Hour*3600 + Time_1.Min*60 + Time_1.Sec;
				Timer_2_Count=Time_2.Hour*3600 + Time_2.Min*60 + Time_2.Sec;
				Write_u32_BKR(BKP_DR2,Timer_1_Count);
				Write_u32_BKR(BKP_DR4,Timer_2_Count);
			
			Timer_Chage=0;
			}

			 

}



u8 New_Key;
void Menu(void)
{
  
		if(Seting==Bit_RESET)
		{
			Delay_MS(100);	 
			if(Seting== Bit_RESET)
			{
			 Set_Clock();
		
		 	 }	
		  	
		}

		if ((Start1==Bit_SET)&&(Start2==Bit_SET)&&(Stop1==Bit_SET)&&(Stop2==Bit_SET))  New_Key=1;
		
		if ((Start1==Bit_RESET)&&(New_Key==1))
		{
			Delay_MS(100);	
			if (Start1==Bit_RESET)
			{
				if (Timer_1_En==1) Timer_1_En=0; else Timer_1_En=1;
				New_Key=0;
				Delay_MS(200);
			}
				
		}

		if ((Stop1==Bit_RESET)&&(New_Key==1))
		{
			Delay_MS(100);	
			if (Stop1==Bit_RESET)
			{
			if (Timer_1_En==1) Timer_1_En=0; else Timer_1_Count=0;
			New_Key=0;
			Delay_MS(200);
			}
			
				
		}


		if ((Start2==Bit_RESET)&&(New_Key==1))
		{
			Delay_MS(100);	
			if (Start2==Bit_RESET)
			{
				if (Timer_2_En==1) Timer_2_En=0; else Timer_2_En=1;
				New_Key=0;
				Delay_MS(200);
			}
				
		}

		if ((Stop2==Bit_RESET)&&(New_Key==1))
		{
			Delay_MS(100);	
			if (Stop2==Bit_RESET)
			{
			if (Timer_2_En==1) Timer_2_En=0; else Timer_2_Count=0;
			New_Key=0;
			Delay_MS(200);
			}
			
				
		}


//		if (Start2==Bit_RESET)
//		{
//			if (Timer_2_En==1) Timer_2_En=0; else Timer_2_En=1;
//			while (Start2==Bit_RESET)
//			{
//			
//			}
//				
//		}
		
		

}



void RTC_Configuration(void)
{

	uint16_t WaitForOscSource;

	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Reset Backup Domain */
	BKP_DeInit();

	
    /*Enable 32.768 kHz external oscillator */
    RCC_LSEConfig(RCC_LSE_ON);
  
    for(WaitForOscSource=0;WaitForOscSource<5000;WaitForOscSource++)
    {
    }

	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}


void RTC_Re_Configuration(void)
{


	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);

	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();

	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);

	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();


}

/**
  * @brief Chaeks is counter value is more than 86399 and the number of
  *   elapsed and updates date that many times
  * @param None
  * @retval :None
  */
void CheckForDaysElapsed(void)
{
  uint8_t DaysElapsed;
 
  if((RTC_GetCounter() / SECONDS_IN_DAY) != 0)
  {
    for(DaysElapsed = 0; DaysElapsed < (RTC_GetCounter() / SECONDS_IN_DAY)\
         ;DaysElapsed++)
   

    RTC_SetCounter(RTC_GetCounter() % SECONDS_IN_DAY);
  }
}

void CalculateTime(void)
{
  uint32_t TimeVar;
  
  TimeVar=RTC_GetCounter();
  TimeVar=TimeVar % 86400;
  Time_Now.Hour=(uint8_t)(TimeVar/3600);
  Time_Now.Min=(uint8_t)((TimeVar%3600)/60);
  Time_Now.Sec=(uint8_t)((TimeVar%3600)%60);

}


 /**
  * @brief  Sets the RTC Current Counter Value
  * @param Hour, Minute and Seconds data
  * @retval : None
  */
void SetTime(uint8_t Hour,uint8_t Minute,uint8_t Seconds)
{
  uint32_t CounterValue;

  CounterValue=((Hour * 3600)+ (Minute * 60)+Seconds);

 	// RTC_WaitForLastTask();
 	 RTC_SetCounter(CounterValue);
  	 RTC_WaitForLastTask();
}



/**
  * @brief  Returns the time entered by user, using Hyperterminal.
  * @param  None
  * @retval Current time RTC counter value
  */
uint32_t Time_Regulate(void)
{
	uint32_t Tmp_HH = 0xFF, Tmp_MM = 0xFF, Tmp_SS = 0xFF;

	printf("\r\n==============Time Settings=====================================");
	printf("\r\n  Please Set Hours");

	while (Tmp_HH == 0xFF)
	{
		Tmp_HH = USART_Scanf(23);
	}
	printf(":  %d", Tmp_HH);
	printf("\r\n  Please Set Minutes");
	while (Tmp_MM == 0xFF)
	{
		Tmp_MM = USART_Scanf(59);
	}
	printf(":  %d", Tmp_MM);
	printf("\r\n  Please Set Seconds");
	while (Tmp_SS == 0xFF)
	{
		Tmp_SS = USART_Scanf(59);
	}
	printf(":  %d", Tmp_SS);

	/* Return the value to store in RTC counter register */
	return((Tmp_HH*3600 + Tmp_MM*60 + Tmp_SS));
}




/**
  * @brief  Adjusts time.
  * @param  None
  * @retval None
  */
void Time_Adjust(void)
{
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Change the current time */
	RTC_SetCounter(Time_Regulate());
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}




void Timer_Display(void)
{
	BCD_LED(Time_1.Hour);
	//	if (BCD[1]==0)LED1[0]=10;else
	LED1[0]=BCD[1];
	LED1[1]=BCD[0];
	BCD_LED(Time_1.Min);
	LED1[2]=BCD[1];
	LED1[3]=BCD[0];
	BCD_LED(Time_1.Sec);
	LED1[4]=BCD[1];
	LED1[5]=BCD[0];


	BCD_LED(Time_2.Hour);
	//if (BCD[1]==0)LED2[0]=10;else 
	LED2[0]=BCD[1];
	LED2[1]=BCD[0];
	BCD_LED(Time_2.Min);
	LED2[2]=BCD[1];
	LED2[3]=BCD[0];
	BCD_LED(Time_2.Sec);
	LED2[4]=BCD[1];
	LED2[5]=BCD[0];


}




void Time_Display(uint32_t TimeVar)
{
	CalculateTime();

	if (Time_Now.Sec!=New_sec)
		{
			New_sec=Time_Now.Sec;
			Cham=1;
			Timer_Chop=220;
			if ((Timer_1_En==1)||(Timer_2_En==1))
			{

			Write_u32_BKR(BKP_DR2,Timer_1_Count);
			Write_u32_BKR(BKP_DR4,Timer_2_Count);
			}

		
		}
	
	
	BCD_LED(Time_Now.Hour);
	if (BCD[1]==0)LED[0]=10;else LED[0]=BCD[1];
	
	LED[1]=BCD[0];
	BCD_LED(Time_Now.Min);
	LED[2]=BCD[1];
	LED[3]=BCD[0];
	BCD_LED(Time_Now.Sec);
	LED[4]=BCD[1];
	LED[5]=BCD[0];

	printf("Time: %0.2d:%0.2d:%0.2d\r", Time_Now.Hour,Time_Now.Min,Time_Now.Sec);
	RTC_WaitForLastTask();

	Time_1.Hour=(uint8_t)(Timer_1_Count/3600);
  	Time_1.Min=(uint8_t)((Timer_1_Count%3600)/60);
  	Time_1.Sec=(uint8_t)((Timer_1_Count%3600)%60);
	Time_2.Hour=(uint8_t)(Timer_2_Count/3600);
  	Time_2.Min=(uint8_t)((Timer_2_Count%3600)/60);
  	Time_2.Sec=(uint8_t)((Timer_2_Count%3600)%60);
	
	
	
	Timer_Display();


	

	
	
		
	
}

void Time_Show(void)
{
	
	
		/* If 1s has paased */
		if (TimeDisplay == 1)
		{
			/* Display current time */
			Time_Display(RTC_GetCounter());
			TimeDisplay = 0;		
			
		}

	
}
