#include "cyBot_Scan.h"
//#include "cyBot_uart.h"
#include "Timer.h"
#include "lcd.h"
#include <math.h>
#include "open_interface.h"
#include "movement.h"
#include "uart_extra_help.h"




int main(void)
{
    timer_init();
       lcd_init();
       lcd_putc('a');

       oi_t *sensor_data = oi_alloc();
       oi_init(sensor_data);
       uart_init();
       lcd_putc('b');

       timer_waitMillis(10000);
    move_forward_go_around(sensor_data, 1000);

}
