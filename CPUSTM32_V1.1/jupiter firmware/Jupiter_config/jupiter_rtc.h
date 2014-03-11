#include <stm32f10x.h>
#include "stm32f10x_bkp.h"
#include "stm32f10x_pwr.h"
#include "common_config.h"

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
  uint8_t Year;
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

/* Exported constants --------------------------------------------------------*/
#define BATTERY_REMOVED 98
#define BATTERY_RESTORED 99
#define SECONDS_IN_DAY 86399
#define CONFIGURATION_DONE 0x0002
#define OCTOBER_FLAG_SET 0x4000
#define MARCH_FLAG_SET 0x8000
// default value of date
#define DEFAULT_DAY 15
#define DEFAULT_MONTH 5
#define DEFAULT_YEAR 13 // khi tinh toan + 2000
#define DEFAULT_HOURS 9
#define DEFAULT_MINUTES 24
#define DEFAULT_SECONDS 0

#define LEAP 1
#define NOT_LEAP 0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_Configuration(void);
void GPIO_Configuration(void);
void SysTickConfig(void);
void CheckForDaysElapsed(void);
void set_time(uint8_t *data);
