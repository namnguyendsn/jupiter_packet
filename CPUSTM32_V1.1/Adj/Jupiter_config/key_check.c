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
uint8_t main_menu_curpoint;
int8_t alarm_curpoint = 0;
int8_t alarm_max_cur_num = 0;
int8_t alarm_type_val = 0;
bool alarmx_stt[MAX_ALARM_NUM] = {FALSE};

extern Time_s systime;
extern uint8_t * alarm_data_ptr;
extern uint32_t * alarm_data_array_ptr;
extern void write_alarm_menu(uint8_t * array_ptr, uint8_t size);
extern void display_menu(uint8_t currpoint, uint8_t menu, uint8_t refresh);
extern void display_subtime_menu(uint8_t currpoint, uint8_t val, bool only);
extern void display_alarm_set(uint8_t currpoint, uint8_t alarm, uint8_t refresh);
extern void display_alarm_menu(uint8_t currpoint, uint8_t val, bool only);

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
            kb_stt = SETALARM_NUM;
            LCD1_Clear();
        break;
        case SETALARMx:
            LCD1_Clear();
            kb_stt = SETALARMx_VAL;
            break;
        case SETALARMx_VAL:
            display_alarm_menu(alarm_type_val, 0, 1);
            switch(alarm_type_val)
            {
                case 0:
                    kb_stt = SETALARMx_HON_VAL;
                    alarm_type_val = 0;
                    break;
                case 1:
                    kb_stt = SETALARMx_MON_VAL;
                    alarm_type_val = 1;
                    break;
                case 2:
                    kb_stt = SETALARMx_ONTIME_VAL;
                    alarm_type_val = 2;
                    break;
            }
            break;
        case SETEFFECTS:

        break;
        case CHECKTIME:

        break;
        case CHECKALARM:

        break;
        case INFO:
            kb_stt = VIEW_INFO;
        break;

        case SETTIME_H:
            kb_stt = SET_HVAL;
            byte_input = systime.Hour;
        break;
        case SETTIME_MIN:
            kb_stt = SET_MINVAL;
            byte_input = systime.Min;
        break;
        case SETTIME_D:
            kb_stt = SET_DVAL;
            byte_input = systime.Day;
        break;
        case SETTIME_MON:
            kb_stt = SET_MONVAL;
            byte_input = systime.Month;
        break;
        case SETTIME_Y:
            kb_stt = SET_YVAL;
            byte_input = systime.Year;
        break;
   }
}

void up_(void)
{
    time_out = 0;
    if(kb_stt == SETALARMx_ONTIME_VAL)
        byte_input = byte_input + 10;
    else
        byte_input++;
    switch (kb_stt)
    {
		case SETALARMx_HON_VAL:
        case SET_HVAL:
            if(byte_input>23)   byte_input = 0;
        break;
        case SETALARMx_MON_VAL:
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
            main_menu_curpoint = SETALARM;
        break;
        case SETALARM:
            display_menu(SETEFFECTS, 0, 1);
            //LCD1_WriteString(main_menu[SETALARM].string);
            kb_stt = main_menu[SETEFFECTS].next_menu;
            main_menu_curpoint = SETEFFECTS;
        break;
		case SETALARMx:
			alarm_curpoint++;
			if(alarm_curpoint >= alarm_max_cur_num)   alarm_curpoint = 0;
			break;
		case SETALARMx_VAL:
			alarm_type_val++;
			if(alarm_type_val >= 3)   alarm_type_val = 0;
			break;
		case SETALARMx_ONTIME_VAL:
			if(byte_input > 1440)   byte_input = 0;
			break;
        case SETALARM_NUM:
			if(byte_input > MAX_ALARM_NUM)   byte_input = 0;
            break;
        case SETEFFECTS:
        display_menu(CHECKTIME, 0, 1);
            //LCD1_WriteString(main_menu[SETEFFECTS].string);
            kb_stt = main_menu[CHECKTIME].next_menu;
            main_menu_curpoint = CHECKTIME;
        break;
        case CHECKTIME:
            display_menu(CHECKALARM, 0, 1);
            //LCD1_WriteString(main_menu[CHECKTIME].string);
            kb_stt = main_menu[CHECKALARM].next_menu;
            main_menu_curpoint = CHECKALARM;
           break;
        case CHECKALARM:
            display_menu(INFO, 0, 1);
            //LCD1_WriteString(main_menu[CHECKALARM].string);
            kb_stt = main_menu[INFO].next_menu;
            main_menu_curpoint = INFO;
        break;
        case INFO:
            display_menu(SETTIME, 0, 1);
            //LCD1_WriteString(main_menu[INFO].string);
            kb_stt = main_menu[SETTIME].next_menu;
            main_menu_curpoint = SETTIME;
        break;
   }
}

void down_(void)
{
  time_out = 0;
    if(kb_stt == SETALARMx_ONTIME_VAL)
        byte_input = byte_input - 10;
    else
        --byte_input;
	switch (kb_stt)
	{
		case SETALARMx_HON_VAL:
		case SET_HVAL:
			if(byte_input<0)   byte_input = 23;
			break;
		case SETALARMx_MON_VAL:
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
			main_menu_curpoint = INFO;
			break;
		case INFO:
			display_menu(CHECKALARM, 0, 1);
			//LCD1_WriteString(main_menu[INFO].string);
			kb_stt = main_menu[CHECKALARM].next_menu;
			main_menu_curpoint = CHECKALARM;
			break;
		case CHECKALARM:
			display_menu(CHECKTIME, 0, 1);
			//LCD1_WriteString(main_menu[CHECKALARM].string);
			kb_stt = main_menu[CHECKTIME].next_menu;
			main_menu_curpoint = CHECKTIME;
			break;
		case CHECKTIME:
			display_menu(SETEFFECTS, 0, 1);
			//LCD1_WriteString(main_menu[CHECKTIME].string);
			kb_stt = main_menu[SETEFFECTS].next_menu;
			main_menu_curpoint = SETEFFECTS;
			break;
		case SETEFFECTS:
			display_menu(SETALARM, 0, 1);
			//LCD1_WriteString(main_menu[SETEFFECTS].string);
			kb_stt = main_menu[SETALARM].next_menu;
			main_menu_curpoint = SETALARM;
			break;
		case SETALARM:
			display_menu(SETTIME, 0, 1);
			//LCD1_WriteString(main_menu[SETALARM].string);
			kb_stt = main_menu[SETTIME].next_menu;
			main_menu_curpoint = SETTIME;
			break;
		case SETALARMx:
			alarm_curpoint--;
			if(alarm_curpoint < 0)   alarm_curpoint = alarm_max_cur_num - 1;
			break;
		case SETALARMx_VAL:
			alarm_type_val--;
			if(alarm_type_val < 0)   alarm_type_val = 3 - 1;
			break;
		case SETALARMx_ONTIME_VAL:
			if(byte_input < 0)   byte_input = 1440;
			break;
        case SETALARM_NUM:
            if(byte_input < 0)   byte_input = MAX_ALARM_NUM;
            break;
    }
}

void ok_(void)
{
    uint8_t index;
    time_out = 0;
    switch (kb_stt)
    {
        case SETTIME:
            kb_stt = NORMAL;
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
        case SET_HVAL:
            SetTime(byte_input, systime.Hour);
            kb_stt = SETTIME_H;
            break;
        case SET_MINVAL:
            SetTime(systime.Hour, byte_input);
            kb_stt = SETTIME_MIN;
            break;
        case SET_DVAL:
            SetDate(byte_input, systime.Month, systime.Year);
            systime.Day = byte_input;
            kb_stt = SETTIME_D;
            break;
        case SET_MONVAL:
            SetDate(systime.Day, byte_input, systime.Year);
            kb_stt = SETTIME_MON;
            systime.Month = byte_input;
            break;
        case SET_YVAL:
            SetDate(systime.Day, systime.Month, byte_input);
            kb_stt = SETTIME_Y;
            systime.Year = byte_input;
            break;

        case SETALARM:
            kb_stt = NORMAL;
            break;

        case SETALARMx:
            kb_stt = SETALARM;
            main_menu_curpoint = SETALARM;
            // write alarm data vao flash
            for(index = 0; index < alarm_max_cur_num; index++)
            {
                if(alarmx_stt[index] == FALSE)
                    return;
            }
            write_alarm_menu((uint8_t *)alarm_data_array_ptr, alarm_curpoint + 1);
            break;
        case SETALARMx_VAL:
            LCD1_Clear();            
            kb_stt = SETALARMx;
            break;
        case SETALARMx_HON_VAL:
            ((ALARM_STRUCT_CLONE*)alarm_data_array_ptr)[alarm_curpoint].on_hour =  (uint8_t)byte_input;
            kb_stt = SETALARMx_VAL;
            alarmx_stt[alarm_curpoint] = TRUE;
            break;
        case SETALARMx_MON_VAL:
            ((ALARM_STRUCT_CLONE*)alarm_data_array_ptr)[alarm_curpoint].on_min =  (uint8_t)byte_input;
            kb_stt = SETALARMx_VAL;
            alarmx_stt[alarm_curpoint] = TRUE;
            break;
        case SETALARMx_ONTIME_VAL:
            ((ALARM_STRUCT_CLONE*)alarm_data_array_ptr)[alarm_curpoint].on_time =  SWAP2BYTE(byte_input/5);
            kb_stt = SETALARMx_VAL;
            alarmx_stt[alarm_curpoint] = TRUE;
            break;
        case SETALARM_NUM:
            LCD1_Clear();
            if(byte_input == 0)
                return;
            alarm_max_cur_num = byte_input;
            kb_stt = SETALARMx;
            break;
        case SETEFFECTS:
            break;
        case CHECKTIME:

            break;
        case CHECKALARM:
            break;

        case VIEW_INFO:
            kb_stt = INFO;
            main_menu_curpoint = INFO;
            break;
    }
}

void cancel_(void)
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
		
		case SETALARMx_HON_VAL:
		case SETALARMx_MON_VAL:
		case SETALARMx_ONTIME_VAL:
			kb_stt = SETALARMx_VAL;
			break;
		case VIEW_INFO:
			kb_stt = INFO;
			main_menu_curpoint = INFO;
		
		case SETALARMx:
			kb_stt = SETALARM;
			main_menu_curpoint = SETALARM;
			break;
		case SETALARMx_VAL:
            LCD1_Clear();
			kb_stt = SETALARMx;
			break;
        case SETALARM_NUM:
			kb_stt = SETALARM;
            break;
	}
}

//------------------------quet ban phim---------------------------------
void scan_key(void) // phim bam binh thuong o muc cao, khi nhan phim thi chuyen muc thap
{
    if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_SEL))
    {
        up_();
        Delay_ms(100);
    }
    if(!GPIO_ReadInputDataBit(KEY_PORT, KEY_UP))
    {
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
            LCD1_Clear();
            break;
        case SETALARM:
        case SETTIME:
        case INFO:
            display_menu(main_menu_curpoint, 0, 1);
            break;
        case SETTIME_H:
            display_subtime_menu(SETHVAL, systime.Hour, 0);
            break;
        case SETTIME_MIN:
            display_subtime_menu(SETMINVAL, systime.Min, 0);
            chg = 1;
            break;
        case SETTIME_D:
            display_subtime_menu(SETDVAL, systime.Day, 0);
            chg = 1;
            break;
        case SETTIME_MON:
            display_subtime_menu(SETMONVAL, systime.Month, 0);
            chg = 1;
            break;
        case SETTIME_Y:
            display_subtime_menu(SETYVAL, systime.Year, 0);
            chg = 1;
            break;
        case SETALARMx_HON_VAL:
            display_alarm_menu(alarm_type_val,byte_input , 1);
            chg = 1;
            break;
        case SETALARMx_MON_VAL:
            display_alarm_menu(alarm_type_val,byte_input , 1);
            chg = 1;
            break;
        case SETALARMx_ONTIME_VAL:
            display_alarm_menu(alarm_type_val,byte_input , 1);
            chg = 1;
            break;
        case SET_HVAL:
            display_subtime_menu(SETHVAL, byte_input, 1);
            chg = 1;
            break;
        case SET_MINVAL:
            display_subtime_menu(SETMINVAL, byte_input, 1);
            chg = 1;
            break;
        case SET_DVAL:
            display_subtime_menu(SETDVAL, byte_input, 1);
            chg = 1;
            break;
        case SET_MONVAL:
            display_subtime_menu(SETMONVAL, byte_input, 1);
            chg = 1;
            break;
        case SET_YVAL:
            display_subtime_menu(SETYVAL, byte_input, 1);
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
        case VIEW_INFO:
            INFO_DISPLAY;
            break;
        case SETALARM_NUM:
            LCD1_Line(0);
            LCD1_WriteString("SO LAN BAT/TAT  ");
            LCD1_Line(1);
            LCD1_DisplayInt(byte_input, 2);
            break;
        case SETALARMx:
            display_alarm_set(alarm_curpoint, alarm_max_cur_num, 1);
            break;
        case SETALARMx_VAL:
            display_alarm_menu(alarm_type_val, 0, 0);
            break;
    }
    if(chg  ==  1)
    {
        chg = 0;
    }
    if(time_out > 1000)//reset time_out;
    {
        time_out = 0;
        kb_stt = NORMAL;
    }
}
