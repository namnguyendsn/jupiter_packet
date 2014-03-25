#include "jupiter_595.h"
#if SOFT_PWM_B
#define SH_CP_low() GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SH_CP_high() GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define ST_CP_low() GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define ST_CP_high() GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define DS_low() GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define DS_high() GPIO_SetBits(GPIOB, GPIO_Pin_5)
#else
#define SH_CP_low() GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define SH_CP_high() GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define ST_CP_low() GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define ST_CP_high() GPIO_SetBits(GPIOA, GPIO_Pin_6)
#define DS_low() GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define DS_high() GPIO_SetBits(GPIOA, GPIO_Pin_7)
#endif
#define _BV(bit) (1 << (bit))

void spi_595_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOA clock */
#if SOFT_PWM_B
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#else
	/* 
	Configure SPI2 pins: 
	SDI:  A7
	SCK: A5
	LE: A6
	*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
}

void spi_595_send(uint16_t __led_state)
{
   uint8_t i;
   SH_CP_low();
   ST_CP_low();
   for(i=0;i<16;i++)
   {
	   if((_BV(i) & __led_state) == _BV(i))//bit_is_set doesn’t work on unsigned int so we do this instead
	   {
		   DS_high();
	   }
	   else
	   {
		   DS_low();
	   }
      SH_CP_high();
      SH_CP_low();
   }
   ST_CP_high();
}
