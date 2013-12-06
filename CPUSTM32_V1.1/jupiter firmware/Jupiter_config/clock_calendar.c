/**
  ******************************************************************************
  * @file RTC/src/clock_calendar.c 
  * @author  MCD Application Team
  * @version  V2.0.0
  * @date  04/27/2009
  * @brief  Clock Calendar basic routines
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
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 


/* Includes ------------------------------------------------------------------*/
#include "JupiterV1_1.h"

/* Private variables--------------------------------------------------------- */
uint8_t ClockSource;
uint8_t *MonthsNames[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug",\
"Sep","Oct","Nov","Dec"};
const uint8_t CalibrationPpm[128]={0,1,2,3,4,5,6,7,8,9,10,10,11,12,13,14,15,16,17,\
                         18,19,20,21,22,23,24,25,26,27,28,29,30,31,31,32,33,34,\
                         35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,51,\
                         52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,\
                         70,71,72,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,\
                         87,88,89,90,91,92,93,93,94,95,96,97,98,99,100,101,102,\
                         103,104,105,106,107,108,109,110,111,112,113,113,114,\
                         115,116,117,118,119,120,121};
/*Structure variable declaration for system time, system date,
alarm time, alarm date */
struct Time_s s_TimeStructVar;
struct AlarmTime_s s_AlarmStructVar;
struct Date_s s_DateStructVar;
struct AlarmDate_s s_AlarmDateStructVar;
uint8_t AlarmDate=0;
uint32_t Dummy;
uint8_t TamperNumber; /* Keeps the number of tamper Events already happened */

/** @addtogroup RTC
  * @{
  */ 


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  COnfiguration of RTC Registers, Selection and Enabling of 
  *   RTC clock
  * @param  None
  * @retval : None
  */
void RTC_Configuration()
{
  uint16_t WaitForOscSource;
  
  /*Allow access to Backup Registers*/
  PWR_BackupAccessCmd(ENABLE);
  
  if(BKP_ReadBackupRegister(BKP_DR1)==CONFIGURATION_RESET)
  {
    /*Enables the clock to Backup and power interface peripherals    */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

		/* Backup Domain Reset */
		BKP_DeInit();
		s_DateStructVar.Month=DEFAULT_MONTH ;
		s_DateStructVar.Day=DEFAULT_DAY;
		s_DateStructVar.Year=DEFAULT_YEAR;
		//SummerTimeCorrect = OCTOBER_FLAG_SET;
		//BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
		BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
		BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
		BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
		BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
		//format flash
		//TamperNumber=0;
		//BKP_WriteBackupRegister(BKP_DR5,TamperNumber);

    /*Enable 32.768 kHz external oscillator */
    RCC_LSEConfig(RCC_LSE_ON);
  
    for(WaitForOscSource=0;WaitForOscSource<5000;WaitForOscSource++)
    {
    }

    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    /* RTC Enabled */
    RCC_RTCCLKCmd(ENABLE);
    RTC_WaitForLastTask();
    /*Wait for RTC registers synchronisation */
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    /* Setting RTC Interrupts-Seconds interrupt enabled */
    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC , ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR6, 1);

		/* Set RTC prescaler: set RTC period to 1 sec */
		RTC_SetPrescaler(32765); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
		/* Prescaler is set to 32766 instead of 32768 to compensate for
			lower as well as higher frequencies*/
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();

		BKP_WriteBackupRegister(BKP_DR6, 2);
		/* Set RTC prescaler: set RTC period to 1 sec */
		RTC_SetPrescaler(49); /* RTC period = RTCCLK/RTC_PR = (50 Hz)/(49+1) */
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();


		BKP_WriteBackupRegister(BKP_DR6, 3);
		/* Set RTC prescaler: set RTC period to 1 sec */
		RTC_SetPrescaler(59); /* RTC period = RTCCLK/RTC_PR = (60 Hz)/(59+1) */
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();

    /* Set default system time to 09 : 24 : 00 */
    SetTime(DEFAULT_HOURS,DEFAULT_MINUTES,DEFAULT_SECONDS);
    BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
  }
  else
  {
    /* PWR and BKP clocks selection */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    for(WaitForOscSource=0;WaitForOscSource<5000;WaitForOscSource++);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    RTC_WaitForLastTask();
  }
    
  /* Check if how many days are elapsed in power down/Low Power Mode-
   Updates Date that many Times*/
  CheckForDaysElapsed();
  ClockSource = BKP_ReadBackupRegister(BKP_DR6);
  //TamperNumber = BKP_ReadBackupRegister(BKP_DR5);
  s_DateStructVar.Month = BKP_ReadBackupRegister(BKP_DR2);
  s_DateStructVar.Day = BKP_ReadBackupRegister(BKP_DR3);
  s_DateStructVar.Year = BKP_ReadBackupRegister(BKP_DR4);
  //SummerTimeCorrect = BKP_ReadBackupRegister(BKP_DR7);
  s_AlarmDateStructVar.Month = BKP_ReadBackupRegister(BKP_DR8);
  s_AlarmDateStructVar.Day = BKP_ReadBackupRegister(BKP_DR9);
  s_AlarmDateStructVar.Year = BKP_ReadBackupRegister(BKP_DR10);
}

/**
  * @brief  Apllication Initialisation Routine
  * @param  None
  * @retval : None
  */
void ApplicationInit(void)
{
  /* Unlock the Flash Program Erase controller */
  FLASH_Unlock();
  /*RTC_NVIC Configuration */
  RTC_NVIC_Configuration();
  
  /* RTC Configuration*/
  RTC_Configuration();
  BKP_RTCOutputConfig(BKP_RTCOutputSource_None);

  /* Tamper pin NVIC Configuration  */
  Tamper_NVIC_Configuration();

  /* Tamper FeatureRTC  -   Enable Tamper Interrupt and configure for Low level */
  BKP_ITConfig(ENABLE);

  /* Enable Tamper Pin for Active low level: Tamper level detected for low level*/
  BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low);

  /* Enable tamper Pin Interrupt */
  BKP_TamperPinCmd(ENABLE);

  /*  Menu Initialisation  */
  //MenuInit();
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

  RTC_WaitForLastTask();
  RTC_SetCounter(CounterValue);
  RTC_WaitForLastTask();
}



/**
  * @brief  Sets the RTC Alarm Register Value
  * @param Hours, Minutes and Seconds data
  * @retval : None
  */
void SetAlarm(uint8_t Hour,uint8_t Minute, uint8_t Seconds)
{
  uint32_t CounterValue;
  
  CounterValue=((Hour * 3600)+ (Minute * 60)+Seconds);
  
  if(CounterValue == 0)
  {
    CounterValue = SECONDS_IN_DAY;
  }

  RTC_WaitForLastTask();
  RTC_SetAlarm(CounterValue);
  RTC_WaitForLastTask();
}



/**
  * @brief  Sets the RTC Date(DD/MM/YYYY)
  * @param DD,MM,YYYY
  * @retval : None
  */
void SetDate(uint8_t Day, uint8_t Month, uint16_t Year)
{
  uint32_t DateTimer;
  
  //RightLeftIntExtOnOffConfig(DISABLE);
  //UpDownIntOnOffConfig(DISABLE);

  /*Check if the date entered by the user is correct or not, Displays an error
    message if date is incorrect  */
  if((( Month==4 || Month==6 || Month==9 || Month==11) && Day ==31) \
    || (Month==2 && Day==31)|| (Month==2 && Day==30)|| \
      (Month==2 && Day==29 && (CheckLeap(Year)==0)))
  {
    DateTimer=RTC_GetCounter();

		while((RTC_GetCounter()-DateTimer)<2)
		{
		}
  }
  /* if date entered is correct then set the date*/
  else
  {
    if(AlarmDate==0)
    {
      BKP_WriteBackupRegister(BKP_DR2,Month);
      BKP_WriteBackupRegister(BKP_DR3,Day);
      BKP_WriteBackupRegister(BKP_DR4,Year);
    }
    else
    {
     s_AlarmDateStructVar.Day = Day;
     s_AlarmDateStructVar.Month = Month;
     s_AlarmDateStructVar.Year = Year;
     BKP_WriteBackupRegister(BKP_DR8,Month);
     BKP_WriteBackupRegister(BKP_DR9,Day);
     BKP_WriteBackupRegister(BKP_DR10,Year);
     AlarmDate=0;
    }
  }
}



/**
  * @brief  RTC Application runs in while loop
  * @param  None
  * @retval : None
  */
void RTC_Application(void)
{
  uint8_t ReturnValue;

  CalculateTime();
  
  //if(TimeDateDisplay==0)
  {
    DisplayTime();
  }

  //if(DisplayDateFlag==1 && TimeDateDisplay==0)
  {
    //DisplayDate();
  }

  //if(AlarmStatus==1)
  {
    DisplayAlarm();
    Dummy=RTC_GetCounter();
    //AlarmStatus=2;
  }

  //if(TamperEvent == 1) /* Tamper event is detected */
  {
    TamperNumber = TamperNumber + 1;
    //BKP_WriteBackupRegister(BKP_DR5,TamperNumber);
    BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
    BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
    BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
    BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
    BKP_WriteBackupRegister(BKP_DR9,s_AlarmDateStructVar.Day);
    BKP_WriteBackupRegister(BKP_DR8,s_AlarmDateStructVar.Month);
    BKP_WriteBackupRegister(BKP_DR10,s_AlarmDateStructVar.Year);
    BKP_WriteBackupRegister(BKP_DR6,ClockSource);
    //BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
    //ReturnValue=EE_WriteVariable(TamperNumber);
    
    //ReturnValue=EE_WriteVariable(s_DateStructVar.Day);
    //ReturnValue=EE_WriteVariable(s_DateStructVar.Month);
    //ReturnValue=EE_WriteVariable((s_DateStructVar.Year)/100);
    //ReturnValue=EE_WriteVariable((s_DateStructVar.Year)%100);
    //ReturnValue=EE_WriteVariable((s_TimeStructVar.HourHigh*10)+\
                    s_TimeStructVar.HourLow);
    //ReturnValue=EE_WriteVariable((s_TimeStructVar.MinHigh*10)+\
                    s_TimeStructVar.MinLow);
    //ReturnValue=EE_WriteVariable((s_TimeStructVar.SecHigh*10)+\
                    s_TimeStructVar.SecLow);
    
    //TamperEvent=0;
    //BKP_TamperPinCmd(ENABLE);
  }
}

/**
  * @brief Updates the Date (This function is called when 1 Day has elapsed
  * @param None
  * @retval :None
  */
void DateUpdate(void)
{
  s_DateStructVar.Month=BKP_ReadBackupRegister(BKP_DR2);
  s_DateStructVar.Year=BKP_ReadBackupRegister(BKP_DR4);
  s_DateStructVar.Day=BKP_ReadBackupRegister(BKP_DR3);
  
  if(s_DateStructVar.Month == 1 || s_DateStructVar.Month == 3 || \
    s_DateStructVar.Month == 5 || s_DateStructVar.Month == 7 ||\
     s_DateStructVar.Month == 8 || s_DateStructVar.Month == 10 \
       || s_DateStructVar.Month == 12)
  {
    if(s_DateStructVar.Day < 31)
    {
      s_DateStructVar.Day++;
    }
    /* Date structure member: s_DateStructVar.Day = 31 */
    else
    {
      if(s_DateStructVar.Month != 12)
      {
        s_DateStructVar.Month++;
        s_DateStructVar.Day = 1;
      }
     /* Date structure member: s_DateStructVar.Day = 31 & s_DateStructVar.Month =12 */
      else
      {
        s_DateStructVar.Month = 1;
        s_DateStructVar.Day = 1;
        s_DateStructVar.Year++;
      }
    }
  }
  else if(s_DateStructVar.Month == 4 || s_DateStructVar.Month == 6 \
            || s_DateStructVar.Month == 9 ||s_DateStructVar.Month == 11)
  {
    if(s_DateStructVar.Day < 30)
    {
      s_DateStructVar.Day++;
    }
    /* Date structure member: s_DateStructVar.Day = 30 */
    else
    {
      s_DateStructVar.Month++;
      s_DateStructVar.Day = 1;
    }
  }
  else if(s_DateStructVar.Month == 2)
  {
    if(s_DateStructVar.Day < 28)
    {
      s_DateStructVar.Day++;
    }
    else if(s_DateStructVar.Day == 28)
    {
      /* Leap Year Correction */
      if(CheckLeap(s_DateStructVar.Year))
      {
        s_DateStructVar.Day++;
      }
      else
      {
        s_DateStructVar.Month++;
        s_DateStructVar.Day = 1;
      }
    }
    else if(s_DateStructVar.Day == 29)
    {
      s_DateStructVar.Month++;
      s_DateStructVar.Day = 1;
    }
  }
  
  BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
  BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
  BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
  //DisplayDateFlag=1;
}



/**
  * @brief  Checks whether the passed year is Leap or not.
  * @param  None
  * @retval : 1: leap year
  *   0: not leap year
  */
uint8_t CheckLeap(uint16_t Year)
{
  if((Year%400)==0)
  {
    return LEAP;
  }
  else if((Year%100)==0)
  {
    return NOT_LEAP;
  }
  else if((Year%4)==0)
  {
    return LEAP;
  }
  else
  {
    return NOT_LEAP;
  }
}



/**
  * @brief Determines the weekday
  * @param Year,Month and Day
  * @retval :Returns the CurrentWeekDay Number 0- Sunday 6- Saturday
  */
uint16_t WeekDay(uint16_t CurrentYear,uint8_t CurrentMonth,uint8_t CurrentDay)
{
  uint16_t Temp1,Temp2,Temp3,Temp4,CurrentWeekDay;
  
  if(CurrentMonth < 3)
  {
    CurrentMonth=CurrentMonth + 12;
    CurrentYear=CurrentYear-1;
  }
  
  Temp1=(6*(CurrentMonth + 1))/10;
  Temp2=CurrentYear/4;
  Temp3=CurrentYear/100;
  Temp4=CurrentYear/400;
  CurrentWeekDay=CurrentDay + (2 * CurrentMonth) + Temp1 \
     + CurrentYear + Temp2 - Temp3 + Temp4 +1;
  CurrentWeekDay = CurrentWeekDay % 7;
  
  return(CurrentWeekDay);
}



/**
  * @brief Displays the Date(DD/MM/YY and DAY ) on LCD
  * @param None
  * @retval :None
  */
//void DisplayDate(void)
//{
//  s_DateStructVar.Year=(BKP_ReadBackupRegister(BKP_DR4));
//  s_DateStructVar.Month=(BKP_ReadBackupRegister(BKP_DR2));
//  s_DateStructVar.Day=(BKP_ReadBackupRegister(BKP_DR3));
//  LCD_DisplayChar(Line5,Column5,(s_DateStructVar.Day/10) + 0x30);
//  LCD_DisplayChar(Line5,Column6,(s_DateStructVar.Day%10) + 0x30);
//  LCD_DisplayString(Line5,Column8,MonthsNames[s_DateStructVar.Month-1]);
//  LCD_DisplayChar(Line5,Column12,((s_DateStructVar.Year/1000) + 0x30));
//  LCD_DisplayChar(Line5,Column13,((s_DateStructVar.Year/100)%10) + 0x30);
//  LCD_DisplayChar(Line5,Column14,((s_DateStructVar.Year/10)%10) + 0x30);
//  LCD_DisplayChar(Line5,Column15,(s_DateStructVar.Year%10) + 0x30);
//  
//  switch(WeekDay(s_DateStructVar.Year,s_DateStructVar.Month,s_DateStructVar.Day))
//  {
//    case 0: LCD_DisplayString(Line6,Column8,"Sun");
//            break;
//    case 1: LCD_DisplayString(Line6,Column8,"Mon");
//            break;
//    case 2: LCD_DisplayString(Line6,Column8,"Tue");
//            break;
//    case 3: LCD_DisplayString(Line6,Column8,"Wed");
//            break;
//    case 4: LCD_DisplayString(Line6,Column8,"Thu");
//            break;
//    case 5: LCD_DisplayString(Line6,Column8,"Fri");
//            break;
//    case 6: LCD_DisplayString(Line6,Column8,"Sat");
//            break;
//  }
//}



/**
  * @brief Displays the Time on LCD
  * @param None
  * @retval :None
  */
void DisplayTime(void)
{
//  LCD_DisplayChar(Line4,Column6,s_TimeStructVar.HourHigh + 0x30);
//  LCD_DisplayChar(Line4,Column7,s_TimeStructVar.HourLow + 0x30);
//  LCD_DisplayChar(Line4,Column9,s_TimeStructVar.MinHigh + 0x30);
//  LCD_DisplayChar(Line4,Column10,s_TimeStructVar.MinLow + 0x30);
//  LCD_DisplayChar(Line4,Column12,s_TimeStructVar.SecHigh + 0x30);
//  LCD_DisplayChar(Line4,Column13,s_TimeStructVar.SecLow + 0x30);
}



/**
  * @brief  Displays Alarm on TFT LCD
  * @param  None
  * @retval : None
  */
void DisplayAlarm(void)
{
//  SelIntExtOnOffConfig(DISABLE);
//  RightLeftIntExtOnOffConfig(DISABLE);
//  UpDownIntOnOffConfig(DISABLE);
//  TimeDateDisplay=1;
//  LCD_Clear(Red);
//  LCD_SetTextColor(Yellow);
//  LCD_SetBackColor(Red);
//  LCD_DisplayString(Line4,Column8,"ALARM");
}



/**
  * @brief Calcuate the Time (in hours, minutes and seconds  derived from
  *   COunter value
  * @param None
  * @retval :None
  */
void CalculateTime(void)
{
  uint32_t TimeVar;
  
  TimeVar=RTC_GetCounter();
  TimeVar=TimeVar % 86400;
  s_TimeStructVar.HourHigh=(uint8_t)(TimeVar/3600)/10;
  s_TimeStructVar.HourLow=(uint8_t)(TimeVar/3600)%10;
  s_TimeStructVar.MinHigh=(uint8_t)((TimeVar%3600)/60)/10;
  s_TimeStructVar.MinLow=(uint8_t)((TimeVar%3600)/60)%10;
  s_TimeStructVar.SecHigh=(uint8_t)((TimeVar%3600)%60)/10;
  s_TimeStructVar.SecLow=(uint8_t)((TimeVar %3600)%60)%10;
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
    {
      DateUpdate();
    }

    RTC_SetCounter(RTC_GetCounter() % SECONDS_IN_DAY);
  }
}



/**
  * @brief  Calibration of External crystal oscillator manually
  * @param  None
  * @retval : None
  */
void ManualClockCalibration(void)
{
  //UpDownIntOnOffConfig(ENABLE);
  //RightLeftIntExtOnOffConfig(ENABLE);
  //SelIntExtOnOffConfig(DISABLE);

  BKP_TamperPinCmd(DISABLE);
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);

  BKP_RTCOutputConfig(BKP_RTCOutputSource_None);
//  SelIntExtOnOffConfig(ENABLE);
}



/**
  * @brief  Calibration of External crystal oscillator auto(through Timer
  *   
  * @param  None
  * @retval : None
  */
void AutoClockCalibration(void)
{
  RCC_ClocksTypeDef ClockValue;
  uint16_t TimerPrescalerValue=0x0003;
  uint16_t CountWait;
  uint16_t DeviationInteger;
  uint32_t CalibrationTimer;
  float f32_Deviation;
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  
  TIM_DeInit(TIM2);
  BKP_TamperPinCmd(DISABLE);
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
  
  /* TIM2 configuration: PWM Input mode ------------------------
     The external signal is connected to TIM2 CH2 pin (PA.01),
     The Rising edge is used as active edge,
     The TIM2 CCR2 is used to compute the frequency value
     The TIM2 CCR1 is used to compute the duty cycle value
  ------------------------------------------------------------ */
  TIM_PrescalerConfig(TIM2,TimerPrescalerValue,TIM_PSCReloadMode_Immediate);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x00;
  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  /* Select the TIM2 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
  /* Enable the Master/Slave Mode */
  TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
  /* TIM enable Counter */
  TIM_Cmd(TIM2, ENABLE);
  /* Wait for 2 seconds */
  CalibrationTimer = RTC_GetCounter();
 
  while((RTC_GetCounter() - CalibrationTimer) < 2)
  {
  }
  
  RCC_GetClocksFreq(&ClockValue);
  //TimerFrequency=(ClockValue.PCLK1_Frequency * 2)/(TimerPrescalerValue+1);
   /* Enable the CC2 Interrupt Request */
  TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
   /* Wait for 2 seconds */
  CalibrationTimer = RTC_GetCounter();
  
  while((RTC_GetCounter() - CalibrationTimer) < 2)
  {
  }

  if(!(TIM_GetFlagStatus(TIM2, TIM_FLAG_CC1)))
   /* There is no signal at the timer TIM2 peripheral input */
  {

  }
  else
  {
    /* Calulate Deviation in ppm  using the formula :
    Deviation in ppm = (Deviation from 511.968/511.968)*1 million*/
//    if(f32_Frequency > 511.968)
//    {
//      f32_Deviation=((f32_Frequency-511.968)/511.968)*1000000;
//    }
//    else
//    {
//      f32_Deviation=((511.968-f32_Frequency)/511.968)*1000000;
//    }
     DeviationInteger = (uint16_t)f32_Deviation;
    
    if(f32_Deviation >= (DeviationInteger + 0.5))
    {
      DeviationInteger = ((uint16_t)f32_Deviation)+1;
    }
    
   CountWait=0;

   /* Frequency deviation in ppm should be les than equal to 121 ppm*/
   if(DeviationInteger <= 121)
   {
     while(CountWait<128)
     {
       if(CalibrationPpm[CountWait] == DeviationInteger)
       break;
       CountWait++;
     }

     BKP_SetRTCCalibrationValue(CountWait);
     //LCD_Clear(Blue2);
     //LCD_DisplayString(Line4,Column1,"Calibration Value");
     //LCD_DisplayChar(Line5,Column10,(CountWait%10)+0x30);
     CountWait=CountWait/10;
     //LCD_DisplayChar(Line5,Column9,(CountWait%10)+0x30);
     CountWait=CountWait/10;
   
     if(CountWait>0)
     {
       //LCD_DisplayChar(Line5,Column8,(CountWait%10)+0x30);
     }
   }
   else /* Frequency deviation in ppm is more than 121 ppm, hence calibration
           can not be done */
   {
     //LCD_Clear(Blue2);
     //LCD_DisplayString(Line3,Column1,"Out Of Calibration");
     //LCD_DisplayString(Line4,Column4,"Range");
   }
  }
  
  BKP_RTCOutputConfig(BKP_RTCOutputSource_None);
  TIM_ITConfig(TIM2, TIM_IT_CC2, DISABLE);
  TIM_Cmd(TIM2, DISABLE);
  TIM_DeInit(TIM2);
  CalibrationTimer=RTC_GetCounter();
  
  /*  Wait for 2 seconds  */
  while((RTC_GetCounter() - CalibrationTimer) < 5)
  {
  }
  
  //MenuInit();
}



/**
  * @brief  Configures the Tamper Interrupts
  * @param  None
  * @retval : None
  */
void Tamper_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TAMPER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



/**
  * @brief  Configures RTC Interrupts
  * @param  None
  * @retval : None
  */
void RTC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  
  EXTI_DeInit();

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the EXTI Line17 Interrupt */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  EXTI_ClearITPendingBit(EXTI_Line16 );
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Line = EXTI_Line16;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
