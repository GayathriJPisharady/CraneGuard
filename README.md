# CraneGuard

An IoT-based Smart Crane Anti-Collision and Safety Monitoring System developed using ESP32.

## Overview

CraneGuard improves construction site safety by continuously monitoring nearby obstacles using ultrasonic sensors. When an object enters the danger zone, the system alerts the operator through LEDs, a buzzer, and automatically restricts crane movement using a servo mechanism.

## Features

- Real-time obstacle detection
- Three-level safety warning
- OLED distance display
- Visual LED indicators
- Audible buzzer alerts
- Automatic movement restriction
- ESP32 based
- Wokwi simulation support

## Hardware

- ESP32 Dev Module
- HC-SR04 Ultrasonic Sensor
- SSD1306 OLED Display
- SG90 Servo Motor
- LEDs
- Buzzer
- Jumper Wires

## Working Principle

1. Ultrasonic sensor measures obstacle distance.
2. ESP32 processes the readings.
3. OLED continuously displays distance.
4. LEDs indicate safe, caution and danger zones.
5. Buzzer activates during danger.
6. Servo restricts crane movement if obstacle is too close.

## Safety Zones

| Distance | Status |
|-----------|--------|
| >100 cm | Safe |
| 50–100 cm | Warning |
| <50 cm | Danger |

## Technologies Used

- ESP32
- Arduino Framework
- PlatformIO
- Wokwi
- C++

## Future Improvements

- Multiple ultrasonic sensors
- AI-based object detection
- Load monitoring
- Mobile app
- Blynk IoT Dashboard
- LoRa communication
- Cloud logging

## Status 
Developed and validated using the Wokwi simulator. No physical prototype has been built yet.

## Repository Structure

```
firmware/
hardware/
docs/
simulation/
assets/
```

## Author

**Gayathri J Pisharady**

Mechanical Engineering  
Government Engineering College Palakkad

## License

MIT License
