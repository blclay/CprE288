#include "open_interface.h"
#include "Timer.h"
//#include "cyBot_Scan.h"
#include <stdio.h>
#include <math.h>
#include "movement.h"
#include "uart_extra_help.h"
#include "adc.h"
#include "servo.h"
#include "ping.h"
#include <stdio.h>
#include <stdlib.h>
#include "Timer.h"
#include "servo.h"
#include "lcd.h"
#include "button.h"
#include <inc/tm4c123gh6pm.h>


int main()
{
    timer_init();
    lcd_init();
    lcd_putc('a');

    oi_t *sensor_data = oi_alloc();
    lcd_putc('d');
    oi_init_noupdate();
    //oi_init(sensor_data);
    lcd_putc('c');
    uart_init();
    lcd_putc('b');

    adc_init();
    servo_init();
    ping_init();

 /*   servo_move(90);
    int n;

    uart_sendChar('R');
    for(n=0; n < 75; n++)
    {
        char adcvals[100] = "";
        uart_sendChar('m');
        timer_waitMillis(7500);
        int j = adc_read();
        sprintf(adcvals, "%d", j);
        uart_sendString(adcvals);
        uart_sendChar('\n');
    }
*/
    //cyBOT_init_Scan(0b0111);
//
//        right_calibration_value = 17500;
//        left_calibration_value = 1335250;

            lcd_putc('c');

            int previousScan = 1;

            int objectStartDegree;
            int objectEndDegree;
            char angle[4];
            char distance[4];
            char width[4];
            int shortestObjectIndex = 0;
            char linearWidth[4];
            typedef struct{
                int degree;
                int distance;
                int width;
                int linearWidth;
            }Object;
            Object objectList[4];
               int objectCount = 0;
               // YOUR CODE HERE
               char scanval[5];
               int i = 0;
               char pingScan[5];
               char degre[3];
               int previousPingScan = 0;
               char calculatedDistance[5];
               int deg;
               char readVal;
               int toggle = 0;
               cyBOT_Scan_t scan;
               cyBOT_Scan_t tempscan;
               uart_sendChar('h');
               uart_receive();
               while(1){
                   readVal = uart_receive();
                   uart_sendChar(readVal);
                   if (readVal == 't')
                   {
                       if (toggle == 0)
                       {
                           toggle = 1;
                       }
                       else if (toggle == 1)
                       {
                           toggle = 0;
                       }
                   }
                   if(readVal == 'h' && toggle == 0){
                       objectCount = 0;
                       for(deg = 0; deg <= 180; deg += 2){
                           if((char)(UART1_DR_R & 0xFF) == 't'){
                               for( i = 0; i < 20; i ++){
                                   uart_sendChar('-');
                               }
                               uart_sendChar('\n');
                               uart_sendChar('\r');
                               toggle = 1;
                               break;
                           }
                           //cyBOT_Scan(deg, &scan);
                           int objectCount = 0;
                           servo_move(deg);
                           timer_waitMillis(200);
                           scan.sound_dist = ping_getDistance();

                           lcd_clear();


                           sprintf(scanval, "%d", (adc_read()+previousScan)/2);


                           sprintf(pingScan, "%f", (scan.sound_dist+previousPingScan)/2);

                           sprintf(degre, "%d", deg);
                           for(i = 0; i< 3; i++){
                               uart_sendChar(degre[i]);
                           }
                           uart_sendChar(',');
                           uart_sendChar(' ');
                           for(i = 0; i< 5; i++){
                               uart_sendChar(scanval[i]);
                           }
                           uart_sendChar(',');
                           uart_sendChar(' ');
                           for(i = 0; i< 5; i++){
                               uart_sendChar(pingScan[i]);
                           }

                           float Stock = pow( ((adc_read()+previousScan)/2.0), -1.406);
                           float Ham = 688283 * Stock;

                           float calculatedIRVAL = 688283 * pow(adc_read(), -1.406);
                           float calculatedPREVIOUSVAL = 688283 * pow(previousScan, -1.406);

                           sprintf(calculatedDistance, "%f", calculatedIRVAL);
                           uart_sendChar(',');
                           uart_sendChar(' ');
                           for(i = 0; i< 5; i++){
                               uart_sendChar(calculatedDistance[i]);

                           }



                           if(calculatedIRVAL - calculatedPREVIOUSVAL < -35){
                                       //Start object
                                       objectStartDegree = deg;
                                       uart_sendChar('\n');
                                       uart_sendChar('\r');
                                       uart_sendChar('s');
                                       lcd_putc('s');
                                   }
                           if(calculatedPREVIOUSVAL - calculatedIRVAL < -35){
                               //end object
                               objectEndDegree = deg;

                               if(objectEndDegree-objectStartDegree > 9){
                              //     if(((objectEndDegree+objectStartDegree)/2) > (objectList[objectCount--].degree + 3)){
                                       //object is valid
                                       uart_sendChar('\n');
                                       uart_sendChar('\r');
                                       uart_sendChar('o');
                                       uart_sendChar('b');
                                       uart_sendChar('j');
                                       uart_sendChar('\n');
                                       uart_sendChar('\r');
                                       lcd_clear();
                                       //save object
                                       objectList[objectCount].degree = (objectEndDegree + objectStartDegree )/ 2;
                    //                   cyBOT_Scan(objectList[objectCount].degree, &tempscan);
                    //                   objectList[objectCount].distance = tempscan.sound_dist;
                                       objectList[objectCount].distance = scan.sound_dist;
                                       objectList[objectCount].linearWidth = abs(2*((sin((objectEndDegree - objectStartDegree)/2))*objectList[objectCount].distance));
                                       objectList[objectCount].width = objectEndDegree-objectStartDegree;

                                       objectCount++;
                             //      }
                               }

                           }

                           previousScan = adc_read();
                           previousPingScan = scan.sound_dist;


                           uart_sendChar('\n');
                           uart_sendChar('\r');
                       }

                       uart_sendChar('O');
                       uart_sendChar('b');
                       uart_sendChar('j');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar('A');
                       uart_sendChar('n');
                       uart_sendChar('g');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar('D');
                       uart_sendChar('i');
                       uart_sendChar('s');
                       uart_sendChar('t');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar('W');
                       uart_sendChar('i');
                       uart_sendChar('d');
                       uart_sendChar('t');
                       uart_sendChar('h');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar(' ');
                       uart_sendChar('L');
                       uart_sendChar('W');
                       uart_sendChar('i');
                       uart_sendChar('d');
                       uart_sendChar('t');
                       uart_sendChar('h');
                       uart_sendChar('\n');
                       uart_sendChar('\r');
                       for(i = 0; i < objectCount; i ++){
                           uart_sendChar(i + 48);
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           sprintf(angle, " %d", objectList[i].degree);
                           sprintf(distance, " %d", objectList[i].distance);
                           sprintf(width, " %d", objectList[i].width);
                           sprintf(linearWidth, " %d", objectList[i].linearWidth);
                           uart_sendChar(angle[0]);
                           uart_sendChar(angle[1]);
                           uart_sendChar(angle[2]);
                           uart_sendChar(angle[3]);
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(distance[0]);
                           uart_sendChar(distance[1]);
                           uart_sendChar(distance[2]);
                           uart_sendChar(distance[3]);
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(width[0]);
                           uart_sendChar(width[1]);
                           uart_sendChar(width[2]);
                           uart_sendChar(width[3]);
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(linearWidth[0]);
                           uart_sendChar(linearWidth[1]);
                           uart_sendChar(linearWidth[2]);
                           uart_sendChar(linearWidth[3]);
                           uart_sendChar('\n');
                           uart_sendChar('\r');

                       }


                       int shortestWidth = objectList[0].width;
                       int shortestObjectIndex = 0;
                       for(i = 0; i < objectCount; i ++){


                           if(objectList[i].width < shortestWidth){
                               shortestWidth = objectList[i].width;
                               shortestObjectIndex = i;
                           }
                       }

                       timer_waitMillis(500);
                       //cyBOT_Scan(objectList[shortestObjectIndex].degree, &tempscan);
                       servo_move(objectList[shortestObjectIndex].degree);
                       tempscan.sound_dist = ping_getDistance();
                       objectList[shortestObjectIndex].distance = tempscan.sound_dist;
                       timer_waitMillis(200);

                       uart_sendChar('\n');
                       uart_sendChar('\r');
                       sprintf(angle, " %d", objectList[shortestObjectIndex].degree);
                       uart_sendChar(angle[0]);
                       uart_sendChar(angle[1]);
                       uart_sendChar(angle[2]);
                       uart_sendChar(angle[3]);

                       readVal = '0';
                      readVal = uart_receive();
                      if(readVal == 'h'){

                          if(objectList[shortestObjectIndex].degree > 90){
                              //turn counter clockwise
                                   turn_cclockwise(sensor_data, (objectList[shortestObjectIndex].degree - 90)*3);
                                   move_forward_go_around(sensor_data, objectList[shortestObjectIndex].distance*6);


                          }
                          else{
                              //turn clockwise
                              turn_clockwise(sensor_data, (90-objectList[shortestObjectIndex].degree)*3);
                              move_forward_go_around(sensor_data, objectList[shortestObjectIndex].distance*6);

                          }
                      }
                   }

                   if(toggle == 1){
                       readVal = uart_receive();
                       if(readVal == 'w'){
                           move_forward(sensor_data, 100);
                       }
                       else if(readVal == 's'){
                           move_backwards(sensor_data, 100);
                       }
                       else if(readVal == 'a'){
                           turn_cclockwise(sensor_data, 25);
                       }
                       else if(readVal == 'd'){
                           turn_clockwise(sensor_data, 25);
                       }
                       else if(readVal == 'm'){
                           for(deg = 0; deg <= 180; deg += 2){
                               if((char)(UART1_DR_R & 0xFF) == 't'){
                                   for( i = 0; i < 20; i ++){
                                       uart_sendChar('-');
                                   }
                                   uart_sendChar('\n');
                                   uart_sendChar('\r');
                                   toggle = 1;
                                   break;
                               }
                               //cyBOT_Scan(deg, &scan);
                               servo_move(deg);
                               scan.sound_dist = ping_getDistance();
                               lcd_clear();


                               sprintf(scanval, "%d", (adc_read()+previousScan)/2);


                               sprintf(pingScan, "%f", (scan.sound_dist+previousPingScan)/2);

                               sprintf(degre, "%d", deg);
                               for(i = 0; i< 3; i++){
                                   uart_sendChar(degre[i]);
                               }
                               uart_sendChar(',');
                               uart_sendChar(' ');
                               for(i = 0; i< 5; i++){
                                   uart_sendChar(scanval[i]);
                               }
                               uart_sendChar(',');
                               uart_sendChar(' ');
                               for(i = 0; i< 5; i++){
                                   uart_sendChar(pingScan[i]);
                               }

                               float Stock = pow( ((adc_read()+previousScan)/2.0), -1.626);
                               float Ham = 4000000 * Stock;

                               float calculatedIRVAL = 10000000 * pow(adc_read(), -1.867);
                               float calculatedPREVIOUSVAL = 10000000 * pow(previousScan, -1.867);

                               sprintf(calculatedDistance, "%f", calculatedIRVAL);
                               uart_sendChar(',');
                               uart_sendChar(' ');
                               for(i = 0; i< 5; i++){
                                   uart_sendChar(calculatedDistance[i]);

                               }



                               if(calculatedIRVAL - calculatedPREVIOUSVAL < -20){
                                           //Start object
                                           objectStartDegree = deg;
                                           uart_sendChar('\n');
                                           uart_sendChar('\r');
                                           uart_sendChar('s');
                                           lcd_putc('s');
                                       }
                               if(calculatedPREVIOUSVAL - calculatedIRVAL < -20){
                                   //end object
                                   objectEndDegree = deg;

                                   if(objectEndDegree-objectStartDegree > 7 ){
                                  //     if(((objectEndDegree+objectStartDegree)/2) > (objectList[objectCount--].degree + 3)){
                                           //object is valid
                                           uart_sendChar('\n');
                                           uart_sendChar('\r');
                                           uart_sendChar('o');
                                           uart_sendChar('b');
                                           uart_sendChar('j');
                                           uart_sendChar('\n');
                                           uart_sendChar('\r');
                                           lcd_clear();
                                           //save object
                                           objectList[objectCount].degree = (objectEndDegree + objectStartDegree )/ 2;
                        //                   cyBOT_Scan(objectList[objectCount].degree, &tempscan);
                        //                   objectList[objectCount].distance = tempscan.sound_dist;
                                           objectList[objectCount].distance = scan.sound_dist;
                                           objectList[objectCount].linearWidth = abs(2*((sin((objectEndDegree - objectStartDegree)/2))*objectList[objectCount].distance));
                                           objectList[objectCount].width = objectEndDegree-objectStartDegree;

                                           objectCount++;
                                 //      }
                                   }

                               }

                               previousScan = adc_read();
                               previousPingScan = scan.sound_dist;


                               uart_sendChar('\n');
                               uart_sendChar('\r');
                           }

                           uart_sendChar('O');
                           uart_sendChar('b');
                           uart_sendChar('j');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar('A');
                           uart_sendChar('n');
                           uart_sendChar('g');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar('D');
                           uart_sendChar('i');
                           uart_sendChar('s');
                           uart_sendChar('t');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar('W');
                           uart_sendChar('i');
                           uart_sendChar('d');
                           uart_sendChar('t');
                           uart_sendChar('h');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar(' ');
                           uart_sendChar('L');
                           uart_sendChar('W');
                           uart_sendChar('i');
                           uart_sendChar('d');
                           uart_sendChar('t');
                           uart_sendChar('h');
                           uart_sendChar('\n');
                           uart_sendChar('\r');
                           for(i = 0; i < objectCount; i ++){
                               uart_sendChar(i + 48);
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               sprintf(angle, " %d", objectList[i].degree);
                               sprintf(distance, " %d", objectList[i].distance);
                               sprintf(width, " %d", objectList[i].width);
                               sprintf(linearWidth, " %d", objectList[i].linearWidth);
                               uart_sendChar(angle[0]);
                               uart_sendChar(angle[1]);
                               uart_sendChar(angle[2]);
                               uart_sendChar(angle[3]);
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(distance[0]);
                               uart_sendChar(distance[1]);
                               uart_sendChar(distance[2]);
                               uart_sendChar(distance[3]);
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(width[0]);
                               uart_sendChar(width[1]);
                               uart_sendChar(width[2]);
                               uart_sendChar(width[3]);
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(' ');
                               uart_sendChar(linearWidth[0]);
                               uart_sendChar(linearWidth[1]);
                               uart_sendChar(linearWidth[2]);
                               uart_sendChar(linearWidth[3]);
                               uart_sendChar('\n');
                               uart_sendChar('\r');

                           }
                       }

                   }
                }
