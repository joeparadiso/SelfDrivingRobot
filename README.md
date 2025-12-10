# Autonomous Robo-Sockey Unit (JARVIS Mk II)

**Project Status:** Completed (Academic Archive)

## 📖 Project Overview

This repository contains the embedded firmware for a custom-built autonomous robot designed for the "Robo-Sockey" engineering competition at Grand Valley State University (Introduction to Engineering II).

The objective of the competition was to design and build a robot capable of navigating a 6x6 foot arena independently to locate balls and deposit them into a goal within a 3-minute time limit. The robot utilizes a variety of sensors for environment mapping, obstacle avoidance, and game objective tracking without human intervention.

## ⚙️ Key Features

* **Finite State Machine (FSM) Architecture:** The robot operates on a responsive state machine, allowing it to transition seamlessly between random exploration, obstacle avoidance, line following, and scoring modes.
* **Sensor Fusion:** Integrates Ultrasonic sensors, Infrared (IR) distance sensors, Time-of-Flight (ToF) sensors, physical limit switches, and break-beam sensors.
* **Visual Debugging System:** Utilizes a NeoPixel LED ring to display real-time internal state changes, allowing for immediate visual diagnostics during autonomous operation.
* **Differential Drive System:** Powered by continuous rotation servos for precise movement and zero-radius turning.
* **Active Intake Mechanism:** A servo-controlled gate mechanism captures game balls and ejects them upon reaching the goal.

## 🛠 Hardware Architecture

### Bill of Materials
* **Microcontroller:** Arduino (Master)
* **Actuators:**
    * 2x Continuous Rotation Servos (Drive Train)
    * 1x Standard Servo (Gate/Intake Mechanism)
* **Sensors:**
    * 3x Ultrasonic Range Finders (HC-SR04 type)
    * 2x Analog IR Distance Sensors (Sharp GP2Y0A21YK0F)
    * 1x Adafruit VL53L0X Time-of-Flight Distance Sensor
    * 1x I2C Line Follower Array (Slave Device)
    * 2x Mechanical Limit Switches (Bumpers)
    * 1x IR Break-beam sensor (Ball detection)
* **Indicators:** Adafruit NeoPixel 12-LED Ring

### Pin Configuration
| Component | Pin / Port | Type |
| :--- | :--- | :--- |
| **Left Drive Motor** | `D11` | PWM Output |
| **Right Drive Motor** | `D10` | PWM Output |
| **Gate Mechanism** | `D9` | PWM Output |
| **NeoPixel Ring** | `A0` | Data Output |
| **Left Bumper** | `D4` | Digital Input (Pullup) |
| **Right Bumper** | `D3` | Digital Input (Pullup) |
| **Right Ultrasonic** | Trig: `D6`, Echo: `D5` | Digital I/O |
| **Left Ultrasonic** | Trig: `D8`, Echo: `D7` | Digital I/O |
| **Center Ultrasonic** | Trig: `D13`, Echo: `D2` | Digital I/O |
| **Right IR Sensor** | `A3` | Analog Input |
| **Left IR Sensor** | `A2` | Analog Input |
| **Breakbeam Sensor** | `D12` | Digital Input |
| **Line Follower** | `I2C Bus` | SDA/SCL (Address 9) |
| **VL53L0X Center IR** | `I2C Bus` | SDA/SCL |

## 💻 Software Architecture

The core logic (`JARVIS_MARK_II_V8.4.ino`) is built around a `switch/case` state machine. The robot continuously polls its sensor array via the `updateSensors()` function and determines the next logic state.

### State Definitions & Visual Indicators
The robot uses the NeoPixel ring defined in `colors.h` to broadcast its current logic state:

| State | LED Color | Description |
| :--- | :--- | :--- |
| `start` | **Red** | Initial boot sequence. |
| `randomMovement` | **Purple/White** | Default exploration mode. Moves forward while scanning for lines or balls. |
| `bumperAvoid` | **Blue** | Physical collision detected. Executes reverse and turn maneuvers. |
| `IRavoidR` | **Red** | Right IR sensor triggered. Turns left to avoid close obstacle. |
| `IRavoidL` | **Yellow** | Left IR sensor triggered. Turns right to avoid close obstacle. |
| `IRavoidC` | **Green** | Center VL53L0X detected obstacle. Reverses and executes random turn. |
| `ultrasonicAvoid` | **Red/Blue** | Side ultrasonic sensors detect approaching walls. Adjusts trajectory. |
| `followingLine` | **Orange/Blue** | Line follower array has detected the goal line. Uses PID-like logic to track the line. |
| `score` | **Orange** | Goal condition met. Activates gate servo to release the ball and backs away. |

### Dependencies
This project relies on the following Arduino libraries:
* `Wire.h` (Standard I2C)
* `Servo.h` (Standard Servo control)
* `NewPing.h` (Efficient Ultrasonic driving)
* `Adafruit_NeoPixel.h` (LED control)
* `Adafruit_VL53L0X.h` (ToF Sensor driver)

## 📸 Gallery

### Prototype Views
Below are images of the final robot configuration used in competition.
|                         **Image One**                                        |                       **Image Two**                          |                       **Image Three**                          |
| :--------------------------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="https://user-images.githubusercontent.com/82463730/190691295-3c22a76d-eea7-4296-9dc7-c42cc5345149.JPG" alt="Robot Img" width=400/> |  <img src="https://user-images.githubusercontent.com/82463730/190691714-586f9eb8-0394-4ae1-856e-748255ca5787.JPG" alt="Robot Img" width=400/>   |  <img src="https://user-images.githubusercontent.com/82463730/190691745-a0e02656-d05f-4675-a05b-f78f5a010c53.JPG" alt="Robot Img" width=400/>   |
|     _Front view of the Self Driving Robot._      | _Side view of the Self Driving Robot._ | _Rear view of the Self Driving Robot._ |
