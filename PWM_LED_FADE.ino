int led = 3;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 3 to be an output:
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 3:
  analogWrite(led, 0); //Brightness set to (0/255)*5V
  delay (1000);
  analogWrite(led, 10); //brightness set to (10/255)*5V
  delay(1000);
  analogWrite(led, 100); //brightness set to (100/255)*5V
  delay(1000);
  analogWrite(led, 255); //brightness set to (255/255)*5V
  delay(1000);
  }

