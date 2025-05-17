# Ecumaster EMU Classic HD44780 display #

Simple "dash" for EMU Classic based on Arduino and HD44780 screen.
Connects to EMU serial output on the expansion port.

## Elements ##

- Arduino Nano

  ![arduino nano](./docs/elements/arduino_nano.png)
- HD44780 with I2C interface

  ![hd44780 i2c](./docs/elements/hd44780_i2c.png)

- MAX3232 RS232<>TTL converter

  ![max3232 top side](./docs/elements/max3232_top.png)
  ![max3232 top side](./docs/elements/max3232_bottom.png)

- GX16 5-pin connector

  ![gx16 5-pin](./docs/elements/gx16_5pin.png)

## Arduino IDE setup ##

- Install LiquidCrystal_I2C library
- Install EMUSerial library (Note: On Linux You need to modify `~/Arduino/libraries/EMUSerial/src/EMUSerial.h` file and
  replace `#include "arduino.h"` with `#include "Arduino.h"`)

## Hardware connections ##

### Arduino <> Display ###

| Arduino | Display |
|---------|---------|
| 5V      | VCC     |
| GND     | GND     |
| A4      | SDA     |
| A5      | SCL     |

### Arduino <> MAX3232 ###

| Arduino | MAX3232 (TTL side) |
|---------|--------------------|
| TX      | IN                 |
| RX      | OUT                |

### EMU <> MAX3232 ###

| EMU           | MAX3232 (RS232 side) |
|---------------|----------------------|
| RXD (pin 1)   | OUT                  |
| TXD (pin 2)   | IN                   |
| +3.3V (pin 3) | unused               |
| GND (pin 4)   | GND                  |
| +5V (pin 5)   | VCC                  |

### Wiring diagram ###

![wiring diagram](./docs/wiring_diagram.png)

## Flashing assembled board ##

You won't be able to flash a fully assembled board due to the way in which TX and RX pins are wired on Arduino.

Before flashing board You need to disconnect TX and RX pins from the board.

## Case ##

### Required hardware ###

- 4 M4x50 bolts
- 4 M4 nuts
