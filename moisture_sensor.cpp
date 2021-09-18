#include <Arduino.h>

#include "moisture_sensor.h"
#include "common_header.h"

#define soilm_in 34

float getMoisture(void)
{
    float moisture_out;
    moisture_out =  ( (analogRead(soilm_in)/1023.00) * 100.00 ) ;
    
#ifdef TESTING
    moisture_out = random(10,100);
#endif
    return(moisture_out);
}