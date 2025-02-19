/*
  This program uses an emergency button, a potentiometer, and an ultrasonic sensor to monitor a system. 
  It checks three conditions:
  1. If the emergency button is pressed, it prints "Emergency_Pressed".
  2. If an obstacle is detected (distance less than 15 cm), it prints "Obstacle_Detected".
  3. If the potentiometer value is below 40, it indicates a low battery and prints "battery_low".
  
  The emergency button is debounced to avoid multiple presses being detected due to noise or quick fluctuations.
  The program communicates the status via the Serial Monitor.
*/

const int Emergency_button = 2;  // Emergency button pin
const int trigPin = 9;  // Trigger pin for ultrasonic sensor
const int echoPin = 10;  // Echo pin for ultrasonic sensor
int Emergency_button_state = 0;  // Variable to hold the current state of the emergency button
int lastEmergency_button_state = LOW;  // Variable to hold the previous state of the emergency button
unsigned long lastDebounceTime = 0;  // Variable to track the last debounce time
unsigned long debounceDelay = 50;  // Debounce delay (50 milliseconds)

int pot = A0;  // Potentiometer analog pin
int PotValue = 0;  // Variable to hold the potentiometer value
float duration, distance;  // Variables to hold duration and calculated distance

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
  Serial.println("Serial OK");

  pinMode(Emergency_button, INPUT);  // Set emergency button pin as input
  pinMode(pot, INPUT);  // Set potentiometer pin as input
  pinMode(trigPin, OUTPUT);  // Set trigger pin for ultrasonic sensor as output
  pinMode(echoPin, INPUT);  // Set echo pin for ultrasonic sensor as input
}

void loop() {
  // Trigger ultrasonic sensor to send pulse
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 
  
  // Measure duration of the pulse from echoPin
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance in cm (speed of sound 0.0343 cm/us)
  distance = (duration * 0.0343) / 2;
  
  // Read the raw state of the emergency button
  int reading = digitalRead(Emergency_button);

  // Check if the button state has changed (i.e., a new press or release)
  if (reading != lastEmergency_button_state) {
    lastDebounceTime = millis();  // Reset the debounce timer
  }

  // If the button state has been stable for longer than the debounce delay, register the press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Only take action if the button state has changed
    if (reading != Emergency_button_state) {
      Emergency_button_state = reading;

      // If the button was pressed
      if (Emergency_button_state == HIGH) {
        Serial.println("Emergency_Pressed");
      }
    }
  }

  // Store the current button state for comparison in the next loop
  lastEmergency_button_state = reading;

  // Read the potentiometer value
  PotValue = analogRead(pot);

  // Check if emergency button is pressed
  if (Emergency_button_state == HIGH) {
    Serial.println("Emergency_Pressed");
    delay(1000);  // Optional delay for readability
  }
  // Check if an obstacle is detected (distance < 15 cm)
  else if (distance < 15) {
    Serial.println("Obstacle_Detected");
  }
  // Check if battery is low (potentiometer value < 40)
  else if (PotValue < 40) {
    Serial.println("battery_low");
  } 
  // If no conditions are met, print normal status
  else {
    Serial.println("Emergency not pressed, Obstacle not detected, battery not low");
    delay(1000);  // Add a delay to reduce the frequency of messages
  }
}
