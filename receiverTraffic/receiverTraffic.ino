
// Code 2 : Push Button and LED (Receiver)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8); // CE, CSN
const byte address[10] = "ADDRESS01";

const int LED2_Pin = 3;     // Green LED

void setup() {
  Serial.begin(9600);
  pinMode(LED2_Pin, OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
};

void loop() {
  if (radio.available()) {
    char txt[2] = "";
    radio.read(&txt, sizeof(txt));
    switch (txt[1]) {
      case '2': digitalWrite(LED2_Pin, HIGH); break;
      default : digitalWrite(LED2_Pin, LOW);  break;
    };
    Serial.println(txt);
    delay(100);
  };
};
