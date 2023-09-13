/*
Traffic Light Controller with Red,Green, and Yellow lights

The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * LED red digital pin 10
 * LED yellow digital pin 9
 * LED green digital pin 8
 * Button 1 digital pin 6 (Adjust Red delay)
 * Button 2 digital pin  7 (Adjust Green delay)
 * Button 3 digital pin 13 (start/stop)

*/

#include <LiquidCrystal.h>

//delay variables
long redDelay = 1000;
long redSeconds = redDelay/1000;

long greenDelay = 1000;
long greenSeconds = greenDelay/1000;

//initialize Buttons
int button1 = 6;
int button2 = 7;
int button3 = 2;
//volatile int buttonFlag;  //interrupt

//initialize LEDs
int red= 10;
int yellow= 9;
int green= 8;

//initialize LCD
const int rs= 12, en= 11, d4=5, d5= 4, d6= 3, d7= 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    //attachInterrupt(digitalPinToInterrupt(button3), ISR_button, RISING);  //interrupt

    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);

    lcd.begin(16,2);
    lcd.print("Time Control");
    lcd.setCursor(0,1);
    lcd.print("Red:");
    lcd.print(redSeconds);  //located at (4,1)
    lcd.setCursor(7,1);
    lcd.print("Green:");
    lcd.print(greenSeconds);  //located at (13,1)

}

void loop() {

    setTime();
    delay(15);
    while(digitalRead(button3) == LOW)
    {
      changeLights();
    }
}

void changeLights() {
  //green for set amount of time
  digitalWrite(green, HIGH);
  delay(greenDelay);
  

  //yellow on for 2 seconds
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(2000);

  //red on for set amount of time
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(redDelay);
  digitalWrite(red, LOW);
}

void setTime()
{
 while(digitalRead(button3) == LOW)
 {
  //Adjust Red delay
  if(digitalRead(button1) == HIGH)
  {
    lcd.setCursor(4,1);
    redDelay = redDelay + 1000;
    redSeconds = redDelay/1000;
    lcd.print(redSeconds); //located at (5,1)
    delay(200);
    }

  //Adjust Green delay
   if(digitalRead(button2) == HIGH)
  {
    lcd.setCursor(13,1);
    greenDelay = greenDelay + 1000;
    greenSeconds = greenDelay/1000;
    lcd.print(greenSeconds); //located at (13,1)
    delay(200);

    }
  }
}


/*
void IRS_button{
  
}
*/
