#include "stm32f10x_flash.h"
#include "common_config.h"

#define PK_DONE 7
#define PK_IDLE 8

typedef enum  
{  
	WRITE_EFFECT = 0,	
	WRITE_ALARM
}flash_write;

void flash_init(void);
int8_t jupiter_effect_erase(void);
int8_t jupiter_flash_write(uint8_t *buff, uint8_t size, uint8_t stt, uint32_t BeginAdd, uint32_t EndAdd);
int8_t jupiter_flash_read(flash_write type, uint8_t *data, uint16_t size);
void jupiter_write_stt(uint32_t buff, uint32_t address);
