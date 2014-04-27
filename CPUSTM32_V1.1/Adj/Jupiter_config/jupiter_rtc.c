#include "jupiter_rtc.h"
#include "stm32f10x_bkp.h"

/* Private variables--------------------------------------------------------- */
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
Time_s systime;
struct AlarmTime_s s_AlarmStructVar;
struct AlarmDate_s s_AlarmDateStructVar;
extern uint8_t AlarmDate;

void SetTime(uint8_t Hour,uint8_t Minute);
void SetDate(uint8_t Day, uint8_t Month, uint8_t Year);
static uint8_t CheckLeap(uint16_t Year);
static void RTC_NVIC_Configuration(void);

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
    if(BKP_ReadBackupRegister(BKP_DR1)== (uint16_t)(~CONFIGURATION_DONE))
    {
        /*Enables the clock to Backup and power interface peripherals    */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR,ENABLE);

        /* Backup Domain Reset */
        BKP_DeInit();
        systime.Month=DEFAULT_MONTH;
        systime.Day=DEFAULT_DAY;
        systime.Year=DEFAULT_YEAR;

        BKP_ModifyBackupRegister(BKP_DR3, (systime.Month << 8) | systime.Day);
        BKP_ModifyBackupRegister(BKP_DR5, systime.Year);
            
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
        SetTime(DEFAULT_HOURS,DEFAULT_MINUTES);
        BKP_ModifyBackupRegister(BKP_DR1, CONFIGURATION_DONE);
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
    systime.Month = (uint8_t)(BKP_ReadBackupRegister(BKP_DR3) >> 8);
    systime.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
    systime.Year = (uint8_t)BKP_ReadBackupRegister(BKP_DR5);
    
    BKP_RTCOutputConfig(BKP_RTCOutputSource_None);
}

void set_time(uint8_t *data)
{
    TIME_PTR temp;
    temp = (TIME_PTR)data;
    SetTime(temp->hours, temp->minutes);
    SetDate(temp->days, temp->months, temp->years);
}

/**
* @brief  Sets the RTC Current Counter Value
* @param Hour, Minute and Seconds data
* @retval : None
*/
void SetTime(uint8_t Hour,uint8_t Minute)
{
    uint32_t CounterValue;

    CounterValue=((Hour * 3600) + (Minute * 60));

    RTC_WaitForLastTask();
    RTC_SetCounter(CounterValue);
    RTC_WaitForLastTask();
}

/**
* @brief  Sets the RTC Alarm Register Value
* @param Hours, Minutes data
* @retval : None
*/
static void SetAlarm(uint8_t Hour,uint8_t Minute)
{
    uint32_t CounterValue;

    CounterValue=((Hour * 3600)+ (Minute * 60));

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
void SetDate(uint8_t Day, uint8_t Month, uint8_t Year)
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
        BKP_ModifyBackupRegister(BKP_DR3,Day | (Month << 8));
        BKP_ModifyBackupRegister(BKP_DR5,Year);
    }
}

/**
* @brief Updates the Date (This function is called when 1 Day has elapsed
* @param None
* @retval :None
*/
void DateUpdate(void)
{
    systime.Month = (uint8_t)BKP_ReadBackupRegister(BKP_DR3) >> 8;
    systime.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
    systime.Year = (uint8_t)BKP_ReadBackupRegister(BKP_DR5);

    if(systime.Month == 1 || systime.Month == 3 || \
            systime.Month == 5 || systime.Month == 7 ||\
            systime.Month == 8 || systime.Month == 10 \
            || systime.Month == 12)
    {
        if(systime.Day < 31)
        {
            systime.Day++;
        }
        /* Date structure member: systime.Day = 31 */
        else
        {
            if(systime.Month != 12)
            {
                systime.Month++;
                systime.Day = 1;
            }
            /* Date structure member: systime.Day = 31 & systime.Month =12 */
            else
            {
                systime.Month = 1;
                systime.Day = 1;
                systime.Year++;
            }
        }
    }
    else if(systime.Month == 4 || systime.Month == 6 \
            || systime.Month == 9 ||systime.Month == 11)
    {
        if(systime.Day < 30)
        {
            systime.Day++;
        }
        /* Date structure member: systime.Day = 30 */
        else
        {
            systime.Month++;
            systime.Day = 1;
        }
    }
    else if(systime.Month == 2)
    {
        if(systime.Day < 28)
        {
            systime.Day++;
        }
        else if(systime.Day == 28)
        {
            /* Leap Year Correction */
            if(CheckLeap(systime.Year))
            {
                systime.Day++;
            }
            else
            {
                systime.Month++;
                systime.Day = 1;
            }
        }
        else if(systime.Day == 29)
        {
            systime.Month++;
            systime.Day = 1;
        }
    }

    BKP_ModifyBackupRegister(BKP_DR3,systime.Day | (systime.Month << 8));
    BKP_ModifyBackupRegister(BKP_DR5,systime.Year);
}

/**
* @brief  Checks whether the passed year is Leap or not.
* @param  None
* @retval : 1: leap year
*   0: not leap year
*/
static uint8_t CheckLeap(uint16_t Year)
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
* @brief Calcuate the Time (in hours, minutes and seconds  derived from
*   COunter value
* @param None
* @retval :None
*/
void CalculateTime(void)
{
    uint32_t TimeVar;

    TimeVar = RTC_GetCounter();
    TimeVar = TimeVar % 86400;
    systime.Hour = (uint8_t)(TimeVar/3600);
    systime.Min = (uint8_t)((TimeVar%3600)/60);
    systime.Sec = (uint8_t)((TimeVar%3600)%60);

    if((systime.Month == 1) || 
        (systime.Month == 3) || 
        (systime.Month == 5) || 
        (systime.Month == 7) || 
        (systime.Month == 8) || 
        (systime.Month == 10) || 
        (systime.Month == 12))
    {
        systime.MonthType = 3;// thang 31 ngay
    }
    else if(systime.Month == 2)
    {
        if(((systime.Year % 4 == 0) && (systime.Year % 100 != 0)) || ((systime.Year % 400) == 0))
            systime.MonthType = 1;// thang 29 ngay
        else
            systime.MonthType = 0;// thang 28 ngay
    }
    else
    {
        systime.MonthType = 2;// thang 30 ngay
    }
}

/**
* @brief Chaeks is counter value is more than 86399 and the number of
*   elapsed and updates date that many times
* @param None
* @retval :None
*/
static void CheckForDaysElapsed(void)
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
static void RTC_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = PVD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
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
    //printf("\nHour: %d\nMin: %d\nSec: %d", systime.Hour, systime.Min, systime.Sec);
}

/**
  * @brief Displays the Date(DD/MM/YY and DAY ) on LCD
  * @param None
  * @retval :None
  */
void DisplayDate(void)
{
    systime.Year = (BKP_ReadBackupRegister(BKP_DR5));
    systime.Month = (uint8_t)(BKP_ReadBackupRegister(BKP_DR3) >> 8);
    systime.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
	
    //printf("\nDay: %c%c", (systime.Day/10) + 0x30, (systime.Day%10) + 0x30);
	//printf("\nMonth: %d", systime.Month);
	//printf("\nYear: %c%c", ((systime.Year/1000) + 0x30), ((systime.Year/100)%10) + 0x30);
	//printf("%c%c\n", ((systime.Year/10)%10) + 0x30, (systime.Year%10) + 0x30);
}
