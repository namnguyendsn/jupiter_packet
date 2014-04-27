#include "key_check.h"
#include "jupiter_rtc.h"
/* =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = 
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
 =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  =  = */
menu_state kb_stt = NORMAL;
int16_t byte_input = 0;
uint16_t time_out = 0;
Time_s TimeTemp;
extern Time_s systime;
void display_menu(uint8_t currpoint, uint8_t menu, uint8_t refresh);
void display_subtime_menu(uint8_t currpoint, uint8_t val);
struct_menu main_menu[MAX_MENU] = 
{
    {// set time
        (uint8_t *)MAIN_SET_TIME,
        SETTIME,
    },
    {// set alarm
        (uint8_t *)MAIN_SET_ALARM,
        SETALARM,
    },
    {// set effect
        (uint8_t *)MAIN_SET_EFFECT,
        SETEFFECTS,
    },
    {// check alarm
        (uint8_t *)MAIN_CHECK_TIME,
        CHECKTIME,
    },
    {// check time
        (uint8_t *)MAIN_CHECK_ALARM,
        CHECKALARM,
    },
    {// check info
        (uint8_t *)MAIN_CHECK_INFO,
        INFO,
    },
    {// normal
        (uint8_t *)MAIN_NORMAL,
        NORMAL,
    }
};

struct_menu sub_time[MAX_SUBTIME] = 
{
    {// cai dat gio
        (uint8_t *)SUB_SET_TIME_HOUR,
        SETTIME_H,
    },
    {// cai dat phut
        (uint8_t *)SUB_SET_TIME_MIN,
        SETTIME_MIN,
    },
    {// cai dat ngay
        (uint8_t *)SUB_SET_TIME_DAY,
        SETTIME_D,
    },
    {// cai dat thang
        (uint8_t *)SUB_SET_TIME_MONTH,
        SETTIME_MON,
    },
    {// cai dat nam
        (uint8_t *)SUB_SET_TIME_YEAR,
        SETTIME_Y,
    }
};


void menu(void)
{
   time_out = 0;
    byte_input = 0;
   switch (kb_stt)
   {
      case NORMAL:
        kb_stt = SETTIME;
        LCD1_Clear();
        display_menu(SETTIME, 0, 1);
        break;
      case SETTIME:
        LCD1_Clear();
        kb_stt = SETTIME_H;
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
   }
}

void up_()
{
   time_out = 0;
   byte_input++;
   switch (kb_stt)
   {
      case SET_HVAL:
         if(byte_input>23)   byte_input = 0;
         break;
      case SET_MINVAL:
         if(byte_input>59)   byte_input = 0;
         break;
      case SET_DVAL:
         if(systime.MonthType == 3)
         {
            if(byte_input>31) byte_input=1;
         }
         else if(systime.MonthType == 2)
         {
            if(byte_input>30) byte_input=1;
         }
         else
         {
            if(systime.MonthType == 1)
               if(byte_input>29) byte_input=1;
            else
               if(byte_input>28) byte_input=1;
         }
         break;
      case SET_MONVAL:
         if(byte_input>12) byte_input = 1;
         break;
      case SET_YVAL:
         if(byte_input>100)  byte_input = 0;
         break;
      // chuyen menu cai dat cac gia tri thoi gian
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
      // chuyen menu chinh
      case SETTIME:
          display_menu(SETALARM, 0, 1);
         //LCD1_WriteString(main_menu[SETTIME].string);
         kb_stt = main_menu[SETALARM].next_menu;
         break;
      case SETALARM:
          display_menu(SETEFFECTS, 0, 1);
         //LCD1_WriteString(main_menu[SETALARM].string);
         kb_stt = main_menu[SETEFFECTS].next_menu;
         break;
      case SETEFFECTS:
          display_menu(CHECKTIME, 0, 1);
         //LCD1_WriteString(main_menu[SETEFFECTS].string);
         kb_stt = main_menu[CHECKTIME].next_menu;
         break;
      case CHECKTIME:
          display_menu(CHECKALARM, 0, 1);
         //LCD1_WriteString(main_menu[CHECKTIME].string);
         kb_stt = main_menu[CHECKALARM].next_menu;
         break;
      case CHECKALARM:
          display_menu(INFO, 0, 1);
         //LCD1_WriteString(main_menu[CHECKALARM].string);
         kb_stt = main_menu[INFO].next_menu;
         break;
      case INFO:
          display_menu(SETTIME, 0, 1);
         //LCD1_WriteString(main_menu[INFO].string);
         kb_stt = main_menu[SETTIME].next_menu;
         break;
   }
}

void down_()
{
    time_out = 0;  
    --byte_input;
    switch (kb_stt)
    {
        case SET_HVAL:
            if(byte_input<0)   byte_input = 23;
            break;
        case SET_MINVAL:
            if(byte_input<0)   byte_input = 59;
            break;
        case SET_DVAL:
            if(systime.MonthType == 3)
            {
                if(byte_input<=1) byte_input = 31;
            }
            else if(systime.MonthType == 2)
            {
                if(byte_input<=1) byte_input = 30;
            }
            else
            {
                if(systime.MonthType == 1)
                    if(byte_input<=1) byte_input = 29;
                else
                    if(byte_input<=1) byte_input = 28;
            }
            break;
        case SET_MONVAL:
            if(byte_input<1) byte_input = 12;
            break;
        case SET_YVAL:
            if(byte_input<0)  byte_input = 100;
            break;
      // chuyen menu cai dat cac gia tri thoi gian
      case SETTIME_H:
         kb_stt = SETTIME_Y;
         break;
      case SETTIME_MIN:
         kb_stt = SETTIME_H;
         break;
      case SETTIME_D:
         kb_stt = SETTIME_MIN;
         break;
      case SETTIME_MON:
         kb_stt = SETTIME_D;
         break;
      case SETTIME_Y:
         kb_stt = SETTIME_MON;
         break;
      // chuyen menu chinh
      case SETTIME:
          display_menu(INFO, 0, 1);
         //LCD1_WriteString(main_menu[SETTIME].string);
         kb_stt = main_menu[INFO].next_menu;
         break;
      case INFO:
          display_menu(CHECKALARM, 0, 1);
         //LCD1_WriteString(main_menu[INFO].string);
         kb_stt = main_menu[CHECKALARM].next_menu;
         break;
      case CHECKALARM:
          display_menu(CHECKTIME, 0, 1);
         //LCD1_WriteString(main_menu[CHECKALARM].string);
         kb_stt = main_menu[CHECKTIME].next_menu;
         break;
      case CHECKTIME:
          display_menu(SETEFFECTS, 0, 1);
         //LCD1_WriteString(main_menu[CHECKTIME].string);
         kb_stt = main_menu[SETEFFECTS].next_menu;
         break;
      case SETEFFECTS:
          display_menu(SETALARM, 0, 1);
         //LCD1_WriteString(main_menu[SETEFFECTS].string);
         kb_stt = main_menu[SETALARM].next_menu;
         break;
      case SETALARM:
          display_menu(SETTIME, 0, 1);
         //LCD1_WriteString(main_menu[SETALARM].string);
         kb_stt = main_menu[SETTIME].next_menu;
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
            TimeTemp.Hour = systime.Hour;
            byte_input = TimeTemp.Hour;
            kb_stt = SET_HVAL;
            break;
        case SETTIME_MIN:
            TimeTemp.Min = systime.Min;
            byte_input = TimeTemp.Min;
            kb_stt = SET_MINVAL;
            break;
        case SETTIME_D:
            TimeTemp.Day = systime.Day;
            byte_input = TimeTemp.Day;
            kb_stt = SET_DVAL;
            break;
        case SETTIME_MON:
            TimeTemp.Month = systime.Month;
            byte_input = TimeTemp.Month;
            kb_stt = SET_MONVAL;
            break;
        case SETTIME_Y:
            TimeTemp.Year = systime.Year;
            byte_input = TimeTemp.Year;
            kb_stt = SET_YVAL;
            break;
        case SET_HVAL:
            //SetTime(byte_input, systime.Hour);
            kb_stt = SETTIME_H;
            break;
        case SET_MINVAL:
            //SetTime(systime.Hour, byte_input);
            kb_stt = SETTIME_MIN;
            break;
        case SET_DVAL:
            //SetDate(byte_input, systime.Month, systime.Year);
            kb_stt = SETTIME_D;
            break;
        case SET_MONVAL:
            //SetDate(systime.Day, byte_input, systime.Year);
            kb_stt = SETTIME_MON;
            break;
        case SET_YVAL:
            //SetDate(systime.Day, systime.Month, byte_input);
            kb_stt = SETTIME_Y;
            break;

        case SETALARM:
            kb_stt = SETALARM_HON;
            break;
        case SETALARM_HON:
            kb_stt = SET_HVAL;
            break;
        case SETALARM_MON:
            kb_stt = SET_MINVAL;
            break;
        case SETALARM_HOFF:
            kb_stt = SET_HVAL;
            break;
        case SETALARM_MOFF:
            kb_stt = SET_MINVAL;
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
        case SETALARM:
        case SETEFFECTS:
        case CHECKTIME:
        case CHECKALARM:
        case INFO:
            kb_stt = NORMAL;
            break;
        case SETTIME_H:
        case SETTIME_MIN:
        case SETTIME_D:
        case SETTIME_MON:
        case SETTIME_Y:
            kb_stt = SETTIME;
            break;
        case SET_HVAL:
            kb_stt = SETTIME_H;
            break;
        case SET_MINVAL:
            kb_stt = SETTIME_MIN;
            break;
        case SET_DVAL:
            kb_stt = SETTIME_D;
            break;
        case SET_MONVAL:
            kb_stt = SETTIME_MON;
            break;
        case SET_YVAL:
            kb_stt = SETTIME_Y;
            break;
        
        case SETALARM_HON:
        case SETALARM_MON:
        case SETALARM_HOFF:
        case SETALARM_MOFF:
            kb_stt = SETALARM;
            break;
    }
}

//------------------------quet ban phim---------------------------------
void scan_key(void) // phim bam binh thuong o muc cao, khi nhan phim thi chuyen muc thap
{
    if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_SEL))
    {
        //LCD1_Clear();
        //LCD1_WriteLineStr(0, "Key selected");
        up_();
        Delay_ms(100);
    }
    if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_UP))
    {
        //LCD1_Clear();
        //LCD1_WriteLineStr(0, "Key Up");
        menu();
        Delay_ms(100);
    }
   if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_DOW))
   {
       down_();
       Delay_ms(100);
   }            
   if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_OK))
   {
       cancel_();
       Delay_ms(100);
   }
   if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_CAN))
   {
       ok_();
       Delay_ms(100);
   }
}
//----------------------hien thi trang thai--------------------------------
//-------- doan code khi bam menu
void state_dislay(void)
{
   uint8_t temp, chg = 0;
   if(kb_stt !=  NORMAL)
      time_out++;
   switch (kb_stt)
      {
         case NORMAL:
             LCD1_Line(0);
             LCD1_WriteString("___NORMAL___");
               break;
         case SETTIME:
               break;
         case SETTIME_H:
                display_subtime_menu(SETHVAL, systime.Hour);
                break;
         case SETTIME_MIN:
                display_subtime_menu(SETMINVAL, systime.Min);
                chg = 1;
                break;
         case SETTIME_D:
                display_subtime_menu(SETDVAL, systime.Day);
                chg = 1;
                break;
         case SETTIME_MON:
                display_subtime_menu(SETMONVAL, systime.Month);
                chg = 1;
                break;
         case SETTIME_Y:
                display_subtime_menu(SETYVAL, systime.Year);
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
               display_subtime_menu(SETHVAL, byte_input);
               chg = 1;
               break;
         case SET_MINVAL:
             display_subtime_menu(SETMINVAL, byte_input);
               chg = 1;
               break;
         case SET_DVAL:
             display_subtime_menu(SETDVAL, byte_input);
               chg = 1;
               break;
         case SET_MONVAL:
             display_subtime_menu(SETMONVAL, byte_input);
               chg = 1;
               break;
         case SET_YVAL:
             display_subtime_menu(SETYVAL, byte_input);
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
        kb_stt = NORMAL;
    }
}

void display_menu(uint8_t currpoint, uint8_t menu, uint8_t refresh)
{
    uint8_t i;
    if(!refresh)
        return;
    
    for(i = 0;i < 4;i++)
    {
        LCD1_Line(i);
        if(i == 0)
            LCD1_WriteString(">");
        else
            LCD1_WriteString(" ");
        LCD1_WriteString(main_menu[(i + currpoint)%7].string);
    }
}

void display_subtime_menu(uint8_t currpoint, uint8_t val)
{
    uint8_t i;
    uint8_t DataTemp[5];
    uint8_t * cursor[5] = 
    {
        " ^              ",
        "    ^           ",
        "       ^        ",
        "          ^     ",
        "             ^  "
    };
    uint8_t * cursor_info[5] = 
    {
        "1, DAT GIO      ",
        "2, DAT PHUT     ",
        "3, DAT NGAY     ",
        "4, DAT THANG    ",
        "5, DAT NAM      "
    };
    uint8_t * time_ptr;
    time_ptr = &systime.Hour;
    for(i = 0;i < 5;i++)
    {
        if(i == currpoint)
        {
            LCD1_Line(0);
            LCD1_WriteString(cursor_info[i]);
            LCD1_Line(2);
            LCD1_WriteString(cursor[i]);
            DataTemp[i] = val;
        }
        else
            DataTemp[i] = *(time_ptr++);
    }
    LCD1_Line(1);
    LCD1_DisplayInt(DataTemp[0]);
    LCD1_WriteString(":");
    LCD1_DisplayInt(DataTemp[1]);
    LCD1_WriteString(" ");
    LCD1_DisplayInt(DataTemp[2]);
    LCD1_WriteString("/");
    LCD1_DisplayInt(DataTemp[3]);
    LCD1_WriteString("/");
    LCD1_DisplayInt(DataTemp[4]);
    LCD1_WriteString("  ");
}
