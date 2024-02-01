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
  <h4>1.2. Use of images on display</h4>
  <p>The images used in the OLED display are in byte array format. If you wish to use a different image at any time, you can use the following link: <a href="https://mischianti.org/images-to-byte-array-online-converter-cpp-arduino/">images to byte array online converter</a> the result of an example image will look like this: </p>
  <code>
        constunsignedcharcomprobar[]PROGMEM={0x00,0x01,0xfc,0x00,0x00,0x06,0x03,0x00,0x00,0x08,0x00,0x80,0x00,0x11,0xfc,0x20,0x00,0x22,0x03,0x10,0x00,0x44,0x00,0x90,0x00,0x88,0x70,0x48,0x00,0x90,0x50,0x48,0x00,0x90,0x20,0x24,0x00,0x20,0x30,0x24,0x01,0x20,0x50,0x24,0x01,0x20,0x50,0x24,0x01,0x20,0x50,0x24,0x00,0x00,0x50,0x24,0x00,0x90,0x50,0x24,0x00,0x90,0x50,0x48,0x00,0x48,0x30,0x88,0x00,0x44,0x01,0x10,0x00,0x63,0x06,0x20,0x03,0x90,0x78,0x40,0x06,0xdc,0x00,0x80,0x0c,0x63,0x07,0x00,0x00,0x20,0x70,0x00,0x30,0x60,0x00,0x00,0x60,0xc0,0x00,0x00,0xc1,0x80,0x00,0x00,0x83,0x00,0x00,0x00,0x86,0x00,0x00,0x00,0x8c,0x00,0x00,0x00,0x78,0x00,0x00,0x00};
  </code>
</p>