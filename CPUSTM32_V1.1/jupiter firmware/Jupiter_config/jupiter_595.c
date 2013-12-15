#include "jupiter_595.h"

void spi_595_init(void)
{
  STM32vldiscovery_LEDInit(SDI);
	STM32vldiscovery_LEDInit(CLK);
	STM32vldiscovery_LEDInit(STR);
	STM32vldiscovery_LEDInit(OE);
	OE_low();
}

void spi_595_send(uint16_t __led_state)
{
   int i;
	 OE_low();
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
