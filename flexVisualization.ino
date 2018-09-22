#include "config.h"
#include <SoftwareSerial.h>

#define DEBUG true
#define RX 10
#define TX 11
SoftwareSerial esp8266(RX,TX);

String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";

String AP = wifi_SSID;//your AP name
String PASS = password ; //your  password
String API = API_key;//your API

int countTrueCommand;
int countTimeCommand;

boolean found = false;
int valSensor = 1;

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const int FLEX_PIN = A0; // Pin connected to voltage divider output
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg


void setup() {
  Serial.begin(115200);
  esp8266.begin(115200);
  
  Serial.println("AT+CWJAP=\""+AP+"\",\""+PASS+"\"");
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
  countTrueCommand = 0;

  pinMode(FLEX_PIN, INPUT);
}

void loop() {
 
  String readDat="GET https://api.thingspeak.com/channels/9/feeds.json?...";
  String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
  switch(countTrueCommand) {
//  case 0: sendCommand("AT",5,"OK");break;
//  case 1: sendCommand("AT+RST",10,"OK");break;
  case 0: sendCommand("AT+CIPMUX=1",5,"OK"); 
          break;
          
  case 1: sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
          break;    
                
  case 2:  valSensor = sendFlexData(); 
           sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
           break;
           
  case 3: Serial.println(getData);
          esp8266.println(getData);
          delay(1500);
          countTrueCommand++;
          break; 
          
  case 4: sendCommand("AT+CIPCLOSE=0",5,"OK");
          break;
          
  case 5: Serial.println(getData.length());
          countTrueCommand = 0;
          delay(16000);
          break;
  }
}

float sendFlexData(){
  // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  float flexV = flexADC * VCC / 1023.0;
  float flexR = R_DIV * (VCC / flexV - 1.0);
  //  Serial.println("Resistance: " + String(flexR) + " ohms");

  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  //  Serial.println("Bend: " + String(angle) + " degrees");
  //  Serial.println();
             
  valSensor = flexR; // random value, change with sensor value if using sensor
  return valSensor;
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");

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
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false){
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  found = false;
}
