# ESP32 Servo Control — Web + Alexa

Control a servo motor using your browser and Alexa voice commands via ESP32.

## Features
- Web browser control via ESP32 hosted page
- Alexa voice control ("Alexa, turn on servo")
- Local WiFi only — no cloud service needed
- Both controls work simultaneously

## Hardware
- ESP32 Dev Module
- Servo motor
- Servo signal wire → GPIO 13

## Libraries Required
Install via Arduino IDE Library Manager:
- `ESP32Servo`
- `Espalexa`
- `WebServer` (built into ESP32 core)
- `WiFi` (built into ESP32 core)

## Setup

1. Open `ALexa.ino` in Arduino IDE
2. Set your WiFi credentials:
   ```cpp
   const char* ssid     = "YOUR_WIFI_NAME";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Select board: **Tools → Board → ESP32 Dev Module**
4. Upload to ESP32

## Usage

### Web Control
Open browser and go to `http://<ESP32-IP>/`  
Click **ON** or **OFF** buttons

### Alexa Control
1. Say **"Alexa, discover devices"** (first time only)
2. Say **"Alexa, turn on servo"** → servo moves to 180°
3. Say **"Alexa, turn off servo"** → servo moves to 0°

## Wiring
```
ESP32 GPIO 13  →  Servo Signal (orange/yellow wire)
ESP32 5V       →  Servo Power  (red wire)
ESP32 GND      →  Servo GND    (brown/black wire)
```
