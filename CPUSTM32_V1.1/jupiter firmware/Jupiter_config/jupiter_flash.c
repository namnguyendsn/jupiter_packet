#include "jupiter_flash.h"
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
flashcallback fcallback;
static uint32_t Address = 0;

void flash_init(void)
{
    fcallback = jupiter_flash_write;
}

int8_t jupiter_effect_erase(void)
{
	uint8_t page_index;

  /* Unlock the Flash Bank1 Program Erase controller */
  FLASH_UnlockBank1();
  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
	  /* Erase the FLASH pages */
  for(page_index = 0; (page_index < FLASH_NUMPAGE); page_index++)
  {
    FLASHStatus = FLASH_ErasePage(EFFECT_BEGIN_ADD + (FLASH_PAGE_SIZE * page_index));
		if(FLASHStatus == FLASH_COMPLETE)
		{
			return JUPITER_FLASH_FAIL;
	  }
  }
	/* Lock after erase */
	FLASH_LockBank1();
	return JUPITER_OK;
}

void jupiter_write_stt(uint32_t buff, uint32_t address)
{
    FLASH_ProgramHalfWord(address, buff);
}

int8_t jupiter_flash_write(uint8_t *buff, uint8_t size, uint8_t stt)
{
	uint8_t index = 0;
    uint16_t *effect_data;

    uint32_t EraseCounter = 0x00;
    __IO uint32_t NbrOfPage = 0x00;
	
    /* Unlock the Flash Bank1 Program Erase controller */
    FLASH_UnlockBank1();
    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

    if((stt == PK_DONE) || (stt == PK_IDLE))
    {
        /* Erase the FLASH pages */
        for(EraseCounter = 0; (EraseCounter < FLASH_NUMPAGE) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
        {
            FLASHStatus = FLASH_ErasePage(FLASH_START_ADDRESS + (FLASH_PAGE_SIZE * EraseCounter));
        }
        Address = EFFECT_BEGIN_ADD;
    }
    effect_data = (uint16_t *)buff;

    while((Address < EFFECT_END_ADD) && (index < size))
    {
        index += 2;
        FLASHStatus = FLASH_ProgramHalfWord(Address, *effect_data);
        Address = Address + 2;
        effect_data++;

        if(FLASHStatus != FLASH_COMPLETE)
        {
            return JUPITER_FLASH_FAIL;
        }
    }
		
	FLASH_LockBank1();
	return JUPITER_OK;
}

int8_t jupiter_flash_read(flash_write type, uint8_t *data, uint16_t size)
{
    return 1;
}
