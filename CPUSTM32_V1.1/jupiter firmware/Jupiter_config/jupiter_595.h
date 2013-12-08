#include "STM32f10x.h"
#include "common_config.h"
#include "JupiterV1_1.h"

#define SH_CP_low() STM32vldiscovery_LEDOff(CLK)
#define SH_CP_high() STM32vldiscovery_LEDOn(CLK)
#define ST_CP_low() STM32vldiscovery_LEDOff(STR)
#define ST_CP_high() STM32vldiscovery_LEDOn(STR)
#define DS_low() STM32vldiscovery_LEDOff(SDI)
#define DS_high() STM32vldiscovery_LEDOn(SDI)
#define OE_low() STM32vldiscovery_LEDOff(OE)
#define _BV(bit) (1 << (bit))

void spi_595_send(uint16_t __led_state);
void spi_595_init(void);
