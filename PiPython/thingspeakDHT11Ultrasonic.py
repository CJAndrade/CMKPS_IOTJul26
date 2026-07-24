import time
import board
import adafruit_dht
import requests
import RPi.GPIO as GPIO


GPIO.setmode(GPIO.BCM)

GPIO.setwarnings(False)

TRIG_PIN =24
ECHO_PIN =25


GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)

# --- Configuration ---
# Replace with your actual ThingSpeak Write API Key
THINGSPEAK_WRITE_KEY = "4ON6EFIA3A30UXWR"
THINGSPEAK_URL = "https://api.thingspeak.com/update.json"

# Set up the DHT11 sensor. Change 'D4' to match your GPIO pin number.
# For example, if connected to GPIO 4, use board.D4.
dht_device = adafruit_dht.DHT11(board.D15)

print("Starting DHT11 to ThingSpeak logger... Press Ctrl+C to stop.")

def get_distance():
    
    GPIO.output(TRIG_PIN, GPIO.LOW)
    time.sleep(0.1)
    
    GPIO.output(TRIG_PIN, GPIO.HIGH)
    time.sleep(0.0001)
    
    GPIO.output(TRIG_PIN, GPIO.LOW)
    
    while GPIO.input(ECHO_PIN)==0:
        pulse_start = time.time()
        
    while GPIO.input(ECHO_PIN)==1:
        pulse_end = time.time()
    
    pulse_duration = pulse_end - pulse_start
    distance = (pulse_duration * 34300)/2
    return round(distance, 2)


try:
    while True:
        try:
            # Read values from the DHT11 sensor
            temperature_c = dht_device.temperature
            humidity = dht_device.humidity
        

            # Print data to terminal if read is successful
            if temperature_c is not None and humidity is not None:
                print(f"Temp: {temperature_c:.1f}°C | Humidity: {humidity:.1f}%")
                dist = get_distance()
                print(f"Measured distance: {dist} cm")
                time.sleep(1)

                # Payload containing data mapped to ThingSpeak channel fields
                payload = {
                    "api_key": THINGSPEAK_WRITE_KEY,
                    "field1": temperature_c,
                    "field2": humidity,
                    "field3": dist
                }
                print(payload);
                # Send data to ThingSpeak cloud via HTTP POST
                response = requests.post(THINGSPEAK_URL, data=payload)

                if response.status_code == 200:
                    print(f"Successfully posted to ThingSpeak. Server response: {response.text}")
                else:
                    print(f"Failed to post data. Status code: {response.status_code}")
                    
            

        except RuntimeError as error:
            # DHT sensors can be unstable; errors happen frequently. Just retry.
            print(f"Sensor reading failed: {error.args[0]}")
            time.sleep(2.0)
            continue
        except Exception as e:
            print(f"An unexpected error occurred: {e}")

        # ThingSpeak free tier requires a minimum 15-second interval between updates
        time.sleep(60.0)

except KeyboardInterrupt:
    print("\nProgram stopped by user.")
finally:
    # Release hardware resources
    dht_device.exit()
