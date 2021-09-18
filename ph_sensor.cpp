#include <Arduino.h>

#include "ph_sensor.h"
#include "common_header.h"

#define ph_pin 35

float getpH(void)
{
    float ph_out;
    ph_out =  ( (analogRead(ph_pin)/1023.00) * 100.00 ) ;
    
#ifdef TESTING
    ph_out = random(1,10);
#endif
    return(ph_out);
}