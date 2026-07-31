#define ANALOG_PIN A0
#define LO_PLUS    14  // GPIO14 = D5 on Wemos
#define LO_MINUS   12  // GPIO12 = D6 on Wemos

void setup() {
  // Serial communication at high baud rate for smooth plotting
  Serial.begin(115200);

  // Configure Leads-Off detection pins
  pinMode(LO_PLUS, INPUT);
  pinMode(LO_MINUS, INPUT);
}

void loop() {
  // Check if electrodes are disconnected
  if ((digitalRead(LO_PLUS) == 1) || (digitalRead(LO_MINUS) == 1)) {
    // Lead disconnected signal
    Serial.println(0); 
  } else {
    // Read and print analog raw signal (0 - 1023)
    int ecgValue = analogRead(ANALOG_PIN);
    Serial.println(ecgValue);
  }

  // Sampling rate adjustment (~200Hz sampling rate)
  delay(5); 
}