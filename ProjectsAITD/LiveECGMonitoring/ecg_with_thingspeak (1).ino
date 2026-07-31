#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- WiFi & ThingSpeak Credentials ---
const char* WIFI_SSID = "AITD";         // Replace with your WiFi SSID
const char* WIFI_PASSWORD = "123456789"; // Replace with your WiFi Password

unsigned long myChannelNumber = 3440691;          // Replace with your ThingSpeak Channel ID (Number)
const char* myWriteAPIKey = "3A687BCY0SBXX69T"; // Replace with your ThingSpeak Write API Key

WiFiClient client;

// --- OLED Config ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Pin Definitions ---
#define ANALOG_PIN A0
#define LO_PLUS    14  // GPIO14 = D5
#define LO_MINUS   12  // GPIO12 = D6

int waveBuffer[SCREEN_WIDTH];

// Timing variables for cloud updates (Every 15 Seconds)
unsigned long lastCloudUpdate = 0;
const unsigned long cloudInterval = 15000; 

void setup() {
  Serial.begin(115200);

  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);

  // Initialize OLED
  Wire.begin(4, 5);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Connecting WiFi...");
  display.display();

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected!");
  display.display();
  delay(1000);

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  // Fill wave buffer baseline
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    waveBuffer[i] = SCREEN_HEIGHT / 2;
  }
}

void loop() {
  int ecgRaw = 0;
  bool isLeadOff = (digitalRead(LO_PLUS) == 1) || (digitalRead(LO_MINUS) == 1);

  if (isLeadOff) {
    ecgRaw = 0;
    Serial.println(0);
  } else {
    ecgRaw = analogRead(ANALOG_PIN);
    Serial.println(ecgRaw);
  }

  // --- OLED Waveform Rendering ---
  int mappedY;
  if (isLeadOff) {
    mappedY = SCREEN_HEIGHT / 2;
  } else {
    mappedY = map(ecgRaw, 200, 800, SCREEN_HEIGHT - 1, 0);
    mappedY = constrain(mappedY, 0, SCREEN_HEIGHT - 1);
  }

  // Shift buffer left
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    waveBuffer[i] = waveBuffer[i + 1];
  }
  waveBuffer[SCREEN_WIDTH - 1] = mappedY;

  display.clearDisplay();
  if (isLeadOff) {
    display.setCursor(20, 12);
    display.print("LEADS OFF!");
  } else {
    for (int x = 0; x < SCREEN_WIDTH - 1; x++) {
      display.drawLine(x, waveBuffer[x], x + 1, waveBuffer[x + 1], SSD1306_WHITE);
    }
  }
  display.display();

  // --- Non-Blocking ThingSpeak Cloud Upload ---
  if (millis() - lastCloudUpdate >= cloudInterval) {
    lastCloudUpdate = millis();

    // Reconnect WiFi if lost
    if (WiFi.status() == WL_CONNECTED) {
      int httpCode = ThingSpeak.writeField(myChannelNumber, 1, ecgRaw, myWriteAPIKey);
      
      if (httpCode == 200) {
        Serial.println("ThingSpeak update successful!");
      } else {
        Serial.println("Error updating ThingSpeak. HTTP error code: " + String(httpCode));
      }
    } else {
      Serial.println("WiFi Disconnected. Skipping cloud update.");
    }
  }

  delay(5);
}