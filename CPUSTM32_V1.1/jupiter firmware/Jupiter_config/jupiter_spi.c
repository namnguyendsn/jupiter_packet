#include "jupiter_spi.h"
#include "math.h"

static SPI_InitTypeDef * g_pSPIinit;

/*
ham khoi tao spi dua tren lib spi
*/
void spi_init(void)
{
	g_pSPIinit = (SPI_InitTypeDef *)malloc(sizeof(SPI_InitTypeDef));
	SPI_StructInit(g_pSPIinit);
	/* Enable the SPI1 Clock */
  RCC_APB2PeriphClockCmd(SPI1_CLK_SRC, ENABLE);

	SPI_Init(SPI1, g_pSPIinit);
}

/*
sua them phan tach data thanh 2 phien truyen neu truyen data 32bit
*/
void spi_send(uint16_t datain)
{
	if(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY))
	{
    SPI_I2S_SendData(SPI1, datain);
	}
}
