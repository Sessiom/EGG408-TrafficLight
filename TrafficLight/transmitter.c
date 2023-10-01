
// Code 2 : Push Button and LED (Transmitter)
// Library: TMRh20/RF24 (https://github.com/tmrh20/RF24/)

#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9, 8);           // CE, CSN
const byte addresses[][10] = {"ADDRESS01" , "ADDRESS02"};

//previous time for the tasks depending upon time
unsigned long prevTime = millis();

// time intervals for the tasks
long interval_T1 = 1000; // blink every 1 second

bool isRedOn = true;        //Starts with a red light

bool isYellowOn = false;
int yellowLED_state = LOW;

const int redLED = 3;       // Red LED
const int yellowLED = 4;    // yellow LED
const int button = 7;       // Pushbutton 
char txt2[] = "B2", txt3[] = "00";

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
};

void loop() {
  radio.startListening();        //set radio to receive information
   if(isRedOn == false) {        //check if red lights are off
    flashYellow();
    }
   else if(isRedOn == true){     //check if red lights are on
    digitalWrite(redLED,HIGH);   
   }

  int button_state = digitalRead(button);   //check state of the button

   if(radio.available() && (isRedOn == false)) {  // if a car pulls up to the opposite light
    char txt[2] = "";
    radio.read(&txt, sizeof(txt));                 // read the information
    switch (txt[1]) {
      case '2': goToRed(); Serial.println("received"); break;                  // go to red
    }

    delay(100);
    }

   if (button_state == HIGH && (isRedOn == true)) {    // if a car pulls up to the red light
     radio.stopListening();                        // set radio to transmit information
     for(int i = 0; i < 20; i++){
     radio.write(&txt2, sizeof(txt2)); Serial.println("sent"); Serial.println(txt2);
     }
     delay(5000);                                  // Wait 5 seconds for Car to exit
     digitalWrite(redLED, LOW); 
     isRedOn = false;                              // turn off red light
     isYellowOn = true;                            // turn on yellow light
     radio.flush_rx();
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
  isYellowOn = false;
  digitalWrite(redLED, HIGH); 
  isRedOn = true;
}
