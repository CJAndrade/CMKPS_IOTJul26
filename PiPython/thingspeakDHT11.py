import time
import board
import adafruit_dht
import requests

# --- Configuration ---
# Replace with your actual ThingSpeak Write API Key
THINGSPEAK_WRITE_KEY = "WHHV1YVSYSBD19OG"
THINGSPEAK_URL = "https://api.thingspeak.com/update.json"

# Set up the DHT11 sensor. Change 'D4' to match your GPIO pin number.
# For example, if connected to GPIO 4, use board.D4.
dht_device = adafruit_dht.DHT11(board.D4)

print("Starting DHT11 to ThingSpeak logger... Press Ctrl+C to stop.")

try:
    while True:
        try:
            # Read values from the DHT11 sensor
            temperature_c =11 #CA dht_device.temperature
            humidity = 55#CA dht_device.humidity

            # Print data to terminal if read is successful
            if temperature_c is not None and humidity is not None:
                print(f"Temp: {temperature_c:.1f}°C | Humidity: {humidity:.1f}%")

                # Payload containing data mapped to ThingSpeak channel fields
                payload = {
                    "api_key": THINGSPEAK_WRITE_KEY,
                    "field1": temperature_c,
                    "field2": humidity
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
