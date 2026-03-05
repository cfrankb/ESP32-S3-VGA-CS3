# About

Transitioning from 1993 x86 Assembly to modern C++ on ESP32-S3 involved re-implementing low-level memory buffers and interrupt-driven logic while maintaining the original game's timing and deterministic behavior.


To overcome SRAM limitations on the ESP32-S3, the game utilizes a Scanline Composition Engine. Instead of double-buffering the entire screen, sprites and tiles are composited into a single-row offload buffer before being committed to the display surface. This allows for complex transparency and layering without the 300KB+ memory overhead of a back-buffer.

This project serves as a bridge between low-level legacy architecture and modern embedded systems. It involved refactoring 16-bit Assembly logic into a structured, object-oriented C++ framework using the ESP-IDF, demonstrating long-term adaptability in software engineering.

Project focus: High-performance 2D graphics and hardware interfacing. (Note: Utilizing community-standard VGA timing libraries to focus on custom drawing routines and hardware adaptor design).

## Original MS-DOS

![Image](techdocs/images/Screenshot_2022-10-19_21-01-20.png "icon")

## ESP32-S3 VGA

![Image](techdocs/images/20241221_100753-crop.jpg "icon")

Gameplay: https://www.youtube.com/watch?v=SPQwWkzFRpU

I am also releasing the source code for the map editor:
https://github.com/cfrankb/cs3-map-edit

Try the online version of the game:
https://cfrankb.itch.io/creepspread-iii

Current status is alpha. 90% of the core mechanic has been implemented.

# Software required

esp-idf v5.3 or later.

# Installation

This project is based in part on: https://github.com/spikepavel/ESP32-S3-VGA

```Shell
git clone https://github.com/cfrankb/ESP32-S3-VGA-CS3.git
cd ESP32-S3-VGA-CS3/
idf.py set-target esp32s3
idf.py menuconfig
idf.py flash
```

# Hardware

## VGA Adaptor

An adaptor is needed to communicate with the VGA Hardware.


![Image](techdocs/images/20250202_211146-crop.jpg "icon")


kicad / gerber: [cfrankb/ESP32-S3-VGA-ADAPTOR](https://github.com/cfrankb/ESP32-S3-VGA-ADAPTOR)


## Gamepad

![Image](techdocs/images/20241222_072413-crop.jpg "icon")



| Aim   | GPIO Pin |
| ----- | -------- |
| UP    | 38       |
| DOWN  | 35       |
| LEFT  | 47       |
| RIGHT | 48       |

```
CGameController gamepad(GPIO_NUM_38, GPIO_NUM_35, GPIO_NUM_47, GPIO_NUM_48);
engine->attach(&gamepad);
```

The above configuration is for the ESP32S3. Pin out will vary per model.

