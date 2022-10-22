# ROV-Remote-under-water-operating-Vehicle-Control-System

## It Consists of Four ECUs (Atmega32A) to control the ROV Connect by (UART, SPI, I2C):
- Master Unit for Authentication and choosing the kind of controlling (Terminal or Physical Controller) 
  it’s connected to LCD, Keypad and Selector via UART Rx to choose between terminal and Controller
   and it Connect also to Motor Controller Via SPI.
- Controller Unit: A Physical Controller to control the speed and direction of vehicle, 
  it’s connected to for push bottoms and four potentiometers to control speed and direction of ROV 
  and it’s connected also to Master via UART.
- Sensor Unit for Managing and display sensor status, 
  it’s connected to ultrasonic sensor, Humidity and Temperature Sensor 
  and RTC (Via I2C) and connected also to Terminal via UART. 
- Motors Unit for Controlling the Four Motor Around the vehicle
  it’s connected to master via SPI and 4 Motor Driver.
