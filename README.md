# Beeper-Library

The purpose of this library is to control a piezo crystal and make sound
with it. The piezo may either have electronic or be connected directly
to the microcontroller - in last case this library makes the "sound".
The piezo can be connected either to one GPIO or two: The later the GPIO
pins are set to different levels in order to have most volume out of the
piezo crystal.

## Beeper

This class holds all stuff needed.

### Constructor
Beeper(iGPIO, iGPIONeg, boNeg, boAuto)
- iGPIO = first GPIO pin on that the piezo crystal is connected or -1 if unused
- iGPIONeg = second GPIO pin or -1 if unused
- boNeg = controls output logic (default false)
  - if false an inactive output is set LOW
  - if true an inactive output is set HIGH
- boAuto = automatic mode (default false)
  - false = piezo is controlled by library
  - true = piezo has its own electronic

### Methods
- Init(iGPIO, iGPIONeg, boNeg, boAuto)
  - same as constructor, can be used instead of constructor
- Beep(microseconds)
  - beep for microseconds duration (default 100000 microseconds = 100 milliseconds)
- Interval(microseconds)
  - beep half the time, then silence the other half of time (default 100 ms)
- SetFrequency(freq)
  - set frequency for Beep() and Interval() for non-automatic piezo (default 5000 Hz)

## Releases

- 1.0.0 Initial release.
- 1.0.1 Naming convention

## How to install

[Installing Additional Arduino Libraries](https://www.arduino.cc/en/Guide/Libraries)
