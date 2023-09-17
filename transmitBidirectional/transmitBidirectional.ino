
// Code 2 : Push Button and LED (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);          // CE, CSN
const byte addresses[][10] = {"ADDRESS01" , "ADDRESS02"};

const int LED2_Pin = 3;    // Green LED
const int B2_Pin = 5;     // Pushbutton B2
char txt2[] = "B2", txt3[] = "00";

void setup() {
  Serial.begin(9600);
  pinMode(B2_Pin, INPUT);
  pinMode(LED2_Pin, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
};

void loop() {
  digitalWrite(LED2_Pin, LOW);
  radio.startListening();
  int B2_State = digitalRead(B2_Pin);

   if (B2_State == HIGH) {
     radio.stopListening();
     radio.write(&txt2, sizeof(txt2)); Serial.println("sent"); Serial.println(txt2);
   } 

   if (radio.available()) {
    char txt[2] = "";
    radio.read(&txt, sizeof(txt));
    switch (txt[1]) {
      case '2': digitalWrite(LED2_Pin, HIGH); break;
    }
    Serial.println("received");
    Serial.println(txt);
    delay(100);
  }
}
