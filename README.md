# Flexsensor Datavisualization
This project visualizes flexsensor data using the ESP8266_ESP-01 to connect to a WiFi network which sends a HTTP request to the Thingspeak API.

![Flexible](/images/flexData.gif)

## 1. Create the circuit. 
Find the needed components in this link: https://www.circuito.io/app?components=512,8606,11021,13678. <br/>

**NOTE:** The logic level converter is needed to convert the 5V arduino signal to a 3.3V signal. The 3.3V port on the Arduino can generate voltage spikes that could damage your ESP8266 board, this is why the level converter is utilized. 

![Components](/images/Circuit-and-components.png)

## 2. Set up repository
* Clone this repository or download the zip
* Create an account on Thingspeak and find your **Write API key**
* Open the flexVisualization.ino and enter your **wifi-SSID**, **password** and **Write API key** from Thingspeak
* Import the **SoftwareSerial** library (see comments in the .ino file)
   
![Circuit](/images/Setup.png)

This project is based on the following sources: 
* Using the ESP8266 WiFi Module with Arduino Uno publishing to ThingSpeak: https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
* Flex Sensor Hookup Guide: https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide
