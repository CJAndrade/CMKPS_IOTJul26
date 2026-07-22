#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTPIN 2       // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  //Sensor type

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin
#define SCREEN_ADDRESS 0x3C // 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 & OLED Test"));

  // Initialize DHT sensor
  dht.begin();

  // Initialize OLED display (Address 0x3C for 128x32)
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop execution if OLED isn't detected
  }

  // Clear the screen and set up default text styles
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  
  // Initial startup screen
  display.setCursor(0, 10);
  display.println(F("Initializing..."));
  display.display();
  delay(2000);
}

void loop() {
  // Wait 2 seconds between measurements (DHT11 updates slowly)
  delay(2000);

  // Read temperature and humidity
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Celsius

  // Check if sensor reading failed
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println(F("Sensor Error!"));
    display.display();
    return;
  }

  // Log to Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temp: "));
  Serial.print(t);
  Serial.println(F(" C"));

  // --- Draw to OLED Display ---
  display.clearDisplay(); // Clear old text

  // Line 1: Title
  display.setCursor(0, 0);
  display.println(F("=== ENVIRONMENT ==="));

  // Line 2: Temperature
  display.setCursor(0, 12);
  display.print(F("Temp:     "));
  display.print(t, 1); // 1 decimal place
  display.println(F(" C"));

  // Line 3: Humidity
  display.setCursor(0, 22);
  display.print(F("Humidity: "));
  display.print(h, 1); // 1 decimal place
  display.println(F(" %"));

  // Push frame buffer to physical display
  display.display();
}