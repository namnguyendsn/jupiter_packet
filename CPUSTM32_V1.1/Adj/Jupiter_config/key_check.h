#include "jupiter_gpio.h"
#include "timer_delay.h"
#include "LCD1.h"
#include "menuDefine.h"

#define MAX_ALARM_NUM 22
#define SWAP2BYTE(n)    ((n >> 8) | (n << 8))
#define INFO_DISPLAY \
                LCD1_Line(0); \
                LCD1_WriteString("LED DRIVER V1.2"); \
                LCD1_Line(1); \
                LCD1_WriteString("LED SIGN ADJ"); \
                LCD1_Line(2); \
                LCD1_WriteString("SDT 0974062446"); \
                LCD1_Line(3); \
                LCD1_WriteString("LET'S TRY MORE")
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
    SETALARM_NUM,
    ALARM_CREATNEW,// tao moi alarm neu ko co san
    ALARM_FROMFLASH// load tu flash
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
