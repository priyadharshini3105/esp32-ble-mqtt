# ESP32 BLE-MQTT Project

This project demonstrates an ESP32-based system that scans for BLE devices, detects movement based on accelerometer data, and publishes the status ("moving" or "stationary") to an MQTT topic. It includes a Dockerized MQTT broker and a Python listener to receive and display the messages.

## Project Structure
- `esp32_ble_mqtt.ino`: Arduino sketch for the ESP32 to scan BLE devices and publish to MQTT.
- `listener.py`: Python script to subscribe to the MQTT topic and print messages.
- `Dockerfile.mqtt`: Dockerfile for the MQTT broker (Mosquitto).
- `Dockerfile.listener`: Dockerfile for the Python listener.
- `mosquitto.conf`: Configuration file for the MQTT broker.
- `docker-compose.yml`: Docker Compose file to orchestrate the MQTT broker and listener.

## Prerequisites
- **Hardware**: ESP32 board (e.g., ESP32 DevKit).
- **Software**:
  - [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support.
  - Install Wifi, PubSubClient from library manager.
  - [Docker](https://www.docker.com/) and [Docker Compose](https://docs.docker.com/compose/).
  - Git installed on your system.