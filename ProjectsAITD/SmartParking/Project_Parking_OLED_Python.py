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
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=5)
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

while True:
    line = ser.readline().decode('utf-8').strip()

    if not line:
        print("Timeout! Exit.")
        sys.exit()

    print("Received:", line)

    try:
        value1, value2, value3 = line.split(',')

        draw.rectangle((0, 0, 128, 64), outline=0, fill=0)
        available = ParkingS-int(value3)

        draw.text((0, 20), f"Available: {available}", font=font, fill=255)

        oled.image(image)
        oled.show()
        
        

    except ValueError:
        print("Invalid data:", line)