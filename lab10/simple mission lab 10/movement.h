#include "lcd.h"
#include "open_interface.h"
#include "Timer.h"
#include <stdio.h>
#include "uart_extra_help.h"

//volatile  char uart_data;  // Your UART interupt code can place read data here
//volatile  char flag;       // Your UART interupt can update this flag
void move_forward(oi_t *sensor, int centimeters);
void move_backwards(oi_t *sensor, int millimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void turn_cclockwise(oi_t *sensor, int degrees);
void move_forward_go_around(oi_t *sensor, int millimeters);
//
//void move_forward(oi_t *sensor, int centimeters) {
//    double sum = 0;
//    oi_setWheels(250, 250); // move forward; full speed
//    while (sum < centimeters*10) {
//    oi_update(sensor);
//    sum += sensor->distance;
//
//    if(flag)
//            {
//                flag = 0;
//                if((char)uart_data == 't')
//                {
//                    break;
//                }
//            }
//    }
//    oi_setWheels(0, 0); // stop
//}
//
double move_backward(oi_t *sensor, int centimeters) {
    double sum = 0;
    oi_setWheels(-250, -250); // move forward; full speed
    while (abs(sum) < centimeters*10) {
    oi_update(sensor);
    sum += sensor->distance;

    if(flag)
            {
                flag = 0;
                if((char)uart_data == 't')
                {
                    break;
                }
            }
    }
    oi_setWheels(0, 0); // stop
    return sum;
}
//
//void turn_clockwise(oi_t *sensor, float degrees) {
//    double sum = 0;
//    oi_setWheels(-100, 100); //Turn bot clockwise
//    while (sum < abs(degrees)) {
//        oi_update(sensor);
//        sum += abs(sensor->angle);
//
//        if(flag)
//                {
//                    flag = 0;
//                    if((char)uart_data == 't')
//                    {
//                        break;
//                    }
//                }
//
//    }
//    oi_setWheels(0,0); //stop
//}
//
void turn_counterclockwise(oi_t *sensor, float degrees) {
    double sum = 0;
    oi_setWheels(100, -100); //Turn bot clockwise
    while (sum < abs(degrees)) {
        oi_update(sensor);
        sum += abs(sensor->angle);

        if(flag)
                {
                    flag = 0;
                    if((char)uart_data == 't')
                    {
                        break;
                    }
                }

    }
    oi_setWheels(0,0); //stop
}
//
double move_until_bump(oi_t *sensor, int max_cm)
{
    double dist_travelled = 0;
    oi_setWheels(150, 150); // move forward; full speed

    while(!sensor->bumpLeft && !sensor->bumpRight && abs(dist_travelled) < max_cm)
    {
        oi_update(sensor);
        dist_travelled += sensor->distance/10.0;

        if(flag)
        {
            flag = 0;
            if((char)uart_data == 't')
            {
                break;
            }
        }

        if(sensor->bumpLeft)
            uart_sendChar('L');

        if(sensor->bumpRight)
            uart_sendChar('R');



    }
    oi_setWheels(0, 0);
    return dist_travelled;
}

bool hasBumpedLeft(oi_t *sensor)
{
    return sensor->bumpLeft;
}

bool hasBumpedRight(oi_t *sensor)
{
    return sensor->bumpRight;
}
