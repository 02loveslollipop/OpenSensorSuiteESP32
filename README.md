# OpenSensorSuite
> A simple sensor monitoring utility for ESP32 microcontrollers, powered by Python and Redis.

## Introduction
OpenSensorSuite is a simple sensor monitoring utility for ESP32 microcontrollers using a RedisDB for the data persistence. It is designed to be a simple, lightweight, and easy to use solution for monitoring sensor data from ESP32 microcontrollers. This repository contains the source code for ESP32 firmware required to run on the microcontroller to send data to the RedisDB.The source code for the GUI to view the data can be found can be found [here](https://github.com/02loveslollipop/OpenSensorSuite-ESP32).

## Installation

1. Clone the repository
```sh
git clone https://github.com/02loveslollipop/OpenSensorSuiteESP32.git
```

2. Install Arduino IDE
- ubuntu/debian
  ```sh
  sudo apt install arduino
  ```
- arch/manjaro
  ```sh
  sudo pacman -S arduino
  ```
- windows: winget (option 1)
  ```powershell
  winget install --id=ArduinoSA.IDE.stable  -e
  ```
- windows: installer (option 2)

  - Download the installer from [here](https://www.arduino.cc/en/software)
  - Run the installer



3. Copy the `example_config.h` file to `config.h`
```sh
cp example_config.h config.h
```

4. Edit the `config.h` file to match your configuration
```c
const char[] wifi_ssid = "YOUR_WIFI_SSID"; //Change this to your WiFi SSID
const char[] wifi_password = "YOUR_WIFI_PASSWORD"; //Change this to your WiFi password
const char[] redis_address = "redis-13959.c228.us-central1-1.gce.cloud.redislabs.com"; //Change this to your Redis address
const int redis_port = 13959; //Change this to your Redis port
const char[] redis_password = "wVdsBAqzCaWtaOC7DLVeuj2SuMuZc1dm"; //Change this to your Redis password
const char[] redis_key = "example_sensor"; //Change this to your Redis key
const char* ntpServer = "pool.ntp.org"; //Change this to your NTP server
const long gmtOffset_sec = 0; //Change this to your GMT offset in seconds
const int daylightOffset_sec = 0; //Change this to your daylight offset in seconds
```

5. Open the `OpenSensorSuiteESP32.ino` file in Arduino IDE

6. Upload the code to your ESP32

## Notes

1. You must have the ESP32 board manager installed in Arduino IDE. If you don't have it installed, follow the instructions [here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/).

2. You need a redis database to store the data. You can create a free redis database [here](https://redislabs.com/).

3. The `ESP32-BACK.ino` file contains the `getData()` function which is used to get the data from the ESP32. You can modify this function to get the data from your sensors. 

