#include "jupiter_gpio.h"
#include "timer_delay.h"
#include "LCD1.h"
#include "menuDefine.h"

#define MAX_ALARM_NUM 22

/*=======================
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
=========================*/
typedef enum{
    SETTIME = 0,
    SETALARM,
    SETEFFECTS,
    CHECKTIME,
    CHECKALARM,
    INFO,
    NORMAL,

    SETTIME_H,
    SETTIME_MIN,
    SETTIME_D,
    SETTIME_MON,
    SETTIME_Y,

    SETALARMx_HON_VAL,
    SETALARMx_MON_VAL,
    SETALARMx_ONTIME_VAL,
    
    SET_HVAL,
    #define SETHVAL     0
    SET_MINVAL,
    #define SETMINVAL   1
    SET_DVAL,
    #define SETDVAL     2
    SET_MONVAL,
    #define SETMONVAL   3
    SET_YVAL,
    #define SETYVAL     4

    SETEFFECTS_SELECT,
	
	VIEW_INFO,
	SETALARMx,
	SETALARMx_VAL,
}menu_state;

typedef struct
{
    uint8_t * string;
    menu_state next_menu;
} struct_menu;

typedef struct 
{
  uint8_t on_hour;
  uint8_t on_min;
  uint16_t on_time;
}ALARM_STRUCT_CLONE;

void menu(void);
void scan_key(void);
