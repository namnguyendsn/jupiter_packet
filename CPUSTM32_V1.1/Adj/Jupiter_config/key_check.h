#include "jupiter_gpio.h"
#include "timer_delay.h"
#include "LCD1.h"
#include "menuDefine.h"
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

    SETALARM_HON,
    SETALARM_MON,
    SETALARM_HOFF,
    SETALARM_MOFF,
    SETALARM_HON_VAL,
    SETALARM_MON_VAL,
    SETALARM_HOFF_VAL,
    SETALARM_MOFF_VAL,
    
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

    SETEFFECTS_SELECT
}menu_state;

typedef struct
{
    uint8_t * string;
    menu_state next_menu;
} struct_menu;

void menu(void);
void scan_key(void);
