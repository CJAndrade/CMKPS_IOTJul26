const int ledPin = 13;   // LED pin
const int pirPin = 2;    // PIR sensor output pin
int val = 0;             // Variable to store the read value

void setup() {
  pinMode(ledPin, OUTPUT);  // Set LED as output
  pinMode(pirPin, INPUT);   // Set PIR sensor as input
  Serial.begin(9600);       // Initialize serial communication
}

void loop() {
  val = digitalRead(pirPin);  // Read sensor value
  
  if (val == HIGH) {          // Check if motion is detected
    digitalWrite(ledPin, HIGH); // Turn LED ON
    Serial.println("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);  // Turn LED OFF
  }
}
