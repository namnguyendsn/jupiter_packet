#include "stm32f10x_gpio.h"

// infomation of keyboards
#define KEY_PORT	GPIOA
#define KEY_CLK		RCC_APB2Periph_GPIOA

#define KEY_UP		GPIO_Pin_12
#define KEY_SEL		GPIO_Pin_11
//#define KEY_DOW		GPIO_Pin_13
#define KEY_DOW		GPIO_Pin_5
//#define KEY_OK		GPIO_Pin_14
#define KEY_OK		GPIO_Pin_6
//#define KEY_CAN		GPIO_Pin_14
#define KEY_CAN		GPIO_Pin_7

// infomation of softpwm
#define PWM_PORT	GPIOB
#define PWM_PORT_CLK		RCC_APB2Periph_GPIOB

#define PWM_SDI		GPIO_Pin_5
#define PWM_CLK		GPIO_Pin_6
#define PWM_STR		GPIO_Pin_7

// Led status
#define LEDSTT_PORT	GPIOA
#define LEDSTT_PORT_CLK		RCC_APB2Periph_GPIOA

#define LED_STT		GPIO_Pin_2



void sfoftPWM_init(void);
void key_init(void);
void ledstt_init(void);
void LEDstatus(void);
void MCO_config(void);
