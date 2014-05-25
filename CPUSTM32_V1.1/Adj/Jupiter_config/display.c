#include "key_check.h"
#include "jupiter_rtc.h"

extern Time_s systime;
extern uint8_t * alarm_data_ptr;
extern void write_alarm_menu(uint8_t * array_ptr, uint8_t size);
extern struct_menu main_menu[MAX_MENU];
void display_menu(uint8_t currpoint, uint8_t menu, uint8_t refresh);
void display_subtime_menu(uint8_t currpoint, uint8_t val, bool only);
void display_alarm_set(uint8_t currpoint, uint8_t alarm, uint8_t refresh);
void display_alarm_menu(uint8_t currpoint, uint8_t val, bool only);
void display_alarm_set_load(uint8_t currpoint, uint8_t alarm);

struct_menu alarm_set_load_array[2] = 
{
    {// load alarm
        (uint8_t *)ALARM_LOADFLASH,
        0,
    },
    {// set alarm
        (uint8_t *)ALARM_CREATNEW,
        0,
    }
};

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

void display_subtime_menu(uint8_t currpoint, uint8_t val, bool only)
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
    uint8_t * separate_info[5] = 
    {
        ":",
        " ",
        "/",
        "/",
        " "
    };
    uint8_t * time_ptr;
    time_ptr = &systime.Hour;
    for(i = 0;i < 5;i++)
    {
        //time_ptr++;
        if(i == currpoint)
        {
            LCD1_Line(0);
            LCD1_WriteString(cursor_info[i]);
            LCD1_Line(2);
            LCD1_WriteString(cursor[i]);
            DataTemp[i] = val;
        }
        else
            DataTemp[i] = time_ptr[i];
    }
    LCD1_Line(1);
		for(i = 0; i < 5; i++)
		{
			if(only == TRUE)
			{
				if(currpoint == i)
				{
					LCD1_DisplayInt(DataTemp[i], 2);
					LCD1_WriteString(separate_info[i]);
				}
				else
				{
					LCD1_WriteString("  ");
					LCD1_WriteString(separate_info[i]);
				}
			}
			else
			{
				LCD1_DisplayInt(DataTemp[i], 2);
				LCD1_WriteString(separate_info[i]);
			}
		}
}
/*
currpoint: vi tri hien tai cua con tro
alarm: so luong alarm
*/
void display_alarm_set(uint8_t currpoint, uint8_t alarm, uint8_t refresh)
{
    uint8_t i;
    if(!refresh)
        return;
    for(i = 0; \
        alarm >= 4 ? i < 4: i < alarm; \
        i++)
    {
        LCD1_Line(i);
        if(i == 0)
            LCD1_WriteString(">");
        else
            LCD1_WriteString(" ");
        LCD1_WriteString("ALARM ");
        LCD1_DisplayInt((i + currpoint) % alarm, 2);
    }
}

void display_alarm_menu(uint8_t currpoint, uint8_t val, bool only)
{
    uint8_t i;
    uint8_t DataTemp[4];
    uint8_t * cursor[4] = 
    {
        " ^              ",
        "    ^           ",
        "         ^      "
    };
    uint8_t * cursor_info[4] = 
    {
        "1, GIO BAT      ",
        "2, PHUT BAT     ",
        "3, THOI GIAN BAT"
    };

    uint8_t * separate_info[4] = 
    {
			":",
			":",
			" "
    };
    uint8_t * time_ptr;
    time_ptr = alarm_data_ptr; // get alarm data pointer
    for(i = 0;i < 3;i++)
    {
			//time_ptr++;
        if(i == currpoint)
        {
            LCD1_Line(0);
            LCD1_WriteString(cursor_info[i]);
            LCD1_Line(2);
            LCD1_WriteString(cursor[i]);
            DataTemp[i] = val;
        }
        else
            DataTemp[i] = time_ptr[i];
    }
    LCD1_Line(1);
    for(i = 0; i < 3; i++)
    {
        if(only == TRUE)
        {
            if(currpoint == i)
            {
                if(i == 2)
                    LCD1_DisplayInt(DataTemp[i], 4);
                else
                    LCD1_DisplayInt(DataTemp[i], 2);
                LCD1_WriteString(separate_info[i]);
            }
            else
            {
                LCD1_WriteString("  ");
                LCD1_WriteString(separate_info[i]);
            }
        }
        else
        {
            if(i == 2)
                LCD1_DisplayInt(DataTemp[i], 4);
            else
                LCD1_DisplayInt(DataTemp[i], 2);
            LCD1_WriteString(separate_info[i]);
        }
    }
}

void display_alarm_set_load(uint8_t currpoint, uint8_t alarm)
{
    uint8_t i;
    if((currpoint >= 2)||(alarm > 2))
        return;
    for(i = 0; \
        alarm >= 4 ? i < 4: i < alarm; \
        i++)
    {
        LCD1_Line(i);
        if(i == 0)
            LCD1_WriteString(">");
        else
            LCD1_WriteString(" ");
        LCD1_WriteString(alarm_set_load_array[(i + currpoint)%2].string);
    }
}
