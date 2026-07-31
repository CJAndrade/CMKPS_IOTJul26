#include<DHT.h>
#include "HX711.h"
#define DT 4
#define SCK 5

HX711 scale;

float calibration_factor = 11.375; 
DHT dht(2,DHT11);

void setup() {
  dht.begin();
  Serial.begin(115200);
  scale.begin(DT,SCK);
  scale.set_scale(calibration_factor);
  scale.tare();
  //Serial.println("Time,Temperature, Humidity,Load");
   scale.begin(DT, SCK);

  }

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float L = scale.get_units(10);
 
  delay(1000);

Serial.print(t);
Serial.print(",");

Serial.print(h);
Serial.print(",");

Serial.println(-L/100);
  delay(3000);
}

