#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 
const char* ssid     = "SSID";      //wifi name
const char* password = "PWD";       //wifi password

// Adafuit IO Settings
#define username  "username"               //username for website
#define key       "API-key"                //API-key for sending to website
#define server      "io.adafruit.com"      //website to connect to
#define serverport  8883                   // use 8883 for SSL

WiFiClientSecure client;                                                          //Start WiFi
Adafruit_MQTT_Client mqtt(&client, server, serverport, username, username, key);  //connect to website

//Set ut feeder button feed
Adafruit_MQTT_Publish timeFeed = Adafruit_MQTT_Publish(&mqtt, username "/feeds/timefeed");                    //setup feed for logging when the cat has eaten
Adafruit_MQTT_Subscribe catFeederButton = Adafruit_MQTT_Subscribe(&mqtt, username "/feeds/catfeederbutton");  //setup fedd for online feed button

void(* resetFunc) (void) = 0;     //resets the ESP

void setup() {
  Serial.begin(9600);   //start communication with Arduino
  delay(100);
  
  connectToWifi();    //Connect to WiFi
  mqtt.subscribe(&catFeederButton);//Subscribe to "feed button" feed
}

void loop() {
  MQTT_connect(); //start and maintain connection with website
  sendFunc();     // send message to Arduino
  reciveFunc();   // recive message from Arduino
  delay(50);
}
