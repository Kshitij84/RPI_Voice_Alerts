#!/usr/bin/env python3
# 
# This Python script communicates with a serial device an Arduino and listens for specific updates.
# It checks for three types of responses:
# 1. "Emergency_Pressed": Plays an emergency alert sound.
# 2. "Obstacle_Detected": Plays an obstacle detection alert sound.
# 3. "battery_low": Plays a low battery alert sound.
#
# The serial communication is established via '/dev/ttyUSB0' at a baud rate of 115200.
# The system volume is set to 100% using the pyvolume module, and the responses are processed
# by reading data from the serial port and triggering audio alerts accordingly.
# The script runs in an infinite loop and can be stopped by a keyboard interrupt (Ctrl+C).
# 

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
    print("Close Serial Communication.")
