import RPi.GPIO as GPIO
import time
ledPin = 2
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(ledPin, GPIO.OUT)

while True:
    GPIO.output(ledPin, GPIO.HIGH)
    print('Led 2 on')
    time.sleep(1)
    GPIO.output(ledPin, GPIO.LOW)
    print('Led 2 off')
    time.sleep(1)

