#include "movement.h"
#include "open_interface.h"

void move_forward(oi_t *sensor, int millimeters){

     double sum = 0;
     oi_setWheels(250, 250); // move forward; full speed

     while (sum < millimeters) {
     oi_update(sensor);
     sum += sensor->distance;
     if(sensor->bumpLeft){
         move_backwards(sensor, 150);
         sum -= 30;
         turn_clockwise(sensor, 250);
         move_forward(sensor, 200);
         turn_cclockwise(sensor, 350);
         oi_setWheels(250,250);
         }
     if(sensor->bumpRight){
         move_backwards(sensor, 150);
         sum -= 30;
         turn_cclockwise(sensor, 250);
         move_forward(sensor,200);
         turn_clockwise(sensor, 250);
         oi_setWheels(250,250);
         }
     }
     oi_setWheels(0, 0); // stop
}

void move_forward_go_around(oi_t *sensor, int millimeters){

     double sum = 0;
     oi_setWheels(250, 250); // move forward; full speed

     while (sum < millimeters) {
     oi_update(sensor);
     sum += sensor->distance;
     if(sensor->bumpLeft){
         move_backwards(sensor, 150);
         sum -= 10;
         turn_clockwise(sensor, 300);
         move_forward(sensor, 100);
         turn_cclockwise(sensor, 250);
         move_forward(sensor, 450);
         turn_cclockwise(sensor, 250);
         oi_setWheels(150, 150);
         }
     if(sensor->bumpRight){
         move_backwards(sensor, 150);
         sum -= 10;
         turn_cclockwise(sensor, 300);
         move_forward(sensor,100);
         turn_clockwise(sensor, 250);
         move_forward(sensor, 450);
         turn_clockwise(sensor, 250);
         oi_setWheels(150, 150);
         }
     }
     oi_setWheels(0, 0); // stop
}
void move_backwards(oi_t *sensor, int millimeters){

     double sum = 0;
     oi_setWheels(-250, -250); // move back; full speed

     while (sum > -millimeters) {
     oi_update(sensor);
     sum += sensor->distance;
     }
     oi_setWheels(0, 0); // stop
}

void turn_clockwise(oi_t *sensor, int degrees){

    double angle = 0;
    oi_setWheels(-250, 250);
    while (angle > -degrees) {
    oi_update(sensor);
    angle += (sensor->angle / 0.324056);
    }
    oi_setWheels(0, 0); // stop
}
void turn_cclockwise(oi_t *sensor, int degrees){

    double angle = 0;
    oi_setWheels(250, -250);
    while (angle < degrees) {
    oi_update(sensor);
    angle += (sensor->angle / 0.324056);
    }
    oi_setWheels(0, 0); // stop
}
