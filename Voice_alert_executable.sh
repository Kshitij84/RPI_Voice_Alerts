#!/bin/bash

# Update and upgrade the system
echo "Updating system..."
sudo apt-get update -y
sudo apt-get upgrade -y

# Install Python3 and pip if not installed
echo "Checking for Python3 and pip..."
sudo apt-get install python3 python3-pip -y

# Install required Python libraries
echo "Installing required Python libraries..."
pip3 install pyserial pyvolume playsound pyinstaller

# Install dependencies for playsound (required for some systems)
echo "Installing required dependencies for playsound..."
sudo apt-get install libsndfile1 -y

# Confirm installation
echo "All required libraries have been installed."

echo "Setup complete! You can now run your script or create an executable using PyInstaller."
