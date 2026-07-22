#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>



#include<DHT.h>
LiquidCrystal_I2C lcd(0x20, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE);
DHT dht(2,DHT11);
String tempMessage;
String humMessage;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("DHT11 Sensor");
  dht.begin();
  Serial.begin(9600);
  Serial.println("Temperature and Humidity Sensor");

}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h)|| isnan(t)){
    Serial.println("Failed to read from DHT sensor!");
    loop();
  }
  tempMessage = "Temp: " + String(t) + "C";
  humMessage = "Hum: " + String(h) + "%";

  Serial.print(tempMessage + "   ");
  Serial.println(humMessage);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(tempMessage);
  lcd.setCursor(1,1);
  lcd.print(humMessage);
  delay(1000);


}
