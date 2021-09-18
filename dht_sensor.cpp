
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 26     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT22    // DHT 22 (AM2302)


DHT_Unified dht(DHTPIN, DHTTYPE);
static bool initialised = 0;
void dht_init()
{
  dht.begin();
  initialised = true;

}

bool getTempHum(float &temperature_out, float &humidity_out)
{
    bool ret_value = 1;
    sensors_event_t event;

    if (initialised == false)
        dht_init();

    // Read temperature
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        ret_value=0;
        // if there is an error on reading temperature
        // no attempt will made to read humidity

    }
    else {
        temperature_out = event.temperature;
        // Read humidity
        dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            ret_value=0;
        }
        else {
            humidity_out = event.relative_humidity;
        }
        
    }
}