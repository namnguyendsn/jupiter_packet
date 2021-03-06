#include "stm32f10x_spi.h"

#define SPIn 1
#define SPI1_CLK                        GPIO_Pin_4
#define SPI1_MOSI                       GPIO_Pin_5
#define SPI1_MISO                       GPIO_Pin_6
#define SPI1_NSS                        GPIO_Pin_7
#define SPI1_IO_PORT                    SPI1
#define SPI1_CLK_SRC                    RCC_APB2Periph_SPI1
//SPI_TypeDef* SPI_PORT[SPIn] = {SPI1_IO_PORT};

/*
function prototype
*/
void spi_init(void);
void hard_spi_send_595(uint16_t __led_state);
