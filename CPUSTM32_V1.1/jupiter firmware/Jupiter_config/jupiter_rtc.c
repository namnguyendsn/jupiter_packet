#include "jupiter_rtc.h"

// init RTC
void rtc_init(void)
{
	uint16_t WaitForOscSource;

	/*Enables the clock to Backup and power interface peripherals    */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

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
//		SummerTimeCorrect = OCTOBER_FLAG_SET;
//		BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
		BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
		BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
		BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
		BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);

		TamperNumber=0;
		BKP_WriteBackupRegister(BKP_DR5,TamperNumber);

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
 #endif
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
  TamperNumber = BKP_ReadBackupRegister(BKP_DR5);
  s_DateStructVar.Month = BKP_ReadBackupRegister(BKP_DR2);
  s_DateStructVar.Day = BKP_ReadBackupRegister(BKP_DR3);
  s_DateStructVar.Year = BKP_ReadBackupRegister(BKP_DR4);
//  SummerTimeCorrect = BKP_ReadBackupRegister(BKP_DR7);
  s_AlarmDateStructVar.Month = BKP_ReadBackupRegister(BKP_DR8);
  s_AlarmDateStructVar.Day = BKP_ReadBackupRegister(BKP_DR9);
  s_AlarmDateStructVar.Year = BKP_ReadBackupRegister(BKP_DR10);
}
