#include <Arduino.h>

#define echoPin1 5
#define trigPin1 4
#define echoPin2 3
#define trigPin2 2
#define onboard 13

int carCount = 0;
bool prevCarCheck1 = false;
bool currentCarCheck1 = false;
bool prevCarCheck2 = false;
bool currentCarCheck2 = false;
unsigned long prevMillis1 = 0;
unsigned long prevMillis2 = 0;
const long interval1 = 100; // 1/10 second
const long interval2 = 250; // 1/4 second

void setup() {
  pinMode(onboard, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
}

void UltrasonicRead1(); // Declare the function UltrasonicRead1 car counter
void UltrasonicRead2(); // Declare the function UltrasonicRead2 car subtractor

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - prevMillis1 >= interval1) {
    prevMillis1 = currentMillis;
    UltrasonicRead1();
  }
  if (currentMillis - prevMillis2 >= interval2) {
    UltrasonicRead2();
    prevMillis2 = currentMillis;
    
  }
}


/* CarCounter*/
void UltrasonicRead1(){
    long duration, distance;
    digitalWrite(trigPin1, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin1, LOW);
    duration = pulseIn(echoPin1, HIGH);
    distance = (duration/2) / 29.1;
    //Serial.println(distance);
    if (distance < 10) { 
      digitalWrite(onboard, HIGH);
      currentCarCheck1 = true;
      if (currentCarCheck1 && !prevCarCheck1) {
        carCount++;
        Serial.println(carCount);
      }
    } else {
      digitalWrite(onboard, LOW);
      currentCarCheck1 = false;
    }
    prevCarCheck1 = currentCarCheck1;
}

/* CarSubtractor */
void UltrasonicRead2(){
    long duration, distance;
    digitalWrite(trigPin2, LOW);  
    delayMicroseconds(2); 
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin2, LOW);
    duration = pulseIn(echoPin2, HIGH);
    distance = (duration/2) / 29.1;
    //Serial.println(distance);
    if (distance < 10) { 
      digitalWrite(onboard, HIGH);
      currentCarCheck2 = true;
      if (currentCarCheck2 && !prevCarCheck2) {
        carCount--;
        Serial.println(carCount);
      }
    } else {
      digitalWrite(onboard, LOW);
      currentCarCheck2 = false;
    }
    prevCarCheck2 = currentCarCheck2;
}