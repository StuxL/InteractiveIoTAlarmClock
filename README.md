
# IoT Interactive Alarm Clock

> Hardware/Software requirements and Installation instructions

**Hardware**

- Arduino MKR1000
- Particle Argon
- SPI 128 x 128 pixel 16-bit colour LCD (ST7735)
- 3x push button
- Breadboard
- Piezo Buzzer
- Tri-axis digital tilt sensor (MMA8452Q)

**Software**

***Arduino Libraries:***

- Adafruit ST7735 and ST7789 Library by Adafruit
- WiFi101 by Arduino
- ArduinoJSON by BenoitBlanchon


***Circuit sketch diagram***

![sketch diagram](/images/arduino_particle_schematic.png)

### Modules
| Module        | MKR1000       | Function              |
| ------------- | ------------- | --------------------- |
| Piezo Buzzer  | D4            | Digital Pin           |
| Down Button   | D11           | Digital Pin           |
| Enter Button  | D12           | Digital Pin           |
| Up Button     | D1            | Digital Pin           |

### ST7735 Display
| ST7735        | MKR1000       | Function              |
| ------------- | ------------- | --------------------- |
| LED           | VCC           | Display Backlight     |
| SCK           | D9 (SCK)      | SPI Serial Clock Line |
| SDA           | D8 (MOSI)     | SPI Serial Data Line	|
| A0            | D3            | Display contrast   	|
| RESET         | D2            | Reset safety pin      |
| CS            | D6            | Identify slave device |
| GND			| GND			| Ground pin			|
| VCC			| 5V			| 5V Power Supply       |

### Digital Tilt Sensor
| MMA8452Q      | Argon         | Function              |
| ------------- | ------------- | --------------------- |
| GND           | GND           | Ground Pin            |
| VCC           | 3V3           | 3.3V power supply     |
| SDA           | D8 (MOSI)     | SPI Serial Data Line	|
| A0            | D3            | Display contrast   	|

## Installation

---

### arduino_secrets.h

```C++
#define SECRET_SSID "WIFI SSID"
#define SECRET_PASS "WIFI PASSWORD"
```

---

1.	Following the device schematic to attach the piezo buzzer and push buttons to the Arduino MKR1000 device digital pins.
2.	Attach the LCD display to the MKR1000 via the onboard Serial Peripheral Interface
4.	Install and load the required software libraries via arduino IDE
5.	Load the .ino and developed C++ code to the Arduino IDE
6.	Within “Arduino_secrets.h” update with valid WPA2 credentials for the local Wi-Fi network
7.	Generate a new Particle API access token using:
```shell
$ curl https://api.particle.io/oauth/token \ -u particle:particle \ -d grant_type=password \ -d "username=joe@example.com" \ -d "password=SuperSecret"
```
8.	Create sub the return access token into the GET request within the retrieve_standing.cpp, for example:

> "GET /v1/devices/{DEVICE ID}/standingup?access_token={ACCESS TOKEN}&format=raw HTTP/1.1"

10.	Load the firmware updater WiFi shield code
![firmware updater example](/images/firmware_updater.jpg)
9.	Load the root HTTPS certificate for the Particle API service and Tools > Firmware Updater > "Upload Certificates to WiFi module"
![load certificate](/images/load_cert.jpg)
11.	Configure the Particle Argon device and connect to the local Wi-Fi network
12.	Load the code within the Git Hub repository under Wearable_Argon
13.	Flash the device with new firmware
14.	Connect both devices to a power source and ready to use

## Contributing

### Step 1

- **Option 1**
    - 🍴 Fork this repo!

- **Option 2**
    - 👯 Clone this repo to your local machine using `https://github.com/joanaz/HireDot2.git`

### Step 2

- **HACK AWAY!** 🔨🔨🔨

---
