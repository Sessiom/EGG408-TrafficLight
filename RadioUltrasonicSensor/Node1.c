/*
Breadboard-
pin 3 Red LED
pin 6 Yellow LED
pin 7 trig
pin 4 echo

NRF24 Tranceiver-
pin 13 CLK
pin 12 MISO
pin 11 MOSI
pin 9 CE
pin 8 CSN

Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)
*/

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte addresses[][10] = {"ADDRESS01" , "ADDRESS02"};

//previous time for the tasks depending upon time
unsigned long prevTime = millis();

// time intervals for the tasks
long interval_T1 = 800; // blink every 1 second

bool isRedOn = false;


int yellowLED_state = LOW;

const int redLED = 3;      // Red LED
const int yellowLED = 6;   // Yellow LED
char txt2[] = "B2", txt3[] = "00";
long duration;
int distance;

/* ultrasonic sensor*/
const int trigPin = 7;
const int echoPin = 4;
const int greenLED = 5;

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  /* ultrasonic sensor setup */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLED, OUTPUT);

  
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
};

void loop() {

/* Set radio to recieve information */
radio.startListening();                  

/* Check the state of this light*/
  if(isRedOn == true){                   
    digitalWrite(redLED, HIGH);          
    }
  else if(isRedOn == false) {            
    flashYellow();
    }

    
/* ultrasonic testing */
  distance = ultraSonicRead();
  if(distance <= 10){
    digitalWrite(greenLED, HIGH);
  }
  else if(distance >=10){
    digitalWrite(greenLED, LOW);
  }

/* If a car is at the opposite light (A message is incoming and this light is yellow) */
    if(radio.available() && (isRedOn == false)) {         
      char txt[2] = "";
      radio.read(&txt, sizeof(txt));                      // read the information
      Serial.println("radio recieved");
      Serial.println(""); 
      radio.flush_rx();                                   // empty reciever buffer
       switch (txt[1]) {
          case '2': goToRed(); break;                     // go to red
          }
      radio.stopListening();                              // set radio to transmit information
      Serial.println("Sending Acknowledgement...");
      Serial.println("");
        for(int i=0; i<40; i++){
          radio.write(&txt3, sizeof(txt3));               // send acknowledgement message
        }
      //delay buffer
     }

/* Acknowledgement that a message was recieved (A message is incoming and this light is red) */
      if(radio.available() && (isRedOn == true)) {        
        char txt[2] = "";
        radio.read(&txt, sizeof(txt));                    // read the information
          switch (txt[1]) {
            case '0': 
              Serial.println("Recieved Acknowledgement");
              Serial.println("");
              delay(5000);                                // Wait 5 seconds for the car to exit
              digitalWrite(redLED, LOW); 
              isRedOn = false;                            // turn off red light 
              radio.flush_rx();
            break;                                        // will thengo to yellow
          } 
      }

/* If a car pull up to this light (Button is pressed and this light is red) */
   if (distance <= 10 && (isRedOn == true)) {    
     digitalWrite(greenLED, HIGH);  
     radio.stopListening();                               // set radio to transmit information
     Serial.println("Sending Message...");
     Serial.println("");
      for(int i=0; i<40; i++){
        radio.write(&txt2, sizeof(txt2));                 // send message
        }
     //delay buffer
   }  
}

void flashYellow() {
  unsigned long currentTime = millis();

  if(currentTime- prevTime> interval_T1){
    yellowLED_state = !yellowLED_state;
    digitalWrite(yellowLED, yellowLED_state);
    prevTime = currentTime;
  }
}

void goToRed() {
  digitalWrite(yellowLED, HIGH);
  delay(3000);
  digitalWrite(yellowLED, LOW); 
  digitalWrite(redLED, HIGH);
  isRedOn = true;
}

int ultraSonicRead() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;

    Serial.print("Distance: ");
    Serial.println(distance);

    return distance;
}


