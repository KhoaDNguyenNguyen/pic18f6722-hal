# PIC18F6722 Hardware Abstraction Layer

A modular, C99-compliant Hardware Abstraction Layer (HAL) and Board Support Package (BSP) for the PIC18F6722 microcontroller training kit. Refactored from the legacy codebase by Nguyen Dinh Phu.

## Features

- Dual-target build system (Real Board & Proteus Simulation)
- Modular architecture with layered design
- Easy API: Non-blocking, state-machine driven wrappers for multitasking
  - Edge-triggered global debounce for inputs
  - Non-blocking scrolling and blinking animations
  - Custom LCD character generation (CGRAM)
- Hardware SPI accelerated MBI5026 Shift Register Driver
- Displays: LCD 20x4, GLCD 128x64, 8x8 LED Matrix, 8-Digit 7-Segment, 32 Discrete LEDs
- Inputs: 4x4 Keypad, Buttons, Rotary Encoder
- Actuators: Relays, Triacs, Buzzer
- Core: Timer, Counter
- Exam Templates: Ready-to-use boilerplates for state machines and graphics

## Author

Dang-Khoa N. Nguyen
