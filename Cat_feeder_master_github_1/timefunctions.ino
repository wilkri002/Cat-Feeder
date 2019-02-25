int timefunc() {
  DateTime now = rtc.now();       //start servo when time is right
  
  for(int clockRow = 0; clockRow < 2; clockRow++){
      if((now.hour() == clockTime[clockRow][0]) && (now.minute() == clockTime[clockRow][1]) && (rotationStarted == 0) && (lastTimeActivated != now.hour()) && (bowlState == 0)){
        startRotationFunc();              //start to feed
        lastTimeActivated = now.hour();   //record when cat was fed
    }
  }
                            //increase food amount if time is right
  if (lastTimeActivated != now.hour() && (rotationAmount > 0)) {
    rotationAmount--;
  }
}
