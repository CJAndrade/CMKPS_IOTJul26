#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
int ledPin=7;
// Sound sensor analog output connected to A0
const int soundPin = A0;
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
BTSerial.begin(9600);
Serial.begin(9600);
}

void loop() {
if(BTSerial.available()){
int soundValue = analogRead(soundPin);
 if (soundValue< 250){
  const char *msg = "Nicked - Out";
   BTSerial.write((const uint8_t*)msg, strlen(msg));
   digitalWrite(ledPin, HIGH);
  delay(1500);
 }else{
  const char *msg = "No Bat Involved";
   BTSerial.write((const uint8_t*)msg, strlen(msg));
   digitalWrite(ledPin, LOW);
  delay(1500);
 }


}
// connect a blueooth app and send values like 1,2,3
}
