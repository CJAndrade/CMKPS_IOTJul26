void setup() {
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin

  Serial.begin(9600);               // initialize serial communication at 9600 bits per second:
}
void loop() {
  if (Serial.read() == '1'){  // check if 1 is recived from the Arduino 1 on the transmit side
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else if (Serial.read() == '0'){
    digitalWrite(LED_BUILTIN, LOW);
  }
}