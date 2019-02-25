int startRotationFunc(){
    DateTime now = rtc.now();         //used for now.hour()
    rotationStarted = 1;              //start counting rotations
    servoMaster(120);                 //start servo
    delayMultiplier = 1;              //more frequent updatecycles  
    lastTimeActivated = now.hour();   //records when food was given last
  }

int stopRotationFunc(){
    rotationStarted = 0;     //stops checking for rotation
    servoMaster(100);        //stops servo
    delayMultiplier = 10;    //less frequent updatescycles
  }


//press button to start servo
int buttonFunc(){
  buttonVal = digitalRead(buttonPin);
  if (buttonVal == 0){
    startRotationFunc();
    }
  }
  
//start/stop servo and turn on/off light
int servoMaster(int val){
    ledMaster(val);
    myservo.attach(6);    //attach servo
    myservo.write(val);   //start/stop servo
    if(val == 100){
    myservo.detach();     //detasch servo
    }
  }

int ledMaster(int val){           //feed light
    if(val == 120){               //
      digitalWrite(redLED, HIGH); //if feeding cat LED is high  
      }                           //
    else{                         //
      digitalWrite(redLED, LOW);  //if not feeding cat LED is low
      }                           //
}
