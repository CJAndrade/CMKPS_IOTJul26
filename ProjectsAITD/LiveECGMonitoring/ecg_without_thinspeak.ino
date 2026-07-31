#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C  // Default I2C address for 128x32 SSD1306

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ANALOG_PIN A0
#define LO_PLUS    14  // GPIO14 = D5
#define LO_MINUS   12  // GPIO12 = D6

// Waveform buffer array
int waveBuffer[SCREEN_WIDTH];

void setup() {
  Serial.begin(115200);

  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);

  // Initialize OLED (Wemos I2C pins: SDA=D2/GPIO4, SCL=D1/GPIO5)
  Wire.begin(4, 5);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 OLED allocation failed"));
    for(;;); // Stop execution if display isn't detected
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.print("ECG Monitor Ready");
  display.display();
  delay(1000);

  // Fill wave buffer with flat line baseline
  for (int i = 0; i < SCREEN_WIDTH; i++) {
    waveBuffer[i] = SCREEN_HEIGHT / 2;
  }
}

void loop() {
  int ecgRaw = 0;
  bool isLeadOff = (digitalRead(LO_PLUS) == 1) || (digitalRead(LO_MINUS) == 1);

  if (isLeadOff) {
    ecgRaw = 0;
    Serial.println(0); // For Serial Plotter
  } else {
    ecgRaw = analogRead(ANALOG_PIN);
    Serial.println(ecgRaw); // For Serial Plotter
  }

  // Map analog value (0 - 1023) to OLED height (31 - 0)
  // Reversed so high values go up, low values go down
  int mappedY;
  if (isLeadOff) {
    mappedY = SCREEN_HEIGHT / 2; // Flatline on screen when leads are off
  } else {
    // Zoom in on typical AD8232 range (~200 to 800) for better visual amplitude
    mappedY = map(ecgRaw, 200, 800, SCREEN_HEIGHT - 1, 0);
    mappedY = constrain(mappedY, 0, SCREEN_HEIGHT - 1);
  }

  // Shift waveform buffer to the left
  for (int i = 0; i < SCREEN_WIDTH - 1; i++) {
    waveBuffer[i] = waveBuffer[i + 1];
  }
  // Insert new sample at the end
  waveBuffer[SCREEN_WIDTH - 1] = mappedY;

  // Render to OLED
  display.clearDisplay();
  
  if (isLeadOff) {
    display.setCursor(20, 12);
    display.print("LEADS OFF!");
  } else {
    // Draw line segments connecting each stored point
    for (int x = 0; x < SCREEN_WIDTH - 1; x++) {
      display.drawLine(x, waveBuffer[x], x + 1, waveBuffer[x + 1], SSD1306_WHITE);
    }
  }

  display.display();

  // Sampling rate delay
  delay(5);
}