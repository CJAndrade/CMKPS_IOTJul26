import time
import board
#import adafruit_dht
import requests

#!/usr/bin/env python3

import sys
import serial
import board
import busio   
from PIL import Image, ImageDraw, ImageFont
import adafruit_ssd1306

# -------------------------------
# Serial Port
# -------------------------------
ser = serial.Serial('/dev/ttyUSB2', 2000000, timeout=5)
ParkingS = 10
# -------------------------------




# OLED Setup (128x64 I2C)
# -------------------------------
i2c = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(128, 64, i2c)

oled.fill(0)
oled.show()

image = Image.new("1", (128, 64))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()





# --- Configuration ---
# Replace with your actual ThingSpeak Write API Key
THINGSPEAK_WRITE_KEY = "DQ3SY09IE1WI1VLM"
THINGSPEAK_URL = "https://api.thingspeak.com/update.json"

# Set up the DHT11 sensor. Change 'D4' to match your GPIO pin number.
# For example, if connected to GPIO 4, use board.D4.
#dht_device = adafruit_dht.DHT11(board.D4)

print("Starting DHT11 to ThingSpeak logger... Press Ctrl+C to stop.")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()

        if not line:
            print("Timeout! Exit.")
            continue

        print("Received:", line)

        try:
            
            draw.rectangle((0, 0, 128, 64), outline=0, fill=0)
            
            value1, value2, value3 = line.split(',')

            count = int(value3)

            available = max(0, ParkingS - count)

            print("Available updated:", available)
                       

            draw.text((0, 20), f"Available: {available}", font=font, fill=255)

            oled.image(image)
            oled.show()

        except ValueError:
            print("Invalid data:", line)
            continue

        if available is not None:
            print(f"Available: {available}")

            payload = {
                "api_key": THINGSPEAK_WRITE_KEY,
                "field1": available
            }

            print(payload)

            response = requests.post(
                THINGSPEAK_URL,
                data=payload
            )

            if response.status_code == 200:
                print("Successfully posted:", response.text)
            else:
                print("Failed:", response.status_code)

        # ThingSpeak requires about 15 seconds between updates
        time.sleep(1)


except RuntimeError as error:
    print(f"Sensor reading failed: {error}")
    time.sleep(1)


except Exception as e:
    print(f"Unexpected error occurred: {e}")


except KeyboardInterrupt:
    print("\nProgram stopped by user.")