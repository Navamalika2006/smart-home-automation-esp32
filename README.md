# 🏠 Smart Home Automation System (ESP32 + Wokwi Simulator)

A WiFi-enabled home automation system built on the ESP32, simulated end-to-end using **Wokwi** and **PlatformIO**. It controls two household appliances (represented as LEDs — a tubelight and a fan) and monitors live temperature & humidity via a DHT22 sensor, all through a responsive web dashboard.

![Status](https://img.shields.io/badge/status-working-brightgreen) ![Platform](https://img.shields.io/badge/platform-ESP32-blue) ![Framework](https://img.shields.io/badge/framework-Arduino-orange)

---

## 📋 Overview

This project demonstrates core embedded systems and IoT skills relevant to firmware and embedded roles — WiFi/HTTP protocol handling, sensor interfacing, and real-time hardware control via a web interface, all built and validated without physical hardware using circuit simulation.

---

## 🔧 Components Used

| Component | Purpose |
|---|---|
| ESP32 DevKit V1 | Main microcontroller (WiFi + processing) |
| DHT22 Sensor | Temperature & humidity monitoring |
| 2× LEDs | Simulate tubelight and fan appliances |
| 2× 220Ω Resistors | Current limiting for LEDs |

**Tools:** Wokwi Simulator, PlatformIO, VS Code, Arduino Framework (C++)

---

## ⚙️ How It Works

1. ESP32 boots and connects to WiFi.
2. An HTTP web server starts on the ESP32 using `WebServer.h`.
3. The DHT22 sensor is polled for live temperature and humidity readings.
4. A styled web dashboard (served directly from the ESP32) displays sensor data and provides ON/OFF controls for both appliances.
5. A `/status` JSON endpoint exposes live state — ready to be consumed by a future mobile app.

---

## 🔌 Circuit Connections

| Component | ESP32 Pin |
|---|---|
| DHT22 → SDA | GPIO 15 |
| DHT22 → VCC | 3V3 |
| DHT22 → GND | GND |
| LED1 (Tubelight) | GPIO 2 |
| LED2 (Fan) | GPIO 4 |

---

## 🖥️ Dashboard Preview

The web dashboard shows:
- Live temperature (°C) and humidity (%)
- ON / OFF controls for Tubelight and Fan
- Real-time status indicators

---

## 🧠 Skills Demonstrated

- Embedded C / Arduino framework programming on ESP32
- WiFi connectivity and HTTP server implementation
- Sensor interfacing (DHT22, digital protocols)
- Circuit design and simulation (Wokwi)
- Debugging a full embedded toolchain (PlatformIO, VS Code)

---

## 🚀 How to Run

1. Install **VS Code**, the **PlatformIO IDE** extension, and the **Wokwi Simulator** extension.
2. Clone this repository.
3. Open the folder in VS Code — PlatformIO will detect the project automatically.
4. Build the project:
   ```bash
   pio run
   ```
5. Open `diagram.json` and click the green ▶ **Play** button to start the simulation.
6. Once connected, open `http://localhost:8100` in your browser to view the live dashboard.

---

## 🔭 Future Improvements

- [ ] Add MQTT protocol support (industry-standard IoT messaging)
- [ ] Build a dedicated mobile app using the existing `/status` JSON API
- [ ] Add more sensors (motion, gas/smoke detection)
- [ ] Persist LED states across reboots using EEPROM/NVS

---

## 👤 Author

**Navamalika B.**
Final Year B.E. ECE, University College of Engineering (BIT Campus), Anna University
