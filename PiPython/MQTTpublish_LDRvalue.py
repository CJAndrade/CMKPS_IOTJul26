import RPi.GPIO as GPIO
import paho.mqtt.client as mqtt
from gpiozero import DigitalInputDevice
import time

BROKER = "broker.emqx.io"
PORT = 1883
lTopic = "Light"

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

sensor = DigitalInputDevice(26)

client = mqtt.Client()
client.connect(BROKER, PORT, 60)

try:
    while True:
        light = sensor.value      # 0 or 1

        print("Room Light:", light)

        client.publish(lTopic, str(light))
        client.loop()

        time.sleep(2)

except KeyboardInterrupt:
    print("\nExiting the program")
    GPIO.cleanup()
