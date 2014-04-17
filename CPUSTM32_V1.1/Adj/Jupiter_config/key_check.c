#include "key_check.h"
/* =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = 
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
 =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = */
menu_state kb_stt;
uint16_t byte_input = 0;
uint16_t time_out = 0;

void menu(void)
{
   time_out = 0;
    byte_input = 0;
   switch (kb_stt)
   {
      case normal:

         kb_stt = SETTIME;
         break;
      case SETTIME:

         kb_stt = SETALARM;
         break;
      case SETTIME_H:

         kb_stt = SETTIME_MIN;
         break;
      case SETTIME_MIN:

         kb_stt = SETTIME_D;
         break;
      case SETTIME_D:

         kb_stt = SETTIME_MON;
         break;
      case SETTIME_MON:

         kb_stt = SETTIME_Y;
         break;
      case SETTIME_Y:

         kb_stt = SETTIME_H;
         break;
      
      case SETALARM:

         kb_stt = SETEFFECTS;
         break;
      case SETALARM_HON:

         kb_stt = SETALARM_MON;
         break;
      case SETALARM_MON:

         kb_stt = SETALARM_HOFF;
         break;
      case SETALARM_HOFF:

         kb_stt = SETALARM_MOFF;
         break;
      case SETALARM_MOFF:

         kb_stt = SETALARM_HON;
         break;

      case SETEFFECTS:

         kb_stt = CHECKTIME;
         break;
      case CHECKTIME:

         kb_stt = CHECKALARM;
         break;
      case CHECKALARM:

         kb_stt = INFO;
         break;
      case INFO:
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
         kb_stt = INFO;
         break;
      case SET_HVAL:
         if(byte_input>23)   byte_input = 0;
         break;
      case SET_MINVAL:
         if(byte_input>59)   byte_input = 0;
         break;
      case SET_DVAL:

         break;
      case SET_MONVAL:
         if(byte_input>12) byte_input = 1;
         break;
      case SET_YVAL:
         if(byte_input>100)  byte_input = 0;
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
            kb_stt = INFO;
            break;
        case SET_HVAL:
            if(byte_input>23)   byte_input = 0;
            break;
        case SET_MINVAL:
            if(byte_input>59)   byte_input = 0;
            break;
        case SET_DVAL:

            break;
        case SET_MONVAL:
            if(byte_input>12) byte_input = 1;
            break;
        case SET_YVAL:
            if(byte_input>100)  byte_input = 0;
            break;
    }
}

void ok_()
{
    time_out = 0;
    switch (kb_stt)
    {
        case SETTIME:
            kb_stt = SETTIME_H;
            break;
        
        case SETTIME_H:

            kb_stt = SET_HVAL;
            break;
        case SETTIME_MIN:

            kb_stt = SET_MINVAL;
            break;
        case SETTIME_D:

            kb_stt = SET_DVAL;
            break;
        case SETTIME_MON:

            kb_stt = SET_MONVAL;
            break;
        case SETTIME_Y:

            kb_stt = SET_YVAL;
            break;
        
        case SETALARM:

            break;
        case SETEFFECTS:

            break;
        case CHECKTIME:

            break;
        case CHECKALARM:

            break;
        case INFO:

            break;
    }
}

void cancel_()
{
    time_out = 0;
    switch (kb_stt)
    {
        case SETTIME:
            kb_stt = normal;
            break;
        case SETTIME_H:
            kb_stt = SETTIME;
            break;
        case SETTIME_MIN:
            kb_stt = SETTIME;
            break;
        case SETTIME_D:
            kb_stt = SETTIME;
            break;
        case SETTIME_MON:
            kb_stt = SETTIME;
            break;
        case SETTIME_Y:
            kb_stt = SETTIME;
            break;
        case SETALARM:
            kb_stt = normal;
            break;
        case SETEFFECTS:
            kb_stt = normal;
            break;
        case CHECKTIME:
            kb_stt = normal;
            break;
        case CHECKALARM:
            kb_stt = normal;
            break;
        case INFO:
            kb_stt = normal;
            break;
    }
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
         case SETTIME:
               Delay_ms(1000);
               break;
         case SETTIME_H:
               Delay_ms(1000);
               break;
         case SETTIME_MIN:

               chg = 1;
               break;
         case SETTIME_D:

               chg = 1;
               break;
         case SETTIME_MON:

               chg = 1;
               break;
         case SETTIME_Y:

               chg = 1;
               break;
         case SETALARM:

               chg = 1;
               break;
         case SETALARM_HON:
               chg = 1;
               break;
         case SETALARM_MON:
               chg = 1;
               break;
         case SETALARM_HOFF:
               chg = 1;
               break;
         case SETALARM_MOFF:
               chg = 1;
               break;
         case SETALARM_HON_VAL:
               chg = 1;
               break;
         case SETALARM_MON_VAL:
               chg = 1;
               break;
         case SETALARM_HOFF_VAL:
               chg = 1;
               break;
         case SETALARM_MOFF_VAL:
               chg = 1;
               break;
         case SET_HVAL:
               chg = 1;
               break;
         case SET_MINVAL:
               chg = 1;
               break;
         case SET_DVAL:
               chg = 1;
               break;
         case SET_MONVAL:
               chg = 1;
               break;
         case SET_YVAL:
               chg = 1;
               break;
         case SETEFFECTS:
               chg = 1;
               break;
         case SETEFFECTS_SELECT:
               chg = 1;
               break;
         case CHECKTIME:
               chg = 1;
               break;
         case CHECKALARM:
               chg = 1;
               break;
         case INFO:
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


