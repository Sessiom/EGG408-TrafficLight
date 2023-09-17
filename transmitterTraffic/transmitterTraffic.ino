
// Code 2 : Push Button and LED (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte address[10] = "ADDRESS01";

const int B2_Pin = 5;     // Pushbutton B2
char txt2[] = "B2", txt3[] = "00";

void setup() {
  Serial.begin(9600);
  pinMode(B2_Pin, INPUT);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
};

void loop() {
  int B2_State = digitalRead(B2_Pin);
  

   if (B2_State == HIGH) {
     radio.write(&txt2, sizeof(txt2)); Serial.println(txt2);
   } 
   else {
      radio.write(&txt3, sizeof(txt3)); Serial.println(txt3);
   };
   delay(100);
};
