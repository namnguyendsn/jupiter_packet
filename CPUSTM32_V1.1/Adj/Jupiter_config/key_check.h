#include "jupiter_gpio.h"
#include "timer_delay.h"
#include "LCD1.h"
#include "jupiter_rtc.h"
#include "menuDefine.h"
/*=======================
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
=========================*/
typedef enum{
    SETTIME,
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
    SET_MINVAL,
    SET_DVAL,
    SET_MONVAL,
    SET_YVAL,

    SETEFFECTS_SELECT
}menu_state;

typedef struct
{
    uint8_t const * string;
    menu_state next_menu;
} struct_menu;

void menu(void);
void scan_key(void);
