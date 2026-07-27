from gpiozero import PWMLED
from time import sleep

while True:  
    led = PWMLED(14)
    led.value =1
    sleep(1)
    led.value=0.5
    sleep(1)
    led.value=0
