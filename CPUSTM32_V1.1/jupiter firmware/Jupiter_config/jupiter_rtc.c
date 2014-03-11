#include "jupiter_rtc.h"

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
struct Time_s s_TimeStructVar;
struct AlarmTime_s s_AlarmStructVar;
struct Date_s s_DateStructVar;
struct AlarmDate_s s_AlarmDateStructVar;
extern uint8_t AlarmDate;

static void SetTime(uint8_t Hour,uint8_t Minute);
static void SetDate(uint8_t Day, uint8_t Month, uint8_t Year);
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
        s_DateStructVar.Month=DEFAULT_MONTH;
        s_DateStructVar.Day=DEFAULT_DAY;
        s_DateStructVar.Year=DEFAULT_YEAR;

        BKP_WriteBackupRegister(BKP_DR3, (s_DateStructVar.Month << 8) | s_DateStructVar.Day);
        BKP_WriteBackupRegister(BKP_DR5, s_DateStructVar.Year);
            
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
    s_DateStructVar.Month = (uint8_t)(BKP_ReadBackupRegister(BKP_DR3) >> 8);
    s_DateStructVar.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
    s_DateStructVar.Year = (uint8_t)BKP_ReadBackupRegister(BKP_DR5);
    
    BKP_RTCOutputConfig(BKP_RTCOutputSource_None);
}

void set_time(uint8_t *data)
{
    SetTime(data[0], data[1]);
    SetDate(data[2], data[3], data[4]);
}

/**
* @brief  Sets the RTC Current Counter Value
* @param Hour, Minute and Seconds data
* @retval : None
*/
static void SetTime(uint8_t Hour,uint8_t Minute)
{
    uint32_t CounterValue;

    CounterValue=((Hour * 3600) + (Minute * 60));

    RTC_WaitForLastTask();
    RTC_SetCounter(CounterValue);
    RTC_WaitForLastTask();
}

/**
* @brief  Sets the RTC Alarm Register Value
* @param Hours, Minutes and Seconds data
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
static void SetDate(uint8_t Day, uint8_t Month, uint8_t Year)
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
        BKP_WriteBackupRegister(BKP_DR3,Day | (Month << 8));
        BKP_WriteBackupRegister(BKP_DR5,Year);
    }
}

/**
* @brief Updates the Date (This function is called when 1 Day has elapsed
* @param None
* @retval :None
*/
void DateUpdate(void)
{
    s_DateStructVar.Month = (uint8_t)BKP_ReadBackupRegister(BKP_DR3) >> 8;
    s_DateStructVar.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
    s_DateStructVar.Year = (uint8_t)BKP_ReadBackupRegister(BKP_DR5);

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

    BKP_WriteBackupRegister(BKP_DR3,s_DateStructVar.Day | (s_DateStructVar.Month << 8));
    BKP_WriteBackupRegister(BKP_DR5,s_DateStructVar.Year);
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
static void CalculateTime(void)
{
    uint32_t TimeVar;

    TimeVar = RTC_GetCounter();
    TimeVar = TimeVar % 86400;
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
static void DisplayTime(void)
{
	CalculateTime();
  printf("\nHour: %d%d\nMin: %d%d\nSec: %d%d", s_TimeStructVar.HourHigh, s_TimeStructVar.HourLow, s_TimeStructVar.MinHigh, s_TimeStructVar.MinLow, s_TimeStructVar.SecHigh, s_TimeStructVar.SecLow);
}

/**
  * @brief Displays the Date(DD/MM/YY and DAY ) on LCD
  * @param None
  * @retval :None
  */
static void DisplayDate(void)
{
    s_DateStructVar.Year = (BKP_ReadBackupRegister(BKP_DR5));
    s_DateStructVar.Month = (uint8_t)(BKP_ReadBackupRegister(BKP_DR3) >> 8);
    s_DateStructVar.Day = (uint8_t)BKP_ReadBackupRegister(BKP_DR3);
	
    printf("\nDay: %c%c", (s_DateStructVar.Day/10) + 0x30, (s_DateStructVar.Day%10) + 0x30);
	printf("\nMonth: %s", s_DateStructVar.Month);
	printf("\nYear: %c%c", ((s_DateStructVar.Year/1000) + 0x30), ((s_DateStructVar.Year/100)%10) + 0x30);
	printf("%c%c\n", ((s_DateStructVar.Year/10)%10) + 0x30, (s_DateStructVar.Year%10) + 0x30);
}
