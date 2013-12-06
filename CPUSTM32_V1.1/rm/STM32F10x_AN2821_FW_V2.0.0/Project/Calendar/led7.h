/* LCD Data pins----------------------------------------------------- */
#define IN_D0                   			GPIO_Pin_0
#define IN_D1                   			GPIO_Pin_1
#define IN_D2                   			GPIO_Pin_2
#define IN_D3                   			GPIO_Pin_3
#define IN_D4                   			GPIO_Pin_4
#define IN_D5                   			GPIO_Pin_5
#define IN_D6                   			GPIO_Pin_6
#define IN_D7                   			GPIO_Pin_7
#define IN_DATA_GPIO_PINS         	(LED_D0 |LED_D1|LED_D2|LED_D3|LED_D4|LED_D5|LED_D6|LED_D7)
#define IN_DATA_GPIO_PORT 		GPIOA
#define IN_DATA_GPIO_CLK			RCC_APB2Periph_GPIOA


 extern void Init_LED(void);
 extern void Shift_1byte(u8 data);
 extern  void Innit_Timer2(void);
 extern  void QUET_LED(void);
 extern   u8 Dem_quet;
 extern  u8 LED[6];
 extern  u8 LED1[6];
  extern  u8 LED2[6];
 extern  u8  Cham;
 extern u8 BCD[3];
 extern void BCD_LED(u16  SO);
 	

