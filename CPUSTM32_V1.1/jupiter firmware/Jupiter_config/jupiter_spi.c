#include "jupiter_spi.h"
#include "math.h"

static SPI_InitTypeDef * g_pSPIinit;

/*
ham khoi tao spi dua tren lib spi
*/
void spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	g_pSPIinit = (SPI_InitTypeDef *)malloc(sizeof(SPI_InitTypeDef));

	/* Enable the SPI1 Clock */
	RCC_APB2PeriphClockCmd(SPI1_CLK_SRC, ENABLE);
	/* Enable GPIOB clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure SPI2 pins: NSS, SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* init spi */
	SPI_StructInit(g_pSPIinit);
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
	SPI_Init(SPI1, g_pSPIinit);
	/* SPI2 enable */
	SPI_Cmd(SPI1, ENABLE);
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
