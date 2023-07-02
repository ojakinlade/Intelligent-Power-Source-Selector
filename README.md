# Intelligent-Power-Source-Selector

This repository contains the source code and documentation for an intelligent power source selector project in a microgrid. The system is designed to receive power consumption information from individual units within the microgrid via radio frequency (RF) communication. It aggregates the power consumption data from all the nodes and utilizes an algorithm to select the optimal power source or combination of sources that can meet the demand with minimal cost.

## Features

- Automatic selection of the most cost-effective power source(s)
- RF communication for data collection from microgrid units
- Aggregation of power consumption data from all nodes
- IPSS algorithm for optimal power source selection
- Real-time monitoring of energy consumption and cost
- Web application to change the time of the day for testing purposes

## Hardware Requirements

- IPSS
  - ESP32 Development Board
  - LEDS (To show the sources selected)
  - 20x4 LCD
  - RF Modules (HC-12 Transceiver)
  - DS1302 RTC module
- Units
  - Arduino Nano
  - PZEM004Tv30 metering module
  - RF Modules (HC-12 Transceiver)
