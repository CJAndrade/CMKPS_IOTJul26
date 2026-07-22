const int buttonPin = 8;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int buttonState = 0;  
void setup() {
  Serial.begin(9600);    // Initialize the Serial monitor for debugging
 // Serial1.begin(9600);   // Initialize Serial1 for sending data
  pinMode(buttonPin, INPUT);
}

void loop() {

  buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
      Serial.println(1); //Sending 1 from Arduino on the transmit side
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

}