#include <stm32f10x.h>
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"

/* Exported types ------------------------------------------------------------*/
/* Time Structure definition */
struct Time_s
{
  uint8_t SecLow;
  uint8_t SecHigh;
  uint8_t MinLow;
  uint8_t MinHigh;
  uint8_t HourLow;
  uint8_t HourHigh;
};
extern struct Time_s s_TimeStructVar;

/* Alarm Structure definition */
struct AlarmTime_s
{
  uint8_t SecLow;
  uint8_t SecHigh;
  uint8_t MinLow;
  uint8_t MinHigh;
  uint8_t HourLow;
  uint8_t HourHigh;
};
extern struct AlarmTime_s s_AlarmStructVar;

/* Date Structure definition */
struct Date_s
{
  uint8_t Month;
  uint8_t Day;
  uint16_t Year;
};
extern struct Date_s s_DateStructVar;

/* Alarm Date Structure definition */
struct AlarmDate_s
{
  uint8_t Month;
  uint8_t Day;
  uint16_t Year;
};
extern struct AlarmDate_s s_AlarmDateStructVar;

uint8_t ClockSource;
uint8_t TamperNumber; /* Keeps the number of tamper Events already happened */
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
/*Structure variable declaration for 
system time, system date, alarm time, alarm date 
*/
struct Time_s s_TimeStructVar;
struct AlarmTime_s s_AlarmStructVar;
struct Date_s s_DateStructVar;
struct AlarmDate_s s_AlarmDateStructVar;

/* Exported constants --------------------------------------------------------*/
#define BATTERY_REMOVED 98
#define BATTERY_RESTORED 99
#define SECONDS_IN_DAY 86399
#define CONFIGURATION_DONE 0xAAAA
#define CONFIGURATION_RESET 0x0000
#define OCTOBER_FLAG_SET 0x4000
#define MARCH_FLAG_SET 0x8000
#define DEFAULT_DAY 15
#define DEFAULT_MONTH 5
#define DEFAULT_YEAR 2008
#define DEFAULT_HOURS 9
#define DEFAULT_MINUTES 24
#define DEFAULT_SECONDS 0
#define LEAP 1
#define NOT_LEAP 0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CalendarInit(void);
void RTC_Configuration(void);
void SetTime(uint8_t,uint8_t,uint8_t);
void SetAlarm(uint8_t,uint8_t,uint8_t);
void SetDate(uint8_t,uint8_t,uint16_t);
void RTC_Application(void);
void DateUpdate(void);
uint16_t WeekDay(uint16_t,uint8_t,uint8_t);
uint8_t CheckLeap(uint16_t);
void CalculateTime(void);
void DisplayDate(void);
void DisplayTime(void);
void DisplayAlarm(void);
void RTC_NVIC_Configuration(void);
void ApplicationInit(void);
void GPIO_Configuration(void);
void DelayLowPower(__IO uint32_t nCount);
void SysTickConfig(void);
void CheckForDaysElapsed(void);
void SummerTimeCorrection(void);
void Tamper_NVIC_Configuration(void);
void ManualClockCalibration(void);
void AutoClockCalibration(void);
void ReturnFromStopMode(void);
