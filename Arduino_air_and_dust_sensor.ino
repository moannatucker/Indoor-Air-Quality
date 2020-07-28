
#include "AirQuality.h"
#include <dht.h>
#define PIR_MOTION_SENSOR 3
#define DHTPIN 2
#define DHTTYPE DHT11
dht DHT;
AirQuality airqualitysensor;
float sensorValue;
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 1000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;


void setup(){
  pinMode(PIR_MOTION_SENSOR, INPUT);//added
  pinMode(pin, INPUT);
  starttime = millis();
  Serial.begin(9600);
  Serial.println("setup loop");
}

void loop(){

    
  /*delay(1000);//added
   if(digitalRead(PIR_MOTION_SENSOR)){//if it detects the moving people?
        Serial.println("Motion detected");//added
        Serial.print(",");
   }
    else{
        Serial.println("Watching");
        Serial.print(",");
  }*/
  duration = pulseIn(pin,LOW);
    lowpulseoccupancy = lowpulseoccupancy+duration;
    
    if((millis()-starttime) > sampletime_ms)//if sample time == 30s
    {
      ratio = lowpulseoccupancy/(sampletime_ms*10.0);//integer percentage=>100
      concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62;
      Serial.print(lowpulseoccupancy);
      Serial.print(",");
      Serial.print(ratio);
      Serial.print(",");
      Serial.println(concentration);
      lowpulseoccupancy = 0;
      starttime = millis();
      if(digitalRead(PIR_MOTION_SENSOR)){//if it detects the moving people?
        Serial.print("Motion detected,");//added
        
        }
    else{
        Serial.print("Watching,");      }
    }
 
 delay(500);

}
