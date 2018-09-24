/*
 created Feb 2018
 by Christopher Grant
 modified Sep 2018
 by Nicolaas Bijman

 Source: "Using the ESP8266 WiFi Module with Arduino Uno publishing to ThingSpeak"
 https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
*/


//NOTE: I use a local config.h file which is not in the repository to store my password, SSID and API_keys. 
//Uncomment '#include "config.h"' and fill in your own Wifi and API information below 
#include "config.h"

//SoftwareSerial.h is used to simulate the RX and TX ports (ports 1 and 2) on arduino. 
//Go to: Sketch -> Include Library -> Manage Libraries. And search for 'Software Serial'. Install the library by Firmata
//Then: Sketch -> Include Library -> SoftwareSerial
#include <SoftwareSerial.h>
#include <SimpleDHT.h>

//Define the simulated ports to be 10 and 11, which leaves the RX and TX ports open for other functions. 
#define RX 10
#define TX 11
SoftwareSerial esp8266(RX,TX);

int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

//Thingspeak api url
String HOST = "api.thingspeak.com";
// HTTP port 
String PORT = "80";
// field2 is the graph in which the data is uploaded on thingspeak.
String FIELD = "field2";

// NOTE: In this project the ESP8266 acts as a gateway to an existing wifi network, it does not create a WiFi server. 
//replace 'wifi_SSID' with your WiFi's network name and place it in double quotes. For example "myWiFi" (case sensitive)
String WIFI = wifi_SSID;

//replace 'password' with your WiFi's password and place it in double quotes. For example "myPassword" (case sensitive)
String PASSWORD = password; 

//replace 'API_key' with your 'Thingspeak Write API' key and place it in double quotes. For example "94AKWEGJKLJLWM7" (case sensitive)
String API = API_key;//your API

//The AT commands go through several steps in order to create an HTTP request. We start at step 1.
int Step = 1;
int countTimeCommand ;

boolean found = false;
int valSensor = 0;

//FLEXSENSOR
// Measure the voltage at 5V and the actual resistance of your 47k resistor, and enter them below:
const int FLEX_PIN = A3; // Pin connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg


void setup() {
  //Set the baudrate in your serial monitor to 115200
  Serial.begin(115200);
  esp8266.begin(115200);

  //Flexsensor port
  pinMode(FLEX_PIN, INPUT);

  //ESTABLISH ROUTER CONNECTION
  //Test if AT system works correctly
  Serial.println("Your WiFi credentials: "+WIFI+"\",\""+PASSWORD+"\"" +"\n");
  sendCommand("AT",5,"OK"); //"Test if AT system works correctly",
 
  //Set WiFi mode
  sendCommand("AT+CWMODE=1",5,"OK"); //,"Set WiFi mode"
  
  //Connect to a router
  sendCommand("AT+CWJAP=\""+ WIFI +"\",\""+ PASSWORD +"\"",10,"OK"); //,"Connect to a router"
  

}

void loop() {
  //Here we send data to Thingspeak every 16 seconds using AT commands
  String getData = "GET /update?api_key="+ API +"&"+ FIELD +"="+String(valSensor);

  //HTTP REQUEST
  switch(Step) {
          //Enable multiple connections
  case 4: sendCommand("AT+CIPMUX=1",5,"OK"); 
          break;
          
          //ESP8266 connects to the server as a TCP client
  case 5: sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
          break;  
            
           //Update the flexsensor value before sending the value to Thingspeak
  case 6:  valSensor = updateTemperatureValue(); 
           //Send HTTP Request
//           Serial.print(getData);
           sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
           break;
           
  case 7: esp8266.println(getData);
          // Short delay to give data time to transmit to ESP8266
          delay(1500);
          //End the TCP connection
          sendCommand("AT+CIPCLOSE=0",5,"OK"); //
          break;

           //Message update interval limit for free Thingspeak API is 15 seconds https://thingspeak.com/prices/thingspeak_academic
  case 8: delay(15000);
          Step = 4;
          break;
  }
}


void sendCommand(String command, int maxTime, char readReplay[]) { //
  Serial.print("Step ");
  Serial.print(Step);
  Serial.print("\t Command: " + command);
  Serial.print(" ");
  Serial.println();
  
  while(countTimeCommand < (maxTime*1))
  {  
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay)){ //ok
      found = true;
      break;
    }
    countTimeCommand++;
  }
  if(found == true){
    Serial.println("Success \n");
    Step++;
    countTimeCommand = 0;
  }
  
  if(found == false){
    Serial.println("Fail \n");
    if(Step <= 3){
      resetBoard();
    }
    else{
      Step = 4;
    }
    countTimeCommand = 0;
  }
  found = false;
}

// Restarting the connection if you cannot log in with your password/SSID
void resetBoard(){
  if(Step == 3){
    Serial.println("Couldn't connect to the network. Please check your WiFi password and SSID");
    sendCommand("AT+RST",10,"OK");
    Step = 1;
  }
  else{
    Serial.println("Attempting connection again");
    sendCommand("AT+RST",10,"OK");
  }


}

int updateTemperatureValue(){
    // read without samples.
    byte temperature = 0;
    byte humidity = 0;
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
      return;
    }
    
//    Serial.print("Sample OK: ");
//    Serial.print((int)temperature); Serial.print(" *C, "); 
//    Serial.print((int)humidity); Serial.println(" H");
    return temperature;
    // DHT11 sampling rate is 1HZ.
    delay(1500);
}
