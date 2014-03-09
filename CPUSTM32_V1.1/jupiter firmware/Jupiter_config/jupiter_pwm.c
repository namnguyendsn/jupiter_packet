#include "stdint.h"
#include "stdlib.h"
#include "jupiter_pwm.h"

extern void spi_595_send(uint16_t __led_state);
extern void hard_spi_send_595(uint16_t __led_state);

PWM_STRUCT *pwm_data = NULL;
/*
LED PWM over software SPI
*/
//void SoftPWM(void)
//{
//	spi_595_send((pwm_c[0] > pwm_num[0]) ? 0:DATA_OUT);
//	if(++pwm_num[0]==50){
//		pwm_num[0]=0;
//	}
//}

/*
LED PWM over hardware SPI
*/
void HardLEDPWM(void)
{
    uint16_t temp;
    uint8_t i;
    uint8_t ledPos;

    if(pwm_data != NULL)
    {
        for(i = 0; i < LEDS; i++)
        {
             ledPos  = DATA_OUT << i;
            (pwm_data[i].pwm_ldval > pwm_data[i].step_count) ? (temp |= ledPos) : (temp &= ~ledPos);
            if(++pwm_data[i].step_count == 50)
            {
                pwm_data[i].step_count = 0;
            }
        }
        hard_spi_send_595(temp);
    }
}
