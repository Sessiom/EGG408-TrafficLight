/* Ultrasonic Sensor test
*/

const int trigPin = 9;
const int echoPin = 10;
const int LED = 7;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance >= 50 && distance <= 100){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }

}
