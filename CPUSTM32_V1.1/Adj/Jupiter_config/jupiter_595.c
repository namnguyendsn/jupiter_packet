#include "jupiter_595.h"

#define SH_CP_low() GPIO_ResetBits(PWM_PORT, PWM_CLK)
#define SH_CP_high() GPIO_SetBits(PWM_PORT, PWM_CLK)
#define ST_CP_low() GPIO_ResetBits(PWM_PORT, PWM_STR)
#define ST_CP_high() GPIO_SetBits(PWM_PORT, PWM_STR)
#define DS_low() GPIO_ResetBits(PWM_PORT, PWM_SDI)
#define DS_high() GPIO_SetBits(PWM_PORT, PWM_SDI)

#define _BV(bit) (1 << (bit))

void softSPIPWM_init(void)
{
    sfoftPWM_init();
}

void spi_595_send(uint16_t __led_state)
{
   uint8_t i;
   SH_CP_low();
   Delay_ms(1);
   ST_CP_low();
   Delay_ms(1);
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
      Delay_ms(1);
      SH_CP_high();
      Delay_ms(1);
      SH_CP_low();
      Delay_ms(1);
   }
   ST_CP_high();
}
