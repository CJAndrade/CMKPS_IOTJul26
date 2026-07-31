#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const int analogInPin = A0;  // Gas sensor connected to A0 on ESP8266 NodeMCU
int sensorValue = 0;  // value read from the pot

// Replace with your network credentials
char ssid[] = "AITD";         
char pass[] = "123456789";   

WiFiClient client;

// Replace with your ThingSpeak Channel details
unsigned long myChannelNumber = 3441256; 
const char * myWriteAPIKey = "10DIMR2RG21PIH72";  

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  
}

void loop() {
  // Connect or reconnect to Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); 
      delay(5000);     
    }
    Serial.println("\nConnected.");
  }

  //Reading gas sensor values
  sensorValue = analogRead(analogInPin);
  // Write value to Field 1 of your ThingSpeak Channel
  int x = ThingSpeak.writeField(myChannelNumber, 1, sensorValue, myWriteAPIKey);
  
  if (x == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // ThingSpeak free tier requires at least 15 seconds between updates
  delay(20000); 
}
