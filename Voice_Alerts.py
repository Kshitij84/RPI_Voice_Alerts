#!/usr//bin/env python3
import serial
import time
from playsound import playsound
import pyvolume

pyvolume.custom(percent=100)

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1.0)
time.sleep(3)
ser.reset_input_buffer()
print("Serial OK")

try:
    while True:
        time.sleep(0.01)
        print("Get Updates")
        ser.write("Give updates \n".encode('utf-8'))
        while ser.in_waiting <= 0:
            time.sleep(0.01)
        response = ser.readline().decode('utf-8').rstrip()
        if response == "Emergency_Pressed":
            playsound("/home/kshitij/RPI_Voice_Alerts/Emergency/Emergency_Pressed_Alice.wav")
            print(response)
        elif response == "Obstacle_Detected":
            playsound("/home/kshitij/RPI_Voice_Alerts/Obstacle/obstacle_detected_Alice.wav")
            print(response)
        elif response == "battery_low":
            playsound("/home/kshitij/RPI_Voice_Alerts/low_battery/low_battery_Alice.wav")
            print(response)    
except KeyboardInterrupt:
    print("Close Serial Communication. ")
