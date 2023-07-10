# Door Locker Security System
 Door Locker Security System Using AVR Microcontroller that uses a password to unlock a door. It communicates with another microcontroller using UART communication. It has functions to read and initialize the password, display system options, and simulate the opening of the door. It uses a keypad to take input from the user and displays messages on an LCD. If the user enters the correct password, the door opens, otherwise, the system displays a message indicating the wrong password. If the user wants to change the password, the system prompts them to enter the current password and if it's correct, it allows them to initialize a new password. The application uses timer interrupts to track the time elapsed since the system was started. The application implements several functions, such as initializing the system, reading and initializing the password, displaying main options on the LCD, and simulating the opening of the door. The application's code is designed to run on an AVR microcontroller, making it highly efficient and cost-effective. Overall, this application can be useful for small-scale security systems in homes, offices, or other facilities, providing a reliable and straightforward solution to ensure access control.

**Features**
-Password-based security system
-User input via keypad
-LCD display for system messages and prompts
-Communication with Control ECU via UART
-Timer to track elapsed time
-Door unlocking simulation

**Drivers used:**
-GPIO (General Purpose Input/Output) Driver: Used to control the microcontroller's pins for various purposes, such as reading keypad input, driving DC motor and buzzer output, and controlling LCD display.
- Buzzer Used to generate sound output to indicate various events, such as a wrong password or the unlocking of the door.
-Keypad Used to read input from the keypad and determine which button was pressed. It includes functions for initializing the keypad and reading its output.
Display:
-LCD (Liquid Crystal Display) Driver: Used to interface with and display information on the LCD display. It includes functions for initializing the display, sending data and commands to the display, and clearing the display.
-Communication Protocol: UART (Universal Asynchronous Receiver/Transmitter) Driver: Used for serial communication between two microcontrollers. In your application, it is used to send and receive passwords to and from the Control ECU.
-I2C (Inter-Integrated Circuit) Driver: Used to communicate with devices using the I2C protocol, such as the Control ECU.
- Memory: EEPROM Used to store and retrieve data in non-volatile memory, such as the password. It includes functions for reading and writing to EEPROM memory.
- Actuators: DC motor Used to drive the DC motor to simulate the unlocking of the door. It includes functions for controlling the direction and speed of the motor.
-Timing:Timer Used to generate periodic interrupts to execute tasks at specific intervals, such as incrementing a global variable to keep track of time since the system was started.


**Demo**
![](https://github.com/husseinAhmed10/Door-Locker-Security-System/blob/main/Final%20Project.gif)
