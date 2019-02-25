int ESPsend(char sendState, int val){           //
  if(ESPserial.available()){                    //if communication with ESP is ready
    ESPserial.write(sendState);                 //Send "ready to send"
    ESPserial.write(val);                       //send data to ESP
  }
}

void ESPlisten(){                               //
  if(ESPserial.available()){                    //listen for input from ESP
    serialVal = ESPserial.read();               //
    }                                                 

  if(serialVal == 91){                          //if Arduino recives 91 start to feed, ascii character "[" = 91
    serialVal = 0;                              //restet serialVal
    startRotationFunc();                        //feed the cat
    //Serial.println("91 activated");           //used for debugging
    }
}
