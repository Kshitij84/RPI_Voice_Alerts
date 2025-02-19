const int Emergency_button = 2;
const int trigPin = 9;  
const int echoPin = 10;
int Emergency_button_state = 0;
int ledPin = 13;
float duration, distance;




void setup(){
  Serial.begin(115200);
  Serial.println("Serial OK");
  pinMode(Emergency_button, INPUT);
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);
}

void loop(){
  

  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  
  Emergency_button_state = digitalRead(Emergency_button);

  if (Emergency_button_state == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Emergency_Pressed");
    delay(1000);
    
  }else if(distance < 15){
    Serial.println("Obstacle_Detected");
  }else {
    digitalWrite(ledPin, LOW);
    Serial.println("Emergency not pressed, Obstacle not detected");
    delay(1000);
  }
}
