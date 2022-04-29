# ECE4180-The-Game-Box
ECE 4180 Final Project

# Authors 
Team Members: Khoa Nguyen, Valentina Fortuny, AJ Dhillon, Fernando

# Table of Contents

# Overview

For the Final Project of ECE 4180, our team designed a mini game console that picks a game at random for a total for 4 games. The system prompts the player to match the output displayed on either the LCD screen or the RGB LED.

Binary Game: Given a decimal value, use the four push buttons to the output in binary.

RGB Game: Use the potentiometers to match the displayed colour.

Distance Game: Use the ultrasonic sensor to match the given distance.

Pattern Game: Use the push buttons to match the displayed patterns on the LCD screen.




# Photos



# Parts List

mbed LPC1768

LCD-144 board from 4D Systems

5 pushbuttons

3 potentiometers

HC-SR04 Sonar

2 RGB LEDs

5V Power Supply 

3 pin power barrel


# Diagram

![alt text](https://github.com/adhillon30/ECE4180-The-Game-Box/blob/main/4180.png?raw=true)

# Pins

ULCD


| MBED        | ULCD |
|-------------|------|
| external 5V | 5V   |
| p14         | RX   |
| p13         | TX   |
| GND         | GND  |
| p12         | RES  |


SONAR


| MBED        | SONAR |
|-------------|-------|
| external 5V | VCC   |
| p29         | Trig  |
| p30         | Echo  |
| GND         | GND   |



USER LEDs


| MBED | USER LED |
|------|----------|
| p26  | red      |
| p25  | green    |
| p24  | blue     |
| GND  | GND      |

Prompt LEDs



| MBED | PROMPT LED |
|------|------------|
| p23  | red        |
| p22  | green      |
| p21  | blue       |
| GND  | GND        |

Pushbuttons


| MBED | Pushbutton Mapping |
|------|--------------------|
| p6   | pb1                |
| p7   | pb2                |
| p8   | pb3                |
| p9   | pb4                |
| p5   | pb SUBMIT          |

Potentiometer



| MBED | POT |
|------|-----|
| p18  | R   |
| p19  | G   |
| p20  | B   |

# Demo


[![Watch the video](https://img.youtube.com/vi/M6GnD1-36NE/default.jpg)](https://youtu.be/M6GnD1-36NE)
