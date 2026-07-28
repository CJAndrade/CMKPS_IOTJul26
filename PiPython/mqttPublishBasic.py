import RPi.GPIO as GPIO 
import paho.mqtt.client as mqtt 
#from dht11 import DHT11 
import time 
BROKER = "broker.emqx.io" 
PORT = 1883 
tTopic="Temp" 
hTopic="Humid" 
#sensorPin=26 
#sensor=DHT11(pin=sensorPin) 
#def on_connect(client, userdata, flags, rc): 
#    print("Connected with result code", str(rc)) 
GPIO.setwarnings(False) 
GPIO.setmode(GPIO.BCM) 
GPIO.cleanup()
client=mqtt.Client() 
client.connect(BROKER, PORT, 60)
#client.on_connect = on_connect
try: 
    while True: 
        #result=sensor.read() 
        #if result.is_valid(): 
        humidity= 85#round(result.humidity,2) 
        temperature=25 #round(result.temperature,2) 
        print(f"Temperature:{temperature}C") 
        print(f"Humidity:{humidity}%") 
        msg=f"{temperature}"
        msg1=f"{humidity}" 
        client.publish(tTopic,msg) 
        client.publish(hTopic,msg1)

        client.loop() 
        time.sleep(20) 
except KeyboardInterrupt: 
    print("\nExiting the program\n") 
    GPIO.cleanup() 
    exit()

