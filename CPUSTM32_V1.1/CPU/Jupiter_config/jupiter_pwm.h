#include "stdint.h"

typedef struct pwm_struct_
{
	uint8_t pwm_ldval;
	uint8_t step_count;
}PWM_STRUCT;

#define LEDS 8
#define DATA_OUT 0x0001
