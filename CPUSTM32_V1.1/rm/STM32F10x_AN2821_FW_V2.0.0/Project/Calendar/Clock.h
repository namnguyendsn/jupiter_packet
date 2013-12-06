#define SECONDS_IN_DAY 86399

void RTC_Configuration(void);
void RTC_Re_Configuration(void);
uint32_t Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(uint32_t TimeVar);
void SetTime(uint8_t Hour,uint8_t Minute,uint8_t Seconds); 
void CheckForDaysElapsed(void);
void CalculateTime(void);
void Set_Clock(void);
void Timer_Display(void);
void Menu(void);
u32 Read_u32_BKR(u16 dc);
#define Seting GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define Move GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)
#define Up GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define Down GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)

#define Start1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define Stop1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define Start2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define Stop2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)





typedef struct
{
	u8 Hour;
  	u8 Min;
	u8 Sec;
  
} Clock;

extern Clock Time_Now;


