#!/usr/bin/env python3

# This Python script establishes serial communication with an Arduino and listens for specific updates.
# When the script receives certain messages from the Arduino, it triggers corresponding voice alerts.
# The alerts are played using pre-recorded audio files for the following events:
# 1. "Emergency_Pressed": Plays an emergency alert sound.
# 2. "Obstacle_Detected": Plays an obstacle detection alert sound.
# 3. "battery_low": Plays a low battery alert sound.
#
# The serial communication is set up on '/dev/ttyUSB0' at a baud rate of 115200.
# The script also sets the system volume to 100% using the pyvolume module.
# The program runs in an infinite loop, processing incoming serial messages and responding with audio.
# The loop continues until the user stops the script using a keyboard interrupt (Ctrl+C).

import serial  # Import the serial module to handle communication with the Arduino.
import time  # Import the time module to control delays and manage timing.
from playsound import playsound  # Import the playsound module to play audio files.
import pyvolume  # Import pyvolume to control the system's volume level.

# Set the system volume to 100% to ensure the audio alerts are loud enough.
pyvolume.custom(percent=100)

# Set up the serial connection to the Arduino with a baud rate of 115200 and a timeout of 1 second.
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1.0)

# Wait for 3 seconds to ensure the serial connection is fully established.
time.sleep(3)

# Clear any leftover data in the serial input buffer.
ser.reset_input_buffer()

# Confirm that the serial connection is established.
print("Serial OK")

try:
    # Run an infinite loop to continuously check for updates from the Arduino.
    while True:
        # Small delay to prevent overloading the CPU and allow for serial communication.
        time.sleep(0.01)
        print("Get Updates")

        # Send a request to the Arduino to get updates.
        ser.write("Give updates \n".encode('utf-8'))

        # Wait until there is data available to read from the serial input buffer.
        while ser.in_waiting <= 0:
            time.sleep(0.01)

        # Read the response from the Arduino, decode it, and strip any extraneous whitespace.
        response = ser.readline().decode('utf-8').rstrip()

        # Check if the received response matches specific events and play the corresponding sound.
        if response == "Emergency_Pressed":
            # Play the emergency alert sound if the Arduino reports "Emergency_Pressed".
            playsound("/home/kshitij/RPI_Voice_Alerts/Emergency/Emergency_Pressed_Alice.wav")
            print(response)  # Output the response to the console for debugging.

        elif response == "Obstacle_Detected":
            # Play the obstacle detection sound if the Arduino reports "Obstacle_Detected".
            playsound("/home/kshitij/RPI_Voice_Alerts/Obstacle/obstacle_detected_Alice.wav")
            print(response)  # Output the response to the console for debugging.

        elif response == "battery_low":
            # Play the low battery alert sound if the Arduino reports "battery_low".
            playsound("/home/kshitij/RPI_Voice_Alerts/low_battery/low_battery_Alice.wav")
            print(response)  # Output the response to the console for debugging.

except KeyboardInterrupt:
    #close the serial connection when the script is interrupted by the user.
    print("Close Serial Communication.")
