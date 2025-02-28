# ESP32 BLE-MQTT Project

This project demonstrates an ESP32-based system that scans for BLE devices, detects movement based on accelerometer data, and publishes the status ("moving" or "stationary") to an MQTT topic.

## Project Structure
- `esp32_ble_mqtt.ino`: Arduino sketch for the ESP32 to scan BLE devices and publish to MQTT.

## Prerequisites
- **Hardware**: ESP32 board (e.g., ESP32 DevKit).
- **Software**:
  - [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support.
  - Install Wifi, PubSubClient from library manager.
  - Git installed on your system.
