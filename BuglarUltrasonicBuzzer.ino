
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