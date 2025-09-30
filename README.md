
![App Screenshot](https://github.com/AkashRouth001/IoT-Based-Aqua-waste-collector/blob/61c3146e0c7ff66e8d0b1f3a50291a4a5e686482/image/main%20image.png)


# Aquawaste Collector — IoT Water Pollution Monitoring & Tracking System 🌊🤖

Aquawaste Collector is a hybrid IoT system that both collects floating solid waste from water surfaces and monitors water quality in real time. The project combines a joystick-controlled robotic boat (NRF24L01 remote control) with a sensor suite (pH, turbidity, DS18B20 water temperature, DHT11 air temp & humidity, ultrasonic water-level detection). Sensor data is uploaded to ThingSpeak via ESP8266/ESP32 and critical alerts can be sent via GSM SMS.

This repository provides firmware, wiring diagrams, configuration examples, and instructions to reproduce and extend the system.
-- 
## ✨ Features
- 🚤 Joystick-controlled robotic boat
- ♻️ Waste collection system
- 📡 Real-time data upload to ThingSpeak
- 🌡️ Multi-sensor monitoring (pH, turbidity, DS18B20, DHT11, ultrasonic)
- 📱 GSM-based SMS alerts (optional)
- 🔧 Modular firmware (transmitter, receiver, uploader)


---


## 🛠️ Hardware Components
- Arduino Uno/Nano (boat controller)
- ESP8266 / ESP32 (Wi-Fi data uploader)
- NRF24L01 transceivers (remote control)
- L298N motor driver + DC motors
- Sensors: pH, Turbidity, DS18B20, DHT11, HC-SR04
- GSM Module (SIM800L/900)
- Separate power supply for logic & motors


---
## 🏗️ System Architecture  
![App Screenshot](https://github.com/AkashRouth001/IoT-Based-Aqua-waste-collector/blob/61c3146e0c7ff66e8d0b1f3a50291a4a5e686482/image/all_connections.jpeg)



The system integrates three major subsystems working in coordination:  

1. **Waste Collection Unit**  
   - A robotic boat equipped with dual DC motors for navigation.  
   - Controlled manually via a wireless joystick remote using **NRF24L01** modules.  
   - Motor driver (L298N) regulates speed and direction of the motors.  

2. **Environmental Monitoring Unit**  
   - Sensors: Turbidity, pH, DS18B20 Temperature, Ultrasonic, and DHT11.  
   - Data acquisition handled by **Arduino + ESP8266**.  
   - Real-time monitoring with LED alerts for critical conditions.  

3. **IoT Communication & Cloud Unit**  
   - Sensor data transmitted to **ThingSpeak** cloud via ESP8266 for visualization.  
   - SMS alerts enabled through GSM module for threshold violations.  
   - Scalable for future integration with autonomous navigation or AI-based decision-making.  
![App Screenshot](https://github.com/AkashRouth001/IoT-Based-Aqua-waste-collector/blob/61c3146e0c7ff66e8d0b1f3a50291a4a5e686482/image/remort%20control.jpeg)

This modular architecture ensures efficient waste collection while simultaneously monitoring water quality in real time.
--

## 🔄 System Flow  
![App Screenshot](https://github.com/AkashRouth001/IoT-Based-Aqua-waste-collector/blob/61c3146e0c7ff66e8d0b1f3a50291a4a5e686482/image/flowchart.jpeg)

The system follows a simple flow:  
1. **Initialization** – Sensors, communication modules, and motor drivers are set up.  
2. **Data Collection** – Turbidity, pH, temperature, humidity, and water level are continuously measured.  
3. **Processing** – Values are filtered, converted, and compared against safe thresholds.  
4. **Action** – Waste is collected via the robotic boat, and alerts are triggered when critical conditions are detected.  
5. **Transmission** – Sensor data is sent to ThingSpeak via Wi-Fi and SMS alerts are delivered through the GSM module.  
6. **Visualization** – Users can monitor real-time water quality parameters on the cloud dashboard.  

## Authors

- [@Akash Routh](https://github.com/AkashRouth001)

