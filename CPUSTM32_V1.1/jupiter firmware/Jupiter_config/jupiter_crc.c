#include "jupiter_crc.h"

uint8_t calc_crc8(uint8_t* data_pointer, uint8_t number_of_bytes)
{
   uint8_t temp1, bit_counter, feedback_bit, crc8_result=0;
   
   while(number_of_bytes--)
    {
      temp1= *data_pointer++;
      
        for(bit_counter=8; bit_counter; bit_counter--)
        {
         feedback_bit=(crc8_result & 0x01);
         crc8_result >>= 1;
         if(feedback_bit ^ (temp1 & 0x01))
         {
            crc8_result ^= 0x8c;
         }
         temp1 >>= 1;
      }
      
    }
   return crc8_result;
} 
