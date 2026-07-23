#include "DFRobot_ADXL345.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin (-1 if sharing Arduino reset)
#define SCREEN_ADDRESS 0x3C // 0x3C for 128x32

DFRobot_ADXL345_I2C ADXL345(&Wire, 0x53);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int accval[3];

void setup() 
{
  Serial.begin(9600);
  
  // Initialize ADXL345 Accelerometer
  ADXL345.begin();
  ADXL345.powerOn();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop execution if OLED isn't detected
  }

  // Clear screen and configure text style
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Brief startup message
  display.setCursor(0, 10);
  display.println(F("ADXL345 Ready..."));
  display.display();
  delay(1000);
}

void loop() 
{
  // Read raw acceleration data
  ADXL345.readAccel(accval);
  ADXL345.RPCalculate(accval);

  // Serial Monitor Output
  Serial.print("x:"); Serial.print(accval[0]);
  Serial.print(" y:"); Serial.print(accval[1]);
  Serial.print(" z:"); Serial.println(accval[2]);
  Serial.print("Roll:"); Serial.println(ADXL345.RP.roll);
  Serial.print("Pitch:"); Serial.println(ADXL345.RP.pitch);

  // --- OLED Display Rendering ---
  display.clearDisplay(); // CRITICAL: Clear previous screen contents

  // Title Line
  display.setCursor(0, 0);
  display.println(F("ACCELEROMETER (RAW)"));

  // Axis Readouts (Line 2 & 3)
  display.setCursor(0, 11);
  display.print(F("X: "));
  display.print(accval[0]);

  display.setCursor(64, 11); // Place Y on the right side of same row
  display.print(F("Y: "));
  display.print(accval[1]);

  display.setCursor(0, 21);
  display.print(F("Z: "));
  display.print(accval[2]);

  // Push frame buffer to screen
  display.display();

  delay(200); // 200ms refresh gives a smooth, readable screen update
}
