#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Display Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// Create OLED object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
const int trigPin = 10;
const int echoPin = 11;
const int buzzerPin = 7;

// Threshold for detection in centimeters
const int thresholdDistance = 30; // Buzzer sounds if object is closer than 30 cm

long duration;
int distance;

void setup() {
  Serial.begin(9600); // For monitoring distance in Serial Monitor

  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt execution if screen isn't found
  }

  // Clear buffer and setup initial text styling
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  // Startup Screen
  display.setCursor(0, 10);
  display.println(F("Ultrasonic Ready..."));
  display.display();
  delay(1000);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond HIGH pulse to trigger ultrasonic soundwave
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters (speed of sound is 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- OLED Display Rendering ---
  display.clearDisplay(); // Wipe previous frame

  // Line 1: Header
  display.setCursor(0, 0);
  display.println(F("DISTANCE MONITOR"));

  // Line 2: Distance Value
  display.setCursor(0, 12);
  display.print(F("Dist: "));
  if (distance > 0 && distance < 400) {
    display.print(distance);
    display.print(F(" cm"));
  } else {
    display.print(F("Out of Range"));
  }

  // Line 3: System Status Indicator
  display.setCursor(0, 22);
  if (distance > 0 && distance <= thresholdDistance) {
    display.print(F("Status: [ ALERT! ]"));
  } else {
    display.print(F("Status: [ CLEAR ]"));
  }

  display.display(); // Push frame buffer to OLED

  // --- Buzzer Control ---
  if (distance > 0 && distance <= thresholdDistance) {
    // Crisp beep tone
    tone(buzzerPin, 1000); // 1 kHz tone
    delay(50);             // Brief tone duration
    noTone(buzzerPin);
    
    // Pause decreases as object gets closer (closer = faster beep rate)
    int delayTime = map(distance, 2, thresholdDistance, 30, 250);
    delay(delayTime);
  } else {
    noTone(buzzerPin); // Turn off buzzer when clear
    delay(100);        // Brief pause before next measurement
  }
}