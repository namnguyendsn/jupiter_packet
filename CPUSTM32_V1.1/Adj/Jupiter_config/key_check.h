#include "jupiter_gpio.h"
#include "timer_delay.h"
#include "LCD1.h"
/*=======================
phim 1: MENU
phim 2: OK
phim 3: UP
phim 4: DOWN
phim 5: EXIT
=========================*/

typedef enum{
   normal,
   xemngay,
   xemnhietdo,
   chinhgio_value,
   chinhphut_value,
   chinhngay_value,
   chinhthang_value,
   chinhnam_value,
   chinhthu_value
}key_state;

void menu(void);
void scan_key(void);
