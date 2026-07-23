import RPi.GPIO as GPIO
import time

# Use Broadcom (BCM) pin numbering
GPIO.setmode(GPIO.BCM)

# Define GPIO pins
TRIG_PIN = 24
ECHO_PIN = 25 #does not work with the 3.3v pins

# Set up pin directions
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)

def get_distance():
    # Ensure trigger is low initially
    GPIO.output(TRIG_PIN, GPIO.LOW)
    time.sleep(0.1)
    # Send a 10-microsecond pulse to trigger the sensor
    GPIO.output(TRIG_PIN, GPIO.HIGH)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, GPIO.LOW)
    # Save the start time (when Echo pin goes HIGH)
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()
    # Save the arrival time (when Echo pin goes LOW)
    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()
    # Calculate pulse duration
    pulse_duration = pulse_end - pulse_start
    # Multiply by the speed of sound (34300 cm/s) and divide by 2 for the round trip
    distance = (pulse_duration * 34300) / 2
    return round(distance, 2)

try:
    print("Starting distance measurement... Press Ctrl+C to stop.")
    while True:
        dist = get_distance()
        print(f"Measured Distance: {dist} cm")
        time.sleep(1)  # Wait 1 second before the next reading

except KeyboardInterrupt:
    print("\nMeasurement stopped by user.")
finally:
    GPIO.cleanup()  # Reset GPIO ports cleanly
