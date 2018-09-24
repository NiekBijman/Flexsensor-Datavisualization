# Visualize data from sensors
![Flexible](/images/flexData.v3.gif)

This project visualizes temperature and flexsensor data using the ESP8266_ESP-01 and Arduino to connect to a WiFi network which sends a HTTP request to the Thingspeak API. Here's the summary of the steps that need to be taken: 

Hardware
* Choose the type of data you would like to visualize. You can choose any sensor you would like. I have examples for the *DHT11 Temperature sensor* and *FlexSensor 4.5*. 
* Get the components (essential are Arduino/ESP8266-ESP-01/Logic level converter)
* Solder pins to the Logic Level Converter 

Software
* Clone/Download this repository 
* Choose the Temperature (tempData.ino) or Flexsensor (flexData.ino) example
* Insert your API Write key and Wifi settings
* Install and include the needed libaries in your sketch


## Hardware
#### Create the circuit
Find the needed components in this link: https://www.circuito.io/app?components=512,8606,11021,13678. <br/>
You will need to solder pins to the logic level converter. 

**NOTE:** The logic level converter is needed to convert the 5V arduino signal to a 3.3V signal. The 3.3V port on the Arduino can generate voltage spikes that could damage your ESP8266 board.

![Components](/images/Circuit-and-components.png)

## Software
* Clone this repository or download the zip
* Create an account on Thingspeak and find your **Write API key**
* Enter your **wifi-SSID**, **password** and **Write API key** from Thingspeak

#### Temperature Sensor
* Import the *SoftwareSerial* library and the *SimpleDHT* library.
* Importing a library: *Sketch -> Include Library -> Manage Libraries*. And search for *'Software Serial'* (library by Firmata) and *SimpleDHT* (library by Winlin)
* Include the library in the sketch: *Sketch -> Include Library -> SoftwareSerial* and *SimpleDHT*

#### Flex Sensor
* Import the *SoftwareSerial* library 
* Importing a library: *Sketch -> Include Library -> Manage Libraries*. And search for *'Software Serial'* (library by Firmata) 
* Include the library in the sketch: *Sketch -> Include Library -> SoftwareSerial*

Both the examples contain AT commands to establish a wifi connection with your modem. Here is a document that explains what each AT command means: https://www.espressif.com/sites/default/files/documentation/4b-esp8266_at_command_examples_en.pdf

![Circuit](/images/Setup.png)

This project is based on the following sources: 
* Using the ESP8266 WiFi Module with Arduino Uno publishing to ThingSpeak: https://medium.com/@cgrant/using-the-esp8266-wifi-module-with-arduino-uno-publishing-to-thingspeak-99fc77122e82
* Flex Sensor Hookup Guide: https://learn.sparkfun.com/tutorials/flex-sensor-hookup-guide
