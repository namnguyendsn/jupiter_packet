#include "jupiter_rtc.h"

// init RTC
void rtc_init(void)
{
	uint16_t WaitForOscSource;

	/*Enables the clock to Backup and power interface peripherals    */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

  /*Allow access to Backup Registers*/
  PWR_BackupAccessCmd(ENABLE);

	/* Backup Domain Reset */
	BKP_DeInit();
	s_DateStructVar.Month=DEFAULT_MONTH ;
	s_DateStructVar.Day=DEFAULT_DAY;
	s_DateStructVar.Year=DEFAULT_YEAR;

	BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
	BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
	BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
	BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* enter config mode */
	RTC_EnterConfigMode();
	/*Enable 32.768 kHz external oscillator */
	RCC_LSEConfig(RCC_LSE_ON);
	/* select clock source for RTC */
//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
	/* RTC Enabled */
	RCC_RTCCLKCmd(ENABLE);
	/*Wait for RTC registers synchronisation */
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	/* Setting RTC Interrupts-Seconds interrupt enabled */
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC , ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* init prescale value*/
	RTC_SetPrescaler(32767);
	/* exit config mode */
	RTC_ExitConfigMode();
#if 0
    if(TotalMenuPointer==1 || TotalMenuPointer==6)
    {
      BKP_WriteBackupRegister(BKP_DR6, 1);
  
      /* Set RTC prescaler: set RTC period to 1 sec */
      RTC_SetPrescaler(32765); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
      /* Prescaler is set to 32766 instead of 32768 to compensate for
        lower as well as higher frequencies*/
      /* Wait until last write operation on RTC registers has finished */
      RTC_WaitForLastTask();
    }

    if( TotalMenuPointer==7)
    {
      BKP_WriteBackupRegister(BKP_DR6, 2);
      /* Set RTC prescaler: set RTC period to 1 sec */
      RTC_SetPrescaler(49); /* RTC period = RTCCLK/RTC_PR = (50 Hz)/(49+1) */
      /* Wait until last write operation on RTC registers has finished */
      RTC_WaitForLastTask();
    }
  
    if(TotalMenuPointer==8)
    {
      BKP_WriteBackupRegister(BKP_DR6, 3);
      /* Set RTC prescaler: set RTC period to 1 sec */
      RTC_SetPrescaler(59); /* RTC period = RTCCLK/RTC_PR = (60 Hz)/(59+1) */
      /* Wait until last write operation on RTC registers has finished */
      RTC_WaitForLastTask();
    }

    /* Set default system time to 09 : 24 : 00 */
    SetTime(DEFAULT_HOURS,DEFAULT_MINUTES,DEFAULT_SECONDS);
    BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
    
  /* Check if how many days are elapsed in power down/Low Power Mode-
		Updates Date that many Times*/
		CheckForDaysElapsed();
		ClockSource = BKP_ReadBackupRegister(BKP_DR6);
		TamperNumber = BKP_ReadBackupRegister(BKP_DR5);
		s_DateStructVar.Month = BKP_ReadBackupRegister(BKP_DR2);
		s_DateStructVar.Day = BKP_ReadBackupRegister(BKP_DR3);
		s_DateStructVar.Year = BKP_ReadBackupRegister(BKP_DR4);
		//  SummerTimeCorrect = BKP_ReadBackupRegister(BKP_DR7);
		s_AlarmDateStructVar.Month = BKP_ReadBackupRegister(BKP_DR8);
		s_AlarmDateStructVar.Day = BKP_ReadBackupRegister(BKP_DR9);
		s_AlarmDateStructVar.Year = BKP_ReadBackupRegister(BKP_DR10);

		BKP_RTCOutputConfig(BKP_RTCOutputSource_None);
 #endif
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
