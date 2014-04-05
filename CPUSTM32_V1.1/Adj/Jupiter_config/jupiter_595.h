#include "STM32f10x.h"
#include "common_config.h"
#include "jupiter_gpio.h"
#include "timer_delay.h"

void spi_595_send(uint16_t __led_state);
void softSPIPWM_init(void);
