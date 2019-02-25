void sendFunc(){                                                  //sending commands to the Arduino
  Adafruit_MQTT_Subscribe *subscription;
  while(subscription = mqtt.readSubscription(2000)){              //look for mesages from website
    if (subscription == &catFeederButton) {                       // Check if its the "feed button" feed
      if(strcmp((char *)catFeederButton.lastread, "1") == 0) {    //check if online button is activated
        Serial.write("["); // send "feed cat" to arduino          //send "[" to Arduino, which means feed cat   
        }
      }
  }
  
  if(! mqtt.ping()) {     // ping the website to keep the mqtt connection alive
    mqtt.disconnect();    //otherwise disconnect
  }
}

void reciveFunc(){
  if (Serial.available() > 0){                // listen for user input from Arduino
    int serialString = Serial.read();         //save input type
    int dataToIO = Serial.read();             //save data from Arduino

    if(serialString == 78){                   //if serialString == 78, means has recorded how long the cat has eaten
      timeFeed.publish(dataToIO);             //send time data to website
    }
  }
}
