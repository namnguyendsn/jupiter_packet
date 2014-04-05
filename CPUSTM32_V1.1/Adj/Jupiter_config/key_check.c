#include "key_check.h"
/* =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = 
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
 =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = */
key_state kb_stt;
uint16_t byte_input = 0;
uint16_t time_out = 0;

void menu(void)
{
   time_out = 0;
    byte_input = 0;
   switch (kb_stt)
   {
      case normal:

         kb_stt = chinhgio_value;
         break;
      case chinhgio_value:

         kb_stt = chinhphut_value;
         break;
      case chinhphut_value:

         kb_stt = chinhngay_value;
         break;
      case chinhngay_value:

         kb_stt = chinhthang_value;
         break;
      case chinhthang_value:

         kb_stt = chinhnam_value;
         break;
      case chinhnam_value:

         kb_stt = chinhthu_value;
         break;
      case chinhthu_value:
         kb_stt = normal;
         break;
   }
}

void up_()
{
   time_out = 0;
   byte_input++;
   switch (kb_stt)
   {
      case normal:
         kb_stt = xemnhietdo;
         break;
      case chinhgio_value:
         if(byte_input>23)   byte_input = 0;
         break;
      case chinhphut_value:
         if(byte_input>59)   byte_input = 0;
         break;
      case chinhngay_value:

         break;
      case chinhthang_value:
         if(byte_input>12) byte_input = 1;
         break;
      case chinhnam_value:
         if(byte_input>100)  byte_input = 0;
         break;
      case chinhthu_value:
         if(byte_input>8)  byte_input = 2;
         break;
   }
}

void down_()
{
   time_out = 0;  
   --byte_input;
   switch (kb_stt)
   {
      case normal:
         kb_stt = xemngay;
         break;
      case chinhgio_value:
         if(byte_input>23)   byte_input = 23;
         break;
      case chinhphut_value:
         if(byte_input>59)   byte_input = 59;
         break;
      case chinhngay_value:

         break;
      case chinhthang_value:
         if(byte_input <= 1) byte_input = 12;
         break;
      case chinhnam_value:
         if(byte_input <= 000)  byte_input = 100;
         break;
      case chinhthu_value:
         if(byte_input <= 2)  byte_input = 8;
         break;
  }
}

void ok_()
{
   time_out = 0;
   switch (kb_stt)
   {
      case chinhgio_value:

         break;
      case chinhphut_value:

         break;
      case chinhngay_value:

         break;
      case chinhthang_value:

         break;
      case chinhnam_value:

         break;
      case chinhthu_value:

         break;
   }
   kb_stt = normal;
}
//------------------------quet ban phim---------------------------------
void scan_key(void) // phim bam binh thuong o muc cao, khi nhan phim thi chuyen muc thap
{
   if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_SEL))
   {
       LCD1_Clear();
       LCD1_WriteLineStr(0, "Key selected");
       menu();
       Delay_ms(200);
   }
   if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_UP))
   {
       LCD1_Clear();
       LCD1_WriteLineStr(0, "Key Up");
       Delay_ms(200);
       up_();
   }
//   if(GPIO_ReadInputDataBit(KEY_PORT, KEY_DOW))
//   {
//       LCD1_Clear();
//       LCD1_WriteLineStr(0, "Key Down");
//       Delay_ms(200);
//       down_();
//   }            
//   if(GPIO_ReadInputDataBit(KEY_PORT, KEY_OK))
//   {
//       LCD1_Clear();
//       LCD1_WriteLineStr(0, "Key ok");
//       Delay_ms(200);
//       ok_();
//   }
//   if(GPIO_ReadInputDataBit(KEY_PORT, KEY_CAN))
//   {
//       LCD1_Clear();
//       LCD1_WriteLineStr(0, "Key cancel");
//       Delay_ms(200);
//       ok_();
//   }
}
//----------------------hien thi trang thai--------------------------------
//-------- doan code khi bam menu
void state_dislay(void)
{
   uint8_t temp, chg = 0;
   if(kb_stt !=  normal)
      time_out++;
   switch (kb_stt)
      {
         case normal:
               break;
         case xemngay:
               kb_stt = normal;
               Delay_ms(1000);
               break;
         case xemnhietdo:
               kb_stt = normal;
               Delay_ms(1000);
               break;
         case chinhgio_value:

               chg = 1;
               break;
         case chinhphut_value:

               chg = 1;
               break;
         case chinhngay_value:

               chg = 1;
               break;
         case chinhthang_value:

               chg = 1;
               break;
         case chinhnam_value:

               chg = 1;
               break;
         case chinhthu_value:

               chg = 1;
               break;
      }
   if(chg  ==  1)
   {
      chg = 0;
   }
   if(time_out > 10000)//reset time_out;
   {
      time_out = 0;
      kb_stt = normal;
   }
}


