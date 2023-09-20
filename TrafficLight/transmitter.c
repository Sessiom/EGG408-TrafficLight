
// Code 2 : Push Button and LED (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte addresses[][10] = {"ADDRESS01" , "ADDRESS02"};

bool redON = true;
bool yellowON = false;
const int redLED = 3;     // Red LED
const int yellowLED = 4;  // yellow LED
const int B2_Pin = 7;     // Pushbutton B2
char txt2[] = "B2", txt3[] = "00";

void setup() {
  Serial.begin(9600);
  pinMode(B2_Pin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
};

void loop() {
  radio.startListening();
   if(redON == false) {
    flashYellow();
    }
  redLight();
  int B2_State = digitalRead(B2_Pin);

   if (B2_State == HIGH) {
     radio.stopListening();
     radio.write(&txt2, sizeof(txt2)); Serial.println("sent"); Serial.println(txt2);
     delay(5000);                                                                    // Wait for Car to exit
     digitalWrite(redLED, LOW); 
     redON = false;
   } 

   if (radio.available()) {
    char txt[2] = "";
    radio.read(&txt, sizeof(txt));
    switch (txt[1]) {
      case '2': digitalWrite(redLED, HIGH); break;
    }
    Serial.println("received");
    Serial.println(txt);
    delay(100);
  }
}

void goToRed() {
  digitalWrite(yellowLED, HIGH);
  delay(3000);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH); redON = true;
}

void flashYellow() {
  digitalWrite(yellowLED, HIGH);
  delay(500);
  digitalWrite(yellowLED, LOW);
  delay(500);
  yellowON = true;
}

void redLight() {
  if(yellowON == false) {
    digitalWrite(redLED, HIGH);
    }
  else{
    digitalWrite(redLED, LOW);
    redON = false;
  }
}

