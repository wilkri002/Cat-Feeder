#include <Wire.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "RTClib.h"

SoftwareSerial ESPserial(2, 3); // RX | TX, pins to connect to ESP
Servo myservo;                  //servo attached to pin 6
RTC_DS1307 rtc;                 //start RTC

const int IRpinRotate = A0;        //used for checking rotation of feeder
const int IRpinBowl = A2;          //used for checking food amount in the bowl
const int IRpinAtBowl = A3;        //used for checking if the cat is eating
const int IRemitterRotate = 9;     //used for checking rotation of feeder
const int IRemitterBowl = 5;       //used for checking food amount in the bowl
const int IRemitterAtBowl = 4;     //used for checking if the cat is eating
const int buttonPin = 7;           //used for "feed button"
const int redLED = 8;              //LED
//servoPin = 6;  

bool buttonVal;                     //value from "feed button"
bool rotationStarted;               //1 or 0 when motor is on or off
bool buttonPressed;                 //states if button is pressed or not
bool bowlState;                     //states if bowl is full or empty
bool isEating = 0;                  //state if cat is eating

int counter;                        //counts how much rotation is left
int now1;                           //used for counting rotation
int last;                           //used for counting rotation
int rotationCounter[] = {4, 3, 2};  //says how many times the feeder should rotate
int rotationAmount = 0;             //
int clockTime[2][2] = {             //says when to feed the cat
    {7, 35},                        //
    {20, 25}                        //
};                                  //
int lastTimeActivated;              //records the last time servo was activated
int delayMultiplier = 1;            //how long the daelay is
int serialVal = 0;                  //used for ESP communictation     
unsigned long startTimer;           //timer for how long the cat has been eating


void setup() {
   rtc.begin();                 //start RTC

  ESPserial.begin(9600);                //start communication with ESP
  
  pinMode(IRemitterRotate, OUTPUT);     //prepare IR-pin
  pinMode(IRemitterBowl, OUTPUT);       //prepare IR-pin
  pinMode(IRemitterAtBowl, OUTPUT);     //prepare IR-pin
  pinMode(buttonPin ,INPUT_PULLUP);     //prepare feed button
  pinMode(redLED, OUTPUT);              //prepare LED-pin
  digitalWrite(IRemitterRotate, LOW);   //set IR-pin to low
  digitalWrite(IRemitterBowl, LOW);     //set IR-pin to low
  digitalWrite(IRemitterAtBowl, LOW);   //set IR-pin to low
  digitalWrite(redLED, LOW);            //set LED-pin to low
  myservo.attach(6);        //start servo
  myservo.write(100);       //put in "stop" position
  myservo.detach();         //detach because otherwise the servo shakes
  
  lastTimeActivated = -1;       //record last time the feed was activated
}

void loop() {
  buttonFunc();                 //check if button is pressed
  timefunc();                   //check if it is time to feed the cat
  checkRotation();              //check if it should stop the feeder
  checkBowl();                  //check is there is food the the bowl
  ESPlisten();                  //listen for commands from ESP
  delay(100*delayMultiplier);   
}
