
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <WiFi.h>
#include <ThingSpeak.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "dht_sensor.h"
#include "moisture_sensor.h"
#include "ph_sensor.h"


#define CHANNEL_ID 1445524 
#define CHANELL_API "E9BTJTSNFD5FXVH9"
  
WiFiClient client;


#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "Omega"
#define WIFI_PASSWORD "methegreat@7"


uint32_t delayMS;
//unsigned int ldr;

void connectToWifi()
{
  Serial.print("connecting to Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK,WIFI_PASSWORD);

  unsigned long startAttemptime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptime < WIFI_TIMEOUT_MS)
  {
    Serial.print(".");
    delay(100);
  }
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println(" FAILED!");
  }
  else
  {
    Serial.print(" CONNECTED");
    Serial.println(WiFi.localIP());
  }
}
void setup() {

  Serial.begin(9600);
  // Initialize device.
  dht_init();
  connectToWifi();
  ThingSpeak.begin(client);
/*
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
 */
  delayMS = 4000;
}

void loop() {
  // Delay between measurements.


  float soil_moisture_value;
  soil_moisture_value = getMoisture();
  Serial.println("\nSoil moisture:  ");
  Serial.print(soil_moisture_value);
  Serial.println("%");
  if(soil_moisture_value>60 && soil_moisture_value<80)
  Serial.println("\n Soil moisture low. so turning on motor");

  float ph;
  ph= getpH();
  Serial.println("\nph value of soil: ");
  Serial.print(ph);
  if(ph<5.5 && ph>7.7)
  Serial.println("\n ph is not under range...");
 

  bool result;
  float temp;
  float hum;
  result = getTempHum(temp,hum);
  Serial.println("\n temperature: ");
  Serial.println(temp);\
  Serial.println("\n humidity: ");
  Serial.println(hum);
 
  Serial.println("\n---------------------------------");


  // Thingspeak
  ThingSpeak.writeField(CHANNEL_ID,3,soil_moisture_value,CHANELL_API);
  ThingSpeak.writeField(CHANNEL_ID,4,ph,CHANELL_API);
  ThingSpeak.writeField(CHANNEL_ID,1,temp,CHANELL_API);
  ThingSpeak.writeField(CHANNEL_ID,2,hum,CHANELL_API);
  ThingSpeak.writeField(CHANNEL_ID,5,"1",CHANELL_API);
    
  delay(delayMS);

}
