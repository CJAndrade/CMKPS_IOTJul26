#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
int ledPin=7;
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
BTSerial.begin(9600);
Serial.begin(9600);
}

void loop() {
if(BTSerial.available()){
  char command= BTSerial.read();
  Serial.println(command);
  if(command == '1'){
  digitalWrite(ledPin,HIGH);
  delay(1000);
  }else{
    digitalWrite(ledPin,LOW);
  }

}
// connect a blueooth app and send values like 1,2,3
}
