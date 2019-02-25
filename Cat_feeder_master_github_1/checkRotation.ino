int checkRotation() {
  int IRvalue = 0;
  if (rotationStarted == 1){
    IRvalue = readIR(IRpinRotate, IRemitterRotate);   //read ir for rotation-thing
                                                      
    if (IRvalue == 0) {     //                        
      now1 = 1;             //
    }                       //check if feeder has rotated 
    else {                  //
      now1 = 0;             //
    }                       //
                            //
    if (now1 != last) {     //
      last = now1;          //if feeder has rotated, add that to the counter
      counter++;            //
    }
  }
                                                      
  if (counter >= 2 * rotationCounter[rotationAmount]) {  //stop if rotation is enough
    stopRotationFunc();
  }
                                                      
  if (counter > 2 * rotationCounter[rotationAmount] - 1) {  //reset counter, adjust how long rotation is boing to be
    counter = 0;
    if (rotationAmount < 2) {
      rotationAmount++;
    }
  }
}
