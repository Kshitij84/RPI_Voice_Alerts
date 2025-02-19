const int Emergency_button = 2;
const int trigPin = 9;
const int echoPin = 10;
int Emergency_button_state = 0;
int lastEmergency_button_state = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int pot = A0;
int PotValue = 0;
float duration, distance;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial OK");

  pinMode(Emergency_button, INPUT);
  pinMode(pot, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;

  int reading = digitalRead(Emergency_button);

  if (reading != lastEmergency_button_state) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != Emergency_button_state) {
      Emergency_button_state = reading;

      if (Emergency_button_state == HIGH) {
        Serial.println("Emergency_Pressed");
      }
    }
  }

  lastEmergency_button_state = reading;

  PotValue = analogRead(pot);

  if (Emergency_button_state == HIGH) {
    Serial.println("Emergency_Pressed");
    delay(1000);
  }
  else if (distance < 15) {
    Serial.println("Obstacle_Detected");
  }
  else if (PotValue < 40) {
    Serial.println("battery_low");
  }
  else {
    Serial.println("Emergency not pressed, Obstacle not detected, battery not low");
    delay(1000);
  }
}
