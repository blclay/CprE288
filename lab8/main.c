

/**
 * main.c
 */

#include "Timer.h"
#include "lcd.h"
#include "adc.h"


int main(void)
{

    // initialize adc
    ADC0_init();

    // need a variable to hold the result
    int adc_result;


    while (1) {

        // trigger the adc conversion and get the result

        adc_result = ADC0_InSeq3();

        // do something with the result

    }

    // initialize adc0 and configure pe3 as analog input

    // need to use pin PB4 (AIN 10)


     void ADC0_init(void){
         // enable clock for adc0 and port e

         SYSCTL_RCGCADC_R |= 0x01; // this is to enable the clock for the adc0 bit 0

         // configure pe3 for aino analog port

         // some more stuff


         // trigger ADC conversion and get result

         ADCO_InSeq3(void)
         {




         }

     }

	return 0;
}
