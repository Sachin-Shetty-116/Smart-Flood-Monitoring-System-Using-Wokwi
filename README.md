# Smart Flood Detection System Using IoT and Fog Computing

## Overview
An educational prototype that monitors a simulated water level and identifies possible flood conditions using ESP32, MQTT, a Python fog node and a live web dashboard.

## Architecture
Water-level input (potentiometer) -> ESP32 -> MQTT broker -> Python fog node -> Web dashboard.

The ESP32 also controls the LEDs and buzzer. The Python program performs fog processing; the MQTT broker only transfers messages.

## Technologies
- ESP32 and Arduino C++
- Python and Paho-MQTT
- MQTT (HiveMQ public broker)
- HTML, CSS and JavaScript
- Wokwi simulator

## Components and Connections
| Component | ESP32 pin |
|---|---:|
| Potentiometer SIG | GPIO 34 |
| Green LED | GPIO 18 |
| Yellow LED | GPIO 19 |
| Red LED | GPIO 21 |
| Buzzer | GPIO 23 |
| Component grounds | GND |

Use a 220-ohm resistor with each LED.

## Water-Level Classification
| Level | Status | LED | Buzzer |
|---|---|---|---|
| Below 40% | NORMAL | Green | OFF |
| 40-69% | HIGH | Yellow | OFF |
| 70% and above | FLOOD ALERT | Red | ON |

## Run the Project
1. Open the ESP32 project in Wokwi and start the simulation.
2. Open a terminal in the `Fog-Node` folder.
3. Install dependencies: `py -m pip install -r requirements.txt`
4. Start the fog node: `py fog_node.py`
5. Open `Website/index.html` in a browser.
6. Change the potentiometer in Wokwi and observe the dashboard.

## MQTT Topics
- Sensor input: `sachin-flood-demo-01/sensor`
- Processed output: `sachin-flood-demo-01/processed`

If you change the topic, update it consistently in all three code files.

## Limitations and Safety
- The potentiometer simulates a water-level sensor; it is not a real sensor.
- The computer running the Python fog node must remain on.
- The demo depends on network connectivity.
- The public MQTT broker is not private or secure. Do not send sensitive information through it. Use a secured broker and authentication for real deployment.

## Future Enhancements
- Connect a real water-level sensor.
- Add SMS or mobile notifications.
- Store historical readings.
- Support multiple monitoring locations.
- Use authenticated, encrypted MQTT communication.

This is an educational prototype, not a certified flood-warning system.
