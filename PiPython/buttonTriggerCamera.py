import subprocess
import datetime
# Create a unique filename using the current timestamp
timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
image_name = f"/home/pi/Pictures/picsCarmelito/image_{timestamp}.jpg"

import RPi.GPIO as GPIO
import time
ledPin = 2
buttonPin=4 ## button
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(ledPin, GPIO.OUT)
GPIO.setup(buttonPin, GPIO.IN) ## button
while True:
    if GPIO.input(buttonPin): ##button
        GPIO.output(ledPin, GPIO.HIGH)
        print('Led 2 on')
        # Command to trigger raspistill with a 500ms delay and no preview
        cmd = ["raspistill", "-o", image_name, "-t", "500", "-n"]
        try:
            # Run the subprocess and wait for it to complete
            subprocess.run(cmd, check=True)
            print(f"Successfully captured image: {image_name}")
        except subprocess.CalledProcessError as e:
            print(f"Error capturing image: {e}")
        time.sleep(1)
        GPIO.output(ledPin, GPIO.LOW)
        print('Led 2 off')
        time.sleep(1)


