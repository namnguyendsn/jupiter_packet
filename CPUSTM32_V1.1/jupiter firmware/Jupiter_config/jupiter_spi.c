#include "jupiter_spi.h"
#include "stdlib.h"

static SPI_InitTypeDef * g_pSPIinit;
static void spi_send(uint16_t datain);
static void pinout_595(void);

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
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* init spi */
	SPI_StructInit(g_pSPIinit);
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                     // enable clock for Alternate Function
	SPI_Init(SPI1, g_pSPIinit);
	/* SPI2 enable */
	SPI_Cmd(SPI1, ENABLE);
	// init LE pin
	pinout_595();
}

/*
sua them phan tach data thanh 2 phien truyen neu truyen data 32bit
*/
static void spi_send(uint16_t datain)
{
	if(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY))
	{
    SPI_I2S_SendData(SPI1, datain);
	}
}

static void pinout_595(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	#define LE_low() GPIO_ResetBits(GPIOA, GPIO_Pin_6);
	#define LE_high() GPIO_SetBits(GPIOA, GPIO_Pin_6);
	#define _BV(bit) (1 << (bit))
}

void hard_spi_send_595(uint16_t __led_state)
{
  int i;
  LE_low();
	// send data over spi
	spi_send(__led_state);
  LE_high();
}
