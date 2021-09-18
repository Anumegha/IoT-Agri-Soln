#ifndef _DHT_SENSOR_H
    // function name: getTempHum()
    // Description:
    //      A call by reference to get the temperature and humidity value 
    // paremeters: Location of temperature and humidity where the values has to be stored
    //          temperature_out: Address for tenperature value
    //          humidity_out: Address for humidity value
    // return:
    //       1: If the sensor is ready successfully
    //       0: For any error encountered
    bool getTempHum(float &temperature_out, float &humidity_out);
    void dht_init();
    #define _DHT_SENSOR_H
#endif 