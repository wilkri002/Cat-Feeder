void connectToWifi(){                  

  WiFi.begin(ssid, password);         //start wifi
  
  int loginTimer = millis()/1000;             //
  while (WiFi.status() != WL_CONNECTED) {     //connect to wifi
    delay(500);                               //
    if(loginTimer + 20 <= millis()/1000){     //if it takes too long, restart
      resetFunc();                            //
      }
  }
}

void MQTT_connect() {            //start a MQTT connection to website
  int8_t ret;

  if (mqtt.connected()) { // Stop if already connected.
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {   // connect will return 0 for connected
       mqtt.disconnect();                 //dsiconnect 
       delay(5000);                       // wait 5 seconds
       retries--;                         //
       if (retries == 0) {                //if it takes too long to connect to website, retasrt
         resetFunc();                     //restart
       }
  }
}
