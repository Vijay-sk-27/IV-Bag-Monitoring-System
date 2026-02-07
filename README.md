# IV Bag Monitoring System with Auto Shutoff

## Overview
This project implements a smart IV fluid monitoring system used in hospitals to
monitor IV saline level and automatically stop the flow when the fluid is about
to empty, preventing air embolism.

## Components Used
- Load cell / Ultrasonic sensor
- Arduino / ESP32
- Solenoid valve
- Relay module
- LCD / Buzzer
- Power supply

## Working Principle
The system continuously monitors the IV fluid level. When the fluid drops below
a predefined threshold, the controller activates a solenoid valve to shut off
the IV flow and triggers an alert.

## Features
- Real-time IV level monitoring
- Automatic flow shutoff
- Audible/visual alert
- Low-cost and reliable

## Applications
- Hospitals
- Clinics
- ICU patient monitoring
