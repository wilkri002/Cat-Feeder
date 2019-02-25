int checkBowl(){                                //check if there is food in the bowl
  int bowlValue;
  bowlValue = readIR(IRpinBowl, IRemitterBowl); //read IR in bowl
  if(bowlValue > -3){                           //chech if there is food is bowl
    bowlState = 1;                              // bowl is full
    }
    
  else{                                         //
    bowlState = 0;                              //bowl is empty
    }                                           //
}


void atBowl(){                                            //check if the cat is eating
  const int secondLimit = 10;                             //does not count if the cat eats fro less than 5 seconds
  int distance = readIR(IRpinAtBowl, IRemitterAtBowl);    //read IR if the cat is there
  
  DateTime now = rtc.now();                   //start RTC
  unsigned long timer = now.unixtime();       //UNIX timer used for counting how long cat is eating
  
  if(-1*distance > 135){                      //see if cat is close to bowl
    ledMaster(120);                           //turn on LED
    if(startTimer == 0){                      //if cat is close to bowl record base time
      startTimer = now.unixtime();            //start timer after 10 seconds
      }
    
    if(startTimer + secondLimit == timer){    //check if cat is there after 10 seconds
      isEating = 1;                           //isEsting = 1 if cat is actually eating
      }
    }
    
  else{
    ledMaster(100);                           //turn off LED
    if(isEating == 1){                        //if cat is done eating
      isEating = 0;                           //reset variables
      int timeEaten = timer - startTimer;     //calculate how long the cat has eaten
      ESPsend(78, timeEaten);                 //send timeEaten to ESP
      }                                       //
    startTimer = 0;                           //reset timer when everything is done
    }
}
