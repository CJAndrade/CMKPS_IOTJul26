// Arduino Nano - 2 Ultrasonic Sensors
// Output format to Raspberry Pi:
// Sensor1_State,Sensor2_State,Occupied_Count
// Example: 1,0,1

const int NUM_SENSORS = 2;

const int trigPins[NUM_SENSORS] = {4, 7};
const int echoPins[NUM_SENSORS] = {5, 8};

const float THRESHOLD_CM = 10.0;      // Detection distance (adjust if needed)
const unsigned long ECHO_TIMEOUT = 30000; // 30 ms timeout

void setup() {
  Serial.begin(2000000);

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    digitalWrite(trigPins[i], LOW);
  }
}

void loop() {

  int sensorState[NUM_SENSORS];
  int occupiedCount = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {

    // Generate trigger pulse
    digitalWrite(trigPins[i], LOW);
    delayMicroseconds(2);

    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(5);

    digitalWrite(trigPins[i], LOW);

    // Measure echo duration
    unsigned long duration = pulseIn(echoPins[i], HIGH, ECHO_TIMEOUT);

    if (duration == 0) {
      // Timeout - treat as no obstacle
      sensorState[i] = 0;
    }
    else {
      float distance = duration * 0.0343 / 2.0;

      if (distance <= THRESHOLD_CM)
        sensorState[i] = 1;
      else
        sensorState[i] = 0;
    }

    occupiedCount += sensorState[i];

    // Delay to avoid interference between sensors
    delay(10);
  }

  // Send data to Raspberry Pi
  // Format: S1,S2,COUNT
  Serial.print(sensorState[0]);
  Serial.print(",");
  Serial.print(sensorState[1]);
  Serial.print(",");
  Serial.println(occupiedCount);

  // Update twice per second
  delay(10);
}
