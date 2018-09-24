# Visualize data from sensors
![Flexible](/images/flexData.v3.gif)

This project visualizes temperature and flexsensor data using the ESP8266_ESP-01 and Arduino to connect to a WiFi network which sends an HTTP request to the Thingspeak API. You can sent an HTTP request every 15 seconds. 

## Hardware
#### Create the circuit
Choose the type of data you would like to visualize. I have examples for the *DHT11 Temperature sensor* and *FlexSensor 4.5*. You can find the components in this link: 

https://www.circuito.io/app?components=512,8606,11021,13678. <br/>

To plug the ESP8266-ESP-01 in a breadboard you need male-to-female jumper wires. You will need to solder male headers to the logic level converter. If you haven't done this before check out this instruction video for THT (through hole soldering) https://goo.gl/GJt3Qc.

![Components](/images/Circuit-and-components.v2.png)
**NOTE:** The logic level converter is needed to convert the 5V arduino signal to a 3.3V signal. The 3.3V port on the Arduino can generate voltage spikes that could damage your ESP8266 board.

## Software
* Clone this repository or download the zip
* Create an account on Thingspeak and find your **Write API key**
![Circuit](/images/Thingspeak-Write-API-key.png)

#### General
* In the Serial Monitor set the Baudrate to *115200* and select the *"Both NL & CR"* in the *'No Line Ending'* dropdown. These settings make sure that you can read the data that's being printed to the Serial monitor. 
* Enter your **wifi-SSID**, **password** and **Write API key** from Thingspeak in the .ino file

#### Temperature Sensor
* Import the *SoftwareSerial* library and the *SimpleDHT* library. Importing a library: *Sketch -> Include Library -> Manage Libraries*. And search for *'Software Serial'* (library by Firmata) and *SimpleDHT* (library by Winlin)
* Include the library in the sketch: *Sketch -> Include Library -> SoftwareSerial* and *SimpleDHT*

#### Flex Sensor
* Import the *SoftwareSerial* library. Importing a library: *Sketch -> Include Library -> Manage Libraries*. And search for *'Software Serial'* (library by Firmata) 
* Include the library in the sketch: *Sketch -> Include Library -> SoftwareSerial*

Both the examples contain AT commands to establish a wifi connection with your modem. Here is a document that explains what each AT command means: https://www.espressif.com/sites/default/files/documentation/4b-esp8266_at_command_examples_en.pdf

![Circuit](/images/Setup.png)

This project is based on the following sources: 
* Using the ESP8266 WiFi Module with Arduino Uno publishing to ThingSpeak: https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
* Flex Sensor Hookup Guide: https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide
