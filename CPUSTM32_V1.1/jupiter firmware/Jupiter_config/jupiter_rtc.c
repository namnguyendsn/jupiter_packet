#include "jupiter_rtc.h"

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
extern uint16_t SummerTimeCorrect;
extern uint8_t DisplayDateFlag;
extern uint8_t AlarmDate;
extern uint8_t TotalMenuPointer;

uint8_t TamperNumber; /* Keeps the number of tamper Events already happened */

// init RTC
void rtc_init(void)
{
    uint16_t WaitForOscSource;
    
		/*RTC_NVIC Configuration */
    RTC_NVIC_Configuration();
	
    /*Enables the clock to Backup and power interface peripherals    */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

    /*Allow access to Backup Registers*/
    PWR_BackupAccessCmd(ENABLE);
    if(BKP_ReadBackupRegister(BKP_DR1)==CONFIGURATION_RESET)
    {
        /*Enables the clock to Backup and power interface peripherals    */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

        if(TotalMenuPointer == 1)
        {
            /* Backup Domain Reset */
            BKP_DeInit();
            s_DateStructVar.Month=DEFAULT_MONTH ;
            s_DateStructVar.Day=DEFAULT_DAY;
            s_DateStructVar.Year=DEFAULT_YEAR;
            SummerTimeCorrect = OCTOBER_FLAG_SET;

            BKP_WriteBackupRegister(BKP_DR7,SummerTimeCorrect);
            BKP_WriteBackupRegister(BKP_DR2,s_DateStructVar.Month);
            BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day);
            BKP_WriteBackupRegister(BKP_DR4,s_DateStructVar.Year);
            BKP_WriteBackupRegister(BKP_DR1, CONFIGURATION_DONE);
        }
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
        /* enter config mode */
        RTC_EnterConfigMode();
        /*Enable 32.768 kHz external oscillator */
        RCC_LSEConfig(RCC_LSE_ON);
        /* select clock source for RTC */
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
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
    SummerTimeCorrect = BKP_ReadBackupRegister(BKP_DR7);
    s_AlarmDateStructVar.Month = BKP_ReadBackupRegister(BKP_DR8);
    s_AlarmDateStructVar.Day = BKP_ReadBackupRegister(BKP_DR9);
    s_AlarmDateStructVar.Year = BKP_ReadBackupRegister(BKP_DR10);

    BKP_RTCOutputConfig(BKP_RTCOutputSource_None);

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
  * @brief Displays the Time on LCD
  * @param None
  * @retval :None
  */
void DisplayTime(void)
{
	CalculateTime();
  printf("\nHour: %d%d\nMin: %d%d\nSec: %d%d", s_TimeStructVar.HourHigh, s_TimeStructVar.HourLow, s_TimeStructVar.MinHigh, s_TimeStructVar.MinLow, s_TimeStructVar.SecHigh, s_TimeStructVar.SecLow);
}

/**
  * @brief Displays the Date(DD/MM/YY and DAY ) on LCD
  * @param None
  * @retval :None
  */
void DisplayDate(void)
{
  s_DateStructVar.Year=(BKP_ReadBackupRegister(BKP_DR4));
  s_DateStructVar.Month=(BKP_ReadBackupRegister(BKP_DR2));
  s_DateStructVar.Day=(BKP_ReadBackupRegister(BKP_DR3));
	
	
  printf("\nDay: %c%c", (s_DateStructVar.Day/10) + 0x30, (s_DateStructVar.Day%10) + 0x30);
	printf("\nMonth: %s", MonthsNames[s_DateStructVar.Month-1]);
	printf("\nYear: %c%c", ((s_DateStructVar.Year/1000) + 0x30), ((s_DateStructVar.Year/100)%10) + 0x30);
	printf("%c%c\n", ((s_DateStructVar.Year/10)%10) + 0x30, (s_DateStructVar.Year%10) + 0x30);
	
  switch(WeekDay(s_DateStructVar.Year,s_DateStructVar.Month,s_DateStructVar.Day))
  {
    case 0: printf("Sun\n");
            break;
    case 1: printf("Mon\n");
            break;
    case 2: printf("Tue\n");
            break;
    case 3: printf("Wed\n");
            break;
    case 4: printf("Thu\n");
            break;
    case 5: printf("Fri\n");
            break;
    case 6: printf("Sat\n");
            break;
  }
}
