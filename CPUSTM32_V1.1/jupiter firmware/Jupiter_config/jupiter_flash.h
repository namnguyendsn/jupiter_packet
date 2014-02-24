#include "stm32f10x_flash.h"
#include "common_config.h"

#define CONFIG_BEGIN_ADD 0x8005000
#define CONFIG_END_ADD   0x8008000

#define TIME_BEGIN_ADD   0x8005000
#define TIME_END_ADD     0x8005013

#define ALARM_BEGIN_ADD  0x8005014
#define ALARM_END_ADD    0x80050DB

#define EFFECT_BEGIN_ADD 0x08007C00
#define EFFECT_END_ADD   0x08008000

#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define FLASH_NUMPAGE   12

#define PK_DONE 7
#define PK_IDLE 8

typedef enum  
{  
	WRITE_EFFECT = 0,	
	WRITE_ALARM
}flash_write;

void flash_init(void);
int8_t jupiter_effect_erase(void);
int8_t jupiter_flash_write(uint8_t *buff, uint8_t size, uint8_t stt);
int8_t jupiter_flash_read(flash_write type, uint8_t *data, uint16_t size);
