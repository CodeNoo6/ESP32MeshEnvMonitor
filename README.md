<p align="center">
  <img src="https://github.com/CodeNoo6/ESP32MeshEnvMonitor/blob/master/Images/UniversidadLogo.png?raw=true" alt="UniversidadLogo">
  <h3 align="center"><i>Environmental Data Acquisition System</i></h3>
  <p align="center"><i>Vargas Edwin - Camargo Ruben - Quirama Miguel - Sanchez Joaquín - Martínez Darwin - Salazar Camilo</i></p>
  <p align="center">IoT Device for Environmental Variables Monitoring</p>
  <img src="https://github.com/CodeNoo6/ESP32MeshEnvMonitor/blob/master/Images/Diseño.png?raw=true" alt="UniversidadLogo">
  <p>The device is composed of the following modules:</p>
  <ul>
    <li>A. LILYGO T7 V1.3 MINI 32 ESP32</li>
    <li>B. PM 2.5 Air/Dust Particle Sensor G5 PMS500</li>
    <li>C. NEO6MV2 GPS</li>
    <li>D. DHT11 Temperature and Humidity sensor</li>
    <li>E. DS3231 Real Time Clock Module</li>
    <li>F. Micro SD TF Card Memory</li>
    <li>G. 1.3-inch OLED display module with 128 x 64</li>
    <li>H. Li-ion/Li-Po 500mA 3.7V</li>
  </ul>
  <hr>
  <h3>Pin description in lilygo t7 v1.3 mini 32 ESP32</h3>
  <p>Using the following datasheet corresponding to the ESP32, the pins for each component are described:</p>
  <img src="https://github.com/CodeNoo6/ESP32MeshEnvMonitor/blob/master/Images/ESP_Datashet.jpg?raw=true" alt="UniversidadLogo">
  <p>PM 2.5 Air/Dust Particle Sensor G5 PMS500: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>RX: 25</li>
    <li>TX: 32</li>
  </ul>
  <p>NEO6MV2 GPS: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>RX: 17</li>
    <li>TX: 16</li>
  </ul>
  <p>DHT11 Temperature and Humidity sensor: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>SDA: 21</li>
    <li>SCL: 22</li>
  </ul>
  <p>DS3231 Real Time Clock Module: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>Data: 21</li>
  </ul>
  <p>Micro SD TF Card Memory: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>MOSI: 23</li>
    <li>MISO: 19</li>
    <li>CS: 5</li>
    <li>SCK: 18</li>
  </ul>
  <p>Buttons: </p>
  <ul>
    <li>VCC: 5v</li>
    <li>MOSI: 23</li>
    <li>MISO: 19</li>
    <li>CS: 5</li>
    <li>SCK: 18</li>
  </ul>
  <p>1.3-inch OLED display module with 128 x 64: </p>
  <ul>
    <li>VCC: 5v </li>
    <li>MOSI: 23</li>
    <li>MISO: 19</li>
    <li>CS: 5</li>
    <li>SCK: 18</li>
  </ul>
  <hr>
  <h3>1. Installation and use</h3>
  <hr>
  <h4>1.1. Installation of Libraries</h4>
  <p>Download the folder from <a href="Source code/libraries">libraries</a> paste it in your Arduino IDE libraries folder, generally it is in:</p>
  <p>Documents/Arduino/libraries</p>
  <p>In the script they look like this <a href="Source code/sketch_jan25a.ino">source code</a>:</p>
  <code>
        #include "SPI.h"
        #include "Wire.h"
        #include "SoftwareSerial.h"
        #include "Adafruit_SSD1306.h"
        #include "Fonts/FreeSerif12pt7b.h"
        #include "Fonts/FreeSansBold12pt7b.h"
        #include "Fonts/FreeMonoOblique12pt7b.h"
        #include "Fonts/FreeMonoBold12pt7b.h"
        #include "Fonts/FreeSansOblique12pt7b.h"
        #include "TinyGPS++.h"
        #include "DHT.h"
        #include "RtcDS3231.h"
        #include "FS.h"
        #include "SD.h"
        #include "math.h"
        #include "painlessMesh.h"
        #include "Adafruit_Sensor.h"
        #include "Fonts/FreeSans12pt7b.h"
        #include "Arduino.h"
        #include "Sensirion_GadgetBle_Lib.h"
        #include "Adafruit_PM25AQI.h"
        #include "SPI.h"
        #include "WiFi.h"
        #include "Firebase_ESP_Client.h"
        #include "addons/TokenHelper.h"
        #include "Fonts/FreeSerifBoldItalic9pt7b.h"
        #include "BluetoothSerial.h"
        #include "RTClib.h"
  </code>
  <p>In the Arduino IDE environment, download and paste into a new sketch <a href="Source code/sketch_jan25a.ino">source code</a> click on verify so that everything is working correctly.</p>
  <h4>1.2. Code Explanation</h4>
  <code>
        const unsigned char logo_ste [] PROGMEM = {
        0x08, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 
        0xff, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 
        0x07, 0xf8, 0x00, 0x00, 0x03, 0xfc, 0x60, 0x00, 0x01, 0xfc, 0xf0, 0x00, 0x01, 0xf9, 0xf8, 0x00, 
        0x00, 0xff, 0xf8, 0x00, 0x10, 0x6f, 0xf0, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x20, 0x1f, 0xc0, 0x00, 
        0x20, 0x0f, 0xd8, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x32, 0x7c, 0x00, 0x00, 0x30, 0xfe, 0x00, 
        0x00, 0x00, 0xff, 0x00, 0x20, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x0f, 0xf0, 
        0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x83, 0xf8, 0x00, 0x82, 0x01, 0xf0, 
        0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x40
    };
    const unsigned char blue[] PROGMEM={
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf3, 0xe0, 
        0x00, 0x00, 0x00, 0x00, 0x80, 0xf1, 0xe0, 0x00, 0x00, 0x00, 0x01, 0xe0, 0xf0, 0xf0, 0x00, 0x00, 
        0x00, 0x03, 0xe0, 0xf0, 0x78, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf0, 0x78, 0x00, 0x00, 0x00, 0x00, 
        0xf8, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfb, 
        0xe0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 
        0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
        0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0x00, 0x00, 
        0x00, 0x00, 0x3e, 0xf3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7c, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x01, 
        0xf8, 0xf0, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xf0, 0xf0, 0x7c, 0x00, 0x00, 0x00, 0x03, 0xe0, 0xf0, 
        0xfc, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x71, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x80, 0x73, 0xf0, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char Sensirion [750] PROGMEM = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xe0, 0xe0, 0x07, 
        0xe0, 0x18, 0x7e, 0x3c, 0x00, 0x71, 0xc0, 0x0f, 0x8f, 0xc0, 0x7c, 0x3f, 0x00, 0xc0, 0x07, 0xc0, 
        0x18, 0x7e, 0x3c, 0x00, 0x71, 0xc0, 0x0f, 0x8f, 0x80, 0x7c, 0x3f, 0x00, 0x80, 0x07, 0xc0, 0x18, 
        0x3e, 0x38, 0x00, 0x71, 0xc0, 0x07, 0x8f, 0x00, 0x3c, 0x3f, 0x00, 0x80, 0x07, 0x80, 0x18, 0x3e, 
        0x38, 0x00, 0x71, 0xc0, 0x07, 0x8f, 0x00, 0x3c, 0x1f, 0x00, 0x80, 0x07, 0x80, 0x18, 0x3e, 0x38, 
        0x00, 0x71, 0xc0, 0x07, 0x8f, 0x00, 0x3c, 0x1f, 0x00, 0x80, 0x07, 0x80, 0x18, 0x3e, 0x38, 0x00, 
        0x71, 0xc0, 0x03, 0x8f, 0x00, 0x1c, 0x1f, 0x00, 0x80, 0x07, 0x00, 0x18, 0x3e, 0x30, 0x00, 0x71, 
        0xc0, 0x03, 0x8e, 0x0c, 0x1c, 0x1f, 0x00, 0x0f, 0xff, 0x0f, 0xf8, 0x3e, 0x30, 0xff, 0xf1, 0xc7, 
        0xc3, 0x8e, 0x1e, 0x1c, 0x1f, 0x00, 0x0f, 0xff, 0x0f, 0xf8, 0x1e, 0x30, 0xff, 0xf1, 0xc7, 0xe3, 
        0x8e, 0x1f, 0x1c, 0x0f, 0x00, 0x1f, 0xff, 0x1f, 0xf8, 0x1e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8e, 
        0x3f, 0x1c, 0x0f, 0x00, 0x1f, 0xff, 0x1f, 0xf8, 0x1e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8e, 0x3f, 
        0x0c, 0x0f, 0x00, 0x1f, 0xff, 0x1f, 0xf8, 0x1e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8e, 0x3f, 0x0c, 
        0x0f, 0x00, 0x1f, 0xff, 0x1f, 0xf8, 0x9e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x3f, 0x8c, 0x4f, 
        0x00, 0x1f, 0xfe, 0x1f, 0xf8, 0x9e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x3f, 0x8c, 0x4f, 0x00, 
        0x1f, 0xfe, 0x3f, 0xf8, 0x8e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x7f, 0x8c, 0x47, 0x00, 0x1f, 
        0xfe, 0x3f, 0xf8, 0x8e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x7f, 0x8c, 0x47, 0x00, 0x1f, 0xfe, 
        0x3f, 0xf8, 0x8e, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x7f, 0x8c, 0x47, 0x00, 0x1f, 0xfe, 0x3f, 
        0xf8, 0xce, 0x31, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x7f, 0x8c, 0x47, 0x00, 0x0f, 0xfe, 0x3f, 0xf8, 
        0xce, 0x30, 0xff, 0xf1, 0xc7, 0xe3, 0x8c, 0x7f, 0x8c, 0x67, 0x00, 0x07, 0xfe, 0x00, 0x18, 0xce, 
        0x30, 0x7f, 0xf1, 0xc7, 0xc3, 0x8c, 0x7f, 0x8c, 0x67, 0x00, 0x80, 0x0e, 0x00, 0x18, 0xc6, 0x30, 
        0x01, 0xf1, 0xc0, 0x03, 0x8c, 0x7f, 0x8c, 0x63, 0x00, 0x80, 0x0e, 0x00, 0x18, 0xc6, 0x38, 0x00, 
        0xf1, 0xc0, 0x03, 0x8c, 0x7f, 0x8c, 0x63, 0x00, 0x80, 0x06, 0x00, 0x18, 0xc6, 0x38, 0x00, 0xf1, 
        0xc0, 0x07, 0x8c, 0x7f, 0x8c, 0x63, 0x00, 0x80, 0x06, 0x00, 0x18, 0xc6, 0x38, 0x00, 0x71, 0xc0, 
        0x07, 0x8c, 0x7f, 0x8c, 0x63, 0x00, 0xc0, 0x06, 0x00, 0x18, 0xe6, 0x3c, 0x00, 0x71, 0xc0, 0x07, 
        0x8c, 0x7f, 0x8c, 0x73, 0x00, 0xc0, 0x06, 0x00, 0x18, 0xe6, 0x3c, 0x00, 0x71, 0xc0, 0x0f, 0x8c, 
        0x7f, 0x8c, 0x73, 0x00, 0xe0, 0x06, 0x00, 0x38, 0xe2, 0x3e, 0x00, 0x71, 0xc0, 0x0f, 0x8c, 0x7f, 
        0x8c, 0x71, 0x00, 0xff, 0xc6, 0x3f, 0xf8, 0xe2, 0x3f, 0xf8, 0x71, 0xc0, 0x1f, 0x8c, 0x7f, 0x8c, 
        0x71, 0x00, 0xff, 0xc6, 0x3f, 0xf8, 0xe2, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8c, 0x7f, 0x8c, 0x71, 
        0x00, 0xff, 0xc6, 0x3f, 0xf8, 0xf2, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8c, 0x7f, 0x8c, 0x79, 0x00, 
        0xff, 0xe2, 0x3f, 0xf8, 0xf2, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8c, 0x7f, 0x8c, 0x79, 0x00, 0xff, 
        0xe2, 0x3f, 0xf8, 0xf0, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8c, 0x7f, 0x8c, 0x79, 0x00, 0xff, 0xe2, 
        0x3f, 0xf8, 0xf0, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8c, 0x3f, 0x8c, 0x78, 0x00, 0xff, 0xe2, 0x1f, 
        0xf8, 0xf0, 0x3f, 0xfc, 0x71, 0xc7, 0x8f, 0x8e, 0x3f, 0x8c, 0x78, 0x00, 0xff, 0xe3, 0x1f, 0xf8, 
        0xf0, 0x3f, 0xfc, 0x71, 0xc7, 0xc7, 0x8e, 0x3f, 0x0c, 0x78, 0x00, 0xff, 0xc3, 0x1f, 0xf8, 0xf8, 
        0x3f, 0xfc, 0x71, 0xc7, 0xc7, 0x8e, 0x3f, 0x0c, 0x7c, 0x00, 0xff, 0xc7, 0x1f, 0xf8, 0xf8, 0x3f, 
        0xfc, 0x71, 0xc7, 0xc7, 0x8e, 0x3f, 0x1c, 0x7c, 0x00, 0xff, 0xc7, 0x0f, 0xf8, 0xf8, 0x3f, 0xfc, 
        0x71, 0xc7, 0xc7, 0x8e, 0x1f, 0x1c, 0x7c, 0x00, 0xff, 0x87, 0x0f, 0xf8, 0xf8, 0x3f, 0xf8, 0x71, 
        0xc7, 0xc7, 0x8e, 0x1e, 0x1c, 0x7c, 0x00, 0x80, 0x07, 0x00, 0x18, 0xf8, 0x38, 0x00, 0x71, 0xc7, 
        0xc7, 0x8e, 0x0c, 0x1c, 0x7c, 0x00, 0x80, 0x07, 0x80, 0x18, 0xf8, 0x38, 0x00, 0x71, 0xc7, 0xe3, 
        0x8f, 0x00, 0x1c, 0x7c, 0x00, 0x80, 0x07, 0x80, 0x18, 0xfc, 0x38, 0x00, 0x71, 0xc7, 0xe3, 0x8f, 
        0x00, 0x3c, 0x7e, 0x00, 0x80, 0x0f, 0x80, 0x18, 0xfc, 0x38, 0x00, 0xf1, 0xc7, 0xe3, 0x8f, 0x00, 
        0x3c, 0x7e, 0x00, 0x80, 0x0f, 0xc0, 0x18, 0xfc, 0x38, 0x00, 0xf1, 0xc7, 0xe3, 0x8f, 0x00, 0x3c, 
        0x7e, 0x00, 0x80, 0x0f, 0xc0, 0x18, 0xfc, 0x38, 0x01, 0xf1, 0xc7, 0xe3, 0x8f, 0x80, 0x7c, 0x7e, 
        0x00, 0x80, 0x1f, 0xe0, 0x18, 0xfc, 0x38, 0x01, 0xf1, 0xc7, 0xe1, 0x8f, 0xc0, 0x7c, 0x7e, 0x00, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xe0, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0
    };
    const unsigned char fire [750] PROGMEM = {
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
        0xfc, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf1, 
        0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf7, 0xe0, 
        0x0f, 0xe0, 0x03, 0x1f, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf7, 0xe0, 0x6f, 
        0xe0, 0x03, 0x1f, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf7, 0xff, 0xef, 0xe0, 
        0x03, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xf7, 0xff, 0xef, 0xe3, 0xff, 
        0x39, 0xdf, 0x1f, 0x18, 0x7f, 0x0f, 0xf1, 0xfe, 0x3f, 0xe0, 0xf3, 0xff, 0xcf, 0xe3, 0xff, 0x10, 
        0x1c, 0x07, 0x00, 0x3c, 0x03, 0xc0, 0x78, 0x0f, 0xe0, 0xf0, 0x7c, 0x0f, 0xe0, 0x07, 0x10, 0x18, 
        0x03, 0x00, 0x1c, 0x01, 0x80, 0x70, 0x07, 0xe0, 0xf6, 0x00, 0x6f, 0xe0, 0x07, 0x10, 0x71, 0xe3, 
        0x0f, 0x0f, 0xf1, 0x8f, 0xe3, 0xc3, 0xe0, 0xf7, 0xff, 0xef, 0xe0, 0x07, 0x10, 0xf1, 0xf1, 0x1f, 
        0x8f, 0xf0, 0x83, 0xe3, 0xe3, 0xe0, 0xf7, 0xff, 0xef, 0xe3, 0xff, 0x10, 0xf0, 0x01, 0x1f, 0x8c, 
        0x00, 0xc0, 0x60, 0x03, 0xe0, 0xf3, 0xff, 0x8f, 0xe3, 0xff, 0x11, 0xf1, 0xff, 0x1f, 0x88, 0x70, 
        0xf8, 0x23, 0xff, 0xe0, 0xf0, 0x00, 0x0f, 0xe3, 0xff, 0x11, 0xf1, 0xff, 0x0f, 0x08, 0xf0, 0xfe, 
        0x23, 0xff, 0xe0, 0xf7, 0xc1, 0xef, 0xe3, 0xff, 0x11, 0xf8, 0x03, 0x00, 0x18, 0x60, 0x84, 0x30, 
        0x07, 0xe0, 0xf7, 0xff, 0xef, 0xe3, 0xff, 0x11, 0xf8, 0x03, 0x00, 0x3c, 0x00, 0x80, 0x78, 0x07, 
        0xe0, 0xf7, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfc, 0xfe, 0x3f, 0xf1, 0xfe, 0x1f, 0xe0, 
        0xf0, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xfe, 
        0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0
    };
    const unsigned char UniversidadSergioArboleda[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xcd, 0xd2, 0x56, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xcd, 0xd2, 0x56, 0xff, 0xff, 0xee, 0x8d, 0x87, 0x40, 0x83, 0x66, 0xc3, 0xe7, 0x0f, 0xff, 0xff,
    0xcd, 0xd2, 0x56, 0xff, 0xff, 0xce, 0x85, 0xa7, 0x4f, 0xbb, 0x76, 0xdd, 0xd7, 0x73, 0xff, 0xff,
    0xcd, 0xd0, 0x56, 0xff, 0xff, 0xde, 0x91, 0xb6, 0x4d, 0xbb, 0x3e, 0xde, 0xd7, 0x7b, 0xff, 0xff,
    0xc9, 0x92, 0xd6, 0xff, 0xff, 0xde, 0x99, 0xb2, 0xcd, 0x87, 0x8e, 0xde, 0xd3, 0x79, 0xff, 0xff,
    0xca, 0xd2, 0xd6, 0xff, 0xff, 0x9e, 0x9d, 0xb8, 0xcf, 0xb7, 0xf6, 0xde, 0xfb, 0x79, 0xff, 0xff,
    0xca, 0xd2, 0xd6, 0xff, 0xff, 0xce, 0x9d, 0xb9, 0xcf, 0xb2, 0xf6, 0xde, 0xbb, 0x7b, 0xff, 0xff,
    0xca, 0xd2, 0xcc, 0xff, 0xff, 0xe0, 0x9d, 0xb9, 0xce, 0xbb, 0x66, 0xd9, 0xb9, 0x67, 0xff, 0xff,
    0xcc, 0xd2, 0x5c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc6, 0x11, 0xda, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc2, 0x43, 0xc2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc8, 0x71, 0xfe, 0xf6, 0xce, 0xb3, 0xb3, 0x76, 0xfe, 0x73, 0x66, 0xf6, 0x67, 0x9d, 0x67, 0x9f,
    0xcf, 0x03, 0xfe, 0xe6, 0xcf, 0xbb, 0x77, 0x6f, 0x7e, 0x7b, 0x37, 0x6f, 0x67, 0x9f, 0x73, 0x9f,
    0xcf, 0xf3, 0xfe, 0xf3, 0xc1, 0xbb, 0x7f, 0x6f, 0x3d, 0xbb, 0x36, 0xef, 0xa7, 0x83, 0x79, 0x6f,
    0xcf, 0xf3, 0xfe, 0xfc, 0xcf, 0xa7, 0x7b, 0x6f, 0xbd, 0x3a, 0x76, 0xef, 0xa7, 0x9f, 0x79, 0x4f,
    0xcf, 0xf3, 0xfe, 0xfe, 0x4f, 0xb7, 0x7b, 0x6f, 0x7f, 0x9b, 0x77, 0x6f, 0x27, 0x9f, 0x79, 0xe7,
    0xe7, 0xf3, 0xf9, 0xee, 0x4f, 0xbb, 0x3b, 0x6f, 0x7f, 0x9b, 0x77, 0x67, 0x67, 0x9d, 0x72, 0xe7,
    0xf3, 0xf3, 0xf3, 0xf0, 0xe1, 0xbb, 0xc3, 0x70, 0xfb, 0xdb, 0xb0, 0x70, 0xe0, 0xc1, 0x06, 0xf7,
    0xfc, 0x73, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x13, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };
    const unsigned char logo[] PROGMEM = {
    0xff, 0x9f, 0xf0, 0xff, 0x9f, 0xf0, 0xee, 0x07, 0x70, 0xc0, 0x00, 0x30, 0xe0, 0xf0, 0x70, 0xe3,
    0xfc, 0x70, 0xe7, 0xce, 0x70, 0xc7, 0xe7, 0x30, 0xcf, 0xe3, 0x30, 0x0d, 0xe3, 0x00, 0x0c, 0xe3,
    0x00, 0x8c, 0x03, 0xb0, 0xc6, 0x01, 0xf0, 0xe7, 0x00, 0xf0, 0xe3, 0xf0, 0x70, 0xe1, 0xf8, 0x30,
    0xc0, 0x0c, 0x10, 0xee, 0x0e, 0x00, 0xff, 0x0f, 0x00, 0xff, 0x9f, 0x90

    };
    const unsigned char icon_hot[] PROGMEM = {
    0xff, 0xef, 0xf0, 0xff, 0xc7, 0xf0, 0xff, 0x87, 0xf0, 0xff, 0x87, 0xf0, 0xff, 0x03, 0xf0, 0xff,
    0x01, 0xf0, 0xff, 0x00, 0xf0, 0xf3, 0x00, 0xf0, 0xe3, 0x00, 0x70, 0xe0, 0x00, 0x70, 0xe0, 0x00,
    0x70, 0xe0, 0x00, 0x70, 0xe0, 0x00, 0x70, 0xe0, 0x20, 0x70, 0xe0, 0x30, 0x70, 0xe0, 0x70, 0x70,
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xfc, 0xf1, 0xf0, 0xfe, 0x07, 0xf0
    };
    const unsigned char location[] PROGMEM = {
    0xff, 0x0f, 0xf0, 0xfc, 0x03, 0xf0, 0xf8, 0x01, 0xf0, 0xf0, 0x00, 0xf0, 0xf0, 0xf0, 0xf0, 0xf1,
    0xf8, 0xf0, 0xf1, 0xf8, 0xf0, 0xf1, 0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0x00, 0xf0, 0xf8, 0x01,
    0xf0, 0xfc, 0x03, 0xf0, 0xfc, 0x03, 0xf0, 0xfe, 0x07, 0xf0, 0xe3, 0x0c, 0x70, 0xc1, 0x08, 0x30,
    0x81, 0x98, 0x10, 0xc0, 0x90, 0x30, 0xe0, 0x60, 0x70, 0xf8, 0x01, 0xf0
    };
    const unsigned char icon_humedity[] PROGMEM = {
    0xff, 0x9f, 0xf0, 0xff, 0x9f, 0xf0, 0xff, 0x2f, 0xf0, 0xfe, 0x67, 0xf0, 0xfc, 0xf3, 0xf0, 0xfd,
    0xfb, 0xf0, 0xfb, 0xfd, 0xf0, 0xf3, 0xfc, 0xf0, 0xf4, 0x3e, 0xf0, 0xe4, 0xb3, 0x70, 0xee, 0x27,
    0x70, 0xef, 0xcf, 0x70, 0xef, 0x9f, 0x70, 0xef, 0x3f, 0x70, 0xee, 0x47, 0x70, 0xec, 0xd3, 0x70,
    0xf7, 0xc2, 0xf0, 0xf3, 0xfc, 0xf0, 0xfc, 0xf1, 0xf0, 0xfe, 0x07, 0xf0
    };
    const unsigned char temperature[] PROGMEM = {
    0xfe, 0x3f, 0xf0, 0xfc, 0xdf, 0xf0, 0xfd, 0xe8, 0xf0, 0xfd, 0xe9, 0xf0, 0xfd, 0xef, 0xf0, 0xfd,
    0x68, 0xf0, 0xfd, 0x6f, 0xf0, 0xfd, 0x68, 0xf0, 0xfd, 0x6f, 0xf0, 0xfd, 0x68, 0xf0, 0xfd, 0x69,
    0xf0, 0xfd, 0x6f, 0xf0, 0xf9, 0x67, 0xf0, 0xf2, 0x37, 0xf0, 0xf6, 0xd3, 0xf0, 0xf4, 0xd3, 0xf0,
    0xf2, 0x17, 0xf0, 0xfb, 0x37, 0xf0, 0xf9, 0xcf, 0xf0, 0xfe, 0x1f, 0xf0
    };
    const unsigned char clockl[] PROGMEM = {
    0xfe, 0x07, 0xf0, 0xf8, 0x01, 0xf0, 0xe0, 0x00, 0x70, 0xc0, 0x60, 0x30, 0xc0, 0x60, 0x30, 0x80,
    0x60, 0x10, 0x80, 0x60, 0x10, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60,
    0x00, 0x00, 0x18, 0x00, 0x00, 0x1c, 0x00, 0x80, 0x0c, 0x10, 0x80, 0x00, 0x10, 0xc0, 0x00, 0x30,
    0xc0, 0x00, 0x30, 0xe0, 0x00, 0x70, 0xf8, 0x01, 0xf0, 0xfe, 0x07, 0xf0
    };
    const unsigned char loading[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
    0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char icon_temperature[] PROGMEM = {
    0x00, 0x70, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00,
    0x01, 0xfc, 0x00, 0x00, 0x3d, 0xfc, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00,
    0x0d, 0xfc, 0x00, 0x00, 0x01, 0xfc, 0x7e, 0x70, 0x0d, 0xfc, 0x42, 0x58, 0x01, 0xfc, 0xc3, 0x70,
    0x39, 0xfc, 0xc0, 0x00, 0x3d, 0xdc, 0xc0, 0x00, 0x01, 0xdc, 0xc0, 0x00, 0x0d, 0xdc, 0xc0, 0x00,
    0x01, 0xdc, 0xc0, 0x00, 0x01, 0xdc, 0xc3, 0x00, 0x0d, 0xdc, 0x42, 0x00, 0x01, 0xdc, 0x3c, 0x00,
    0x3d, 0xdc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00,
    0x01, 0x8e, 0x00, 0x00, 0x03, 0x8e, 0x00, 0x00, 0x03, 0x8e, 0x00, 0x00, 0x01, 0xfe, 0x00, 0x00,
    0x01, 0xfc, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00
    };
    const unsigned char icon_reloj[] PROGMEM = {
    0x00, 0x1f, 0xe0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x00,
    0x0f, 0xff, 0xff, 0xc0, 0x0f, 0xfc, 0xff, 0xc0, 0x1f, 0xfc, 0xff, 0xe0, 0x3f, 0xfc, 0xff, 0xf0,
    0x3f, 0xfc, 0xff, 0xf0, 0x7f, 0xfc, 0xff, 0xf8, 0x7f, 0xfc, 0xff, 0xf8, 0xff, 0xfc, 0xff, 0xfc,
    0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0x7f, 0xfc,
    0xff, 0xfe, 0x3f, 0xfc, 0xff, 0xff, 0x1f, 0xfc, 0xff, 0xff, 0x8f, 0xfc, 0x7f, 0xff, 0xc7, 0xf8,
    0x7f, 0xff, 0xe7, 0xf8, 0x3f, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xe0,
    0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0x80, 0x01, 0xff, 0xfe, 0x00,
    0x00, 0x7f, 0xfc, 0x00, 0x00, 0x1f, 0xe0, 0x00
    };
    const unsigned char schedule[] PROGMEM = {
    0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x7f, 0xff, 0xe0, 0xd8, 0x01, 0xb0, 0xd8, 0x01, 0xb0, 0xc0,
    0x00, 0x30, 0xff, 0xff, 0xf0, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30, 0xd3, 0x6c, 0xb0, 0xd2, 0x64,
    0xb0, 0xc0, 0x00, 0x30, 0xd3, 0x6c, 0xb0, 0xd3, 0x6c, 0xb0, 0xc0, 0x00, 0x30, 0xd2, 0x64, 0x30,
    0xd3, 0x6c, 0x30, 0xc0, 0x00, 0x30, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xe0
    };
    const unsigned char satelite[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x02, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x3e, 0x00, 0x00, 0x00,
    0x03, 0x9c, 0x00, 0x00, 0x00, 0x19, 0xc8, 0x00, 0x00, 0x30, 0x3c, 0xe0, 0x00, 0x00, 0x7e, 0x3e,
    0x60, 0x00, 0x00, 0xff, 0x1f, 0x00, 0x00, 0x00, 0xff, 0x9f, 0x80, 0x00, 0x00, 0x7f, 0xf7, 0x00,
    0x00, 0x00, 0xff, 0xe2, 0x00, 0x00, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xf8, 0x00, 0x00,
    0x00, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0xcf, 0xfc, 0x00, 0x00, 0x01,
    0xfb, 0xf8, 0x00, 0x00, 0x01, 0xf9, 0xf9, 0xfc, 0x00, 0x04, 0xfc, 0xe7, 0xfe, 0x00, 0x0e, 0x7c,
    0x47, 0xfe, 0x00, 0x07, 0x38, 0x0f, 0xfc, 0x00, 0x33, 0x90, 0x0f, 0xf8, 0x00, 0x79, 0xc0, 0x0f,
    0xf0, 0x00, 0x7c, 0xc0, 0x0f, 0xe0, 0x00, 0x3e, 0x00, 0x0f, 0xdc, 0x00, 0x1f, 0x00, 0x0f, 0x98,
    0x12, 0x0e, 0x00, 0x0f, 0x11, 0x12, 0x04, 0x00, 0x06, 0x01, 0x12, 0x00, 0x00, 0x00, 0x0e, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x01, 0x8c, 0x00,
    0x00, 0x00, 0x0e, 0x18, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00,
    0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char longitud[] PROGMEM = {
    0x00, 0x7f, 0x00, 0x00, 0x01, 0xeb, 0xc0, 0x00, 0x05, 0x2a, 0x50, 0x00, 0x0a, 0x49, 0x28, 0x00,
    0x12, 0x49, 0x24, 0x00, 0x24, 0x49, 0x12, 0x00, 0x24, 0x88, 0x90, 0x00, 0x48, 0x88, 0x89, 0x00,
    0x48, 0x88, 0x89, 0x00, 0x88, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x80,
    0x88, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x80, 0x88, 0x88, 0x88, 0x80,
    0x48, 0x88, 0x89, 0x00, 0x48, 0x88, 0x89, 0x00, 0x24, 0x88, 0x90, 0x00, 0x24, 0x49, 0x12, 0x00,
    0x12, 0x49, 0x24, 0x00, 0x0a, 0x49, 0x28, 0x00, 0x05, 0x2a, 0x50, 0x00, 0x01, 0xeb, 0xc0, 0x00,
    0x00, 0x7f, 0x00, 0x00
    };
    const unsigned char latitud[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00,
    0x00, 0xff, 0x80, 0x00, 0x03, 0xf7, 0xe0, 0x00, 0x07, 0x63, 0x30, 0x00, 0x06, 0x63, 0x10, 0x00,
    0x0c, 0x63, 0x18, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x1f, 0xc1, 0xfc, 0x00, 0x1c, 0x41, 0x9c, 0x00,
    0x3d, 0xdd, 0xde, 0x00, 0x1c, 0xc1, 0x9c, 0x00, 0x1f, 0xc1, 0xfc, 0x00, 0x0f, 0xff, 0xf8, 0x00,
    0x0c, 0x63, 0x18, 0x00, 0x04, 0x63, 0x10, 0x00, 0x06, 0x63, 0x30, 0x00, 0x03, 0xf7, 0xe0, 0x00,
    0x00, 0xff, 0x80, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
    };
    const unsigned char check[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00, 0x03, 0xfc,
    0x00, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x3f, 0xc0,
    0x00, 0x00, 0x7f, 0x80, 0x38, 0x00, 0xff, 0x00, 0x7c, 0x01, 0xfe, 0x00, 0xfe, 0x03, 0xfc, 0x00,
    0xff, 0x07, 0xf8, 0x00, 0x7f, 0x8f, 0xf0, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0xc0, 0x00,
    0x0f, 0xff, 0x80, 0x00, 0x07, 0xff, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00,
    0x00, 0xf8, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char icon_sd[] PROGMEM = {
    0x01, 0xff, 0xff, 0xc0, 0x03, 0xfd, 0xdf, 0xe0, 0x03, 0x9d, 0xdc, 0xe0, 0x03, 0x9d, 0xdc, 0xe0,
    0x03, 0x9d, 0xdc, 0xe0, 0x03, 0x9d, 0xdf, 0xe0, 0x03, 0x9d, 0xdf, 0xe0, 0x03, 0xfd, 0xff, 0xe0,
    0x03, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0,
    0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0,
    0x07, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0,
    0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xfe, 0x18, 0xe0, 0x1f, 0xfc, 0xf8, 0x60,
    0x1f, 0xfd, 0x98, 0xe0, 0x1f, 0xfd, 0x8a, 0x60, 0x1f, 0xfc, 0x18, 0x60, 0x1f, 0xff, 0x39, 0xe0,
    0x1f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0
    };
    const unsigned char ready[] PROGMEM = {
    0x00, 0x1f, 0xe0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x00,
    0x0f, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0xf0,
    0x3f, 0xff, 0xff, 0xf0, 0x7f, 0xff, 0xf9, 0xf8, 0x7f, 0xff, 0xf0, 0xf8, 0xff, 0xff, 0xe0, 0xfc,
    0xff, 0xff, 0xc0, 0xfc, 0xff, 0xff, 0x81, 0xfc, 0xfc, 0x3f, 0x03, 0xfc, 0xfc, 0x1e, 0x07, 0xfc,
    0xfc, 0x0c, 0x0f, 0xfc, 0xfe, 0x00, 0x1f, 0xfc, 0xff, 0x00, 0x3f, 0xfc, 0x7f, 0x80, 0x7f, 0xf8,
    0x7f, 0xc0, 0xff, 0xf8, 0x3f, 0xe1, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xe0,
    0x0f, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0x80, 0x01, 0xff, 0xfe, 0x00,
    0x00, 0x7f, 0xfc, 0x00, 0x00, 0x1f, 0xe0, 0x00
    };
    const unsigned char wifi[] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xe0, 
        0x3f, 0x80, 0x07, 0xf0, 0xfc, 0x00, 0x00, 0xfc, 0xf0, 0x00, 0x00, 0x3c, 0xe0, 0x7f, 0xf8, 0x1c, 
        0x01, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x00, 0x07, 0xc0, 0x0f, 0x80, 0x07, 0x00, 0x03, 0x80, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x7f, 0xf8, 0x00, 
        0x00, 0x70, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 
        0x00, 0x07, 0x80, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char icon_dust [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x07, 0x80, 0x60, 0x00, 0x0f, 0x80, 0x70, 
        0x00, 0x0f, 0xc0, 0x20, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 
        0x1a, 0x30, 0x0f, 0x80, 0x14, 0x20, 0x0f, 0x80, 0x28, 0x00, 0xff, 0x80, 0x2c, 0x01, 0x3f, 0x60, 
        0x10, 0x01, 0x7f, 0xf8, 0x0f, 0xf1, 0xff, 0xf8, 0x00, 0x00, 0x70, 0xf8, 0x3f, 0xe7, 0xf7, 0xf8, 
        0x00, 0x05, 0xef, 0xf0, 0x3f, 0x85, 0xff, 0xd0, 0x60, 0x05, 0xff, 0xd0, 0x58, 0x03, 0xfd, 0x90, 
        0x50, 0x00, 0x18, 0xe0, 0x48, 0x00, 0x00, 0x00, 0x3c, 0x40, 0x00, 0x00, 0x00, 0x60, 0x0e, 0x00, 
        0x00, 0x00, 0x0f, 0x80, 0x00, 0x02, 0x0f, 0x80, 0x00, 0x07, 0x1f, 0x80, 0x00, 0x07, 0x1f, 0x80, 
        0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char cargaExitosa [160] PROGMEM = {
        0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 
        0xff, 0xff, 0xff, 0xc4, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xf8, 0x00, 
        0xff, 0xff, 0xf8, 0x0c, 0xff, 0xff, 0xf0, 0x1c, 0xff, 0xff, 0xe0, 0x3c, 0xff, 0xff, 0xc0, 0x7c, 
        0xff, 0xff, 0x80, 0xfc, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xfe, 0x07, 0xfc, 
        0xff, 0xfc, 0x0f, 0xfc, 0xff, 0xfc, 0x0f, 0xfc, 0xff, 0xf8, 0x1f, 0xfc, 0xcf, 0xf0, 0x3f, 0xfc, 
        0x87, 0xf0, 0x7f, 0xfc, 0x03, 0xe0, 0xff, 0xfc, 0x01, 0xc0, 0xff, 0xfc, 0x01, 0xc1, 0xff, 0xfc, 
        0x81, 0x81, 0xff, 0xfc, 0x80, 0x83, 0xff, 0xfc, 0xc0, 0x03, 0xff, 0xfc, 0xc0, 0x07, 0xff, 0xfc, 
        0xc0, 0x07, 0xff, 0xfc, 0xe0, 0x0f, 0xff, 0xfc, 0xe0, 0x0f, 0xff, 0xfc, 0xe0, 0x1f, 0xff, 0xfc, 
        0xf0, 0x1f, 0xff, 0xfc, 0xf0, 0x3f, 0xff, 0xfc, 0xf8, 0x7f, 0xff, 0xfc, 0xfc, 0xff, 0xff, 0xfc, 
        0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xfc
    };
    const unsigned char tranfiriendo [120] PROGMEM = {
        0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x01, 0xf0, 0x00, 
        0x07, 0xc3, 0xff, 0x80, 0x1f, 0xc7, 0xff, 0xe0, 0x3f, 0xc7, 0xff, 0xf0, 0x7f, 0x83, 0xff, 0xf8, 
        0x7e, 0x01, 0xf1, 0xf8, 0xfc, 0x00, 0xf0, 0x7c, 0xf8, 0x00, 0x70, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 
        0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 
        0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x00, 0x00, 0x7c, 0xf8, 0x38, 0x00, 0x7c, 
        0xf8, 0x3c, 0x00, 0x7c, 0x7c, 0x3e, 0x00, 0xf8, 0x7f, 0xff, 0x07, 0xf8, 0x3f, 0xff, 0x8f, 0xf0, 
        0x1f, 0xff, 0x8f, 0xe0, 0x0f, 0xff, 0x0f, 0xc0, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 
        0x00, 0x38, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00
    };
    const unsigned char comprobar[] PROGMEM = {
    0x00, 0x01, 0xfc, 0x00, 0x00, 0x06, 0x03, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 0x11, 0xfc, 0x20,
    0x00, 0x22, 0x03, 0x10, 0x00, 0x44, 0x00, 0x90, 0x00, 0x88, 0x70, 0x48, 0x00, 0x90, 0x50, 0x48,
    0x00, 0x90, 0x20, 0x24, 0x00, 0x20, 0x30, 0x24, 0x01, 0x20, 0x50, 0x24, 0x01, 0x20, 0x50, 0x24,
    0x01, 0x20, 0x50, 0x24, 0x00, 0x00, 0x50, 0x24, 0x00, 0x90, 0x50, 0x24, 0x00, 0x90, 0x50, 0x48,
    0x00, 0x48, 0x30, 0x88, 0x00, 0x44, 0x01, 0x10, 0x00, 0x63, 0x06, 0x20, 0x03, 0x90, 0x78, 0x40,
    0x06, 0xdc, 0x00, 0x80, 0x0c, 0x63, 0x07, 0x00, 0x00, 0x20, 0x70, 0x00, 0x30, 0x60, 0x00, 0x00,
    0x60, 0xc0, 0x00, 0x00, 0xc1, 0x80, 0x00, 0x00, 0x83, 0x00, 0x00, 0x00, 0x86, 0x00, 0x00, 0x00,
    0x8c, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00
    };
  </code>
</p>