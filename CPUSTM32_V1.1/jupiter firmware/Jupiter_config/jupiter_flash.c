#include "jupiter_flash.h"
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
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

int8_t jupiter_flash_write(flash_write type, uint8_t *buff, uint16_t size)
{
	uint8_t page_index;
    uint32_t Address = 0;
	uint32_t effect_data;
	
  /* Unlock the Flash Bank1 Program Erase controller */
  FLASH_UnlockBank1();
  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
	  /* Erase the FLASH pages */

  Address = EFFECT_BEGIN_ADD;

  while(Address < EFFECT_END_ADD)
  {
    FLASHStatus = FLASH_ProgramWord(Address, effect_data);
    Address = Address + 4;
		if(FLASHStatus == FLASH_COMPLETE)
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
