import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
ledPinOne=2
ledPinTwo=3
ledPinThree=5
ledPinFour=6
GPIO.setup(ledPinOne,GPIO.OUT)
GPIO.setup(ledPinTwo,GPIO.OUT)
GPIO.setup(ledPinThree,GPIO.OUT)
GPIO.setup(ledPinFour,GPIO.OUT)
try:
    while True:
        option=int(input("Enter 1/2/3/4/5: "))
        if option==1:
            GPIO.output(ledPinOne,GPIO.HIGH)
            GPIO.output(ledPinTwo,GPIO.LOW)
            GPIO.output(ledPinThree,GPIO.LOW)
            GPIO.output(ledPinFour,GPIO.LOW)
        elif option==2:
            GPIO.output(ledPinOne,GPIO.LOW)
            GPIO.output(ledPinTwo,GPIO.HIGH)
            GPIO.output(ledPinThree,GPIO.LOW)
            GPIO.output(ledPinFour,GPIO.LOW)
        elif option==3:
            GPIO.output(ledPinOne,GPIO.LOW)
            GPIO.output(ledPinTwo,GPIO.LOW)
            GPIO.output(ledPinThree,GPIO.HIGH)
            GPIO.output(ledPinFour,GPIO.LOW)
        elif option==4:
            GPIO.output(ledPinOne,GPIO.LOW)
            GPIO.output(ledPinTwo,GPIO.LOW)
            GPIO.output(ledPinThree,GPIO.LOW)
            GPIO.output(ledPinFour,GPIO.HIGH)
        elif option==5:
            GPIO.output(ledPinOne,GPIO.HIGH)
            GPIO.output(ledPinTwo,GPIO.HIGH)
            GPIO.output(ledPinThree,GPIO.HIGH)
            GPIO.output(ledPinFour,GPIO.HIGH)
        else:
            print("Invalid Input.Try again")
except KeyboardInterrupt:
    print("\nExiting program\n")
    GPIO.cleanup()
    exit()
                                        





