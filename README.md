Roboteq CANOpen Motor Control Project
Author: Your Name
Date: March 2025
Hardware Used:

Roboteq SBL2360T Motor Controller
STM32F103C8T6 (Blue Pill)
SN65HVD230 CAN Bus Transceiver
Two Motors:
LIFT (Channel 2)
TURN (Channel 1)
Power Supply (24V-48V for Motor Controller)
1️⃣ Wiring Diagram
CAN Bus Wiring
STM32F103 (Blue Pill)	SN65HVD230 (CAN Transceiver)	Roboteq SBL2360T
PA11 (CAN_RX)	R (CAN RX)	CAN_H
PA12 (CAN_TX)	D (CAN TX)	CAN_L
GND	GND	GND
3.3V	VCC	-
Power and Motor Wiring
Battery (24V-48V) → Roboteq Main Power Input
Motor 1 (TURN) → Channel 1 on Roboteq
Motor 2 (LIFT) → Channel 2 on Roboteq
Encoder Feedback (if required) → Roboteq Encoder Input
2️⃣ STM32 Configuration (CubeMX Settings)
Peripheral	Configuration
CAN1	Baud Rate: 500Kbps, Normal Mode
GPIO	PA11 (CAN_RX), PA12 (CAN_TX)
Clock	HSE ON (External Crystal 8MHz)
NVIC	Enable CAN RX0 Interrupt
3️⃣ CANOpen Communication Overview
Standard CANOpen Message Format
ID	Data (Bytes)	Description
0x600 + Node ID	[Command, Index LSB, Index MSB, Subindex, Data]	SDO Write
0x580 + Node ID	[Response Data]	SDO Response
CANOpen Object Dictionary
Function	Index (Hex)	Subindex	Type
Set Motor Position	0x2001	0x01	S32
Set Motor Speed	0x2002	0x01	S32
Set Motor Command (Open Loop)	0x2000	0x01	S32
Read Encoder Count	0x2104	0x01	S32
Read Voltage	0x210D	0x02	U16
Apply Emergency Stop	0x200C	0x00	U8
Release Emergency Stop	0x200D	0x00	U8
4️⃣ Available Functions in roboteq.h
Motor Control Functions
Function	Description
roboteq_setMotorCommand(MOTOR_LIFT, speed)	Open-loop speed (-1000 to 1000)
roboteq_setMotorSpeed(MOTOR_LIFT, speed_rpm)	Closed-loop speed (RPM)
roboteq_setMotorPosition(MOTOR_LIFT, position)	Absolute position (Encoder counts)
roboteq_setMotorAngle(MOTOR_LIFT, angle)	Move motor to specific angle
Queries
Function	Description
roboteq_queryVoltage()	Reads system voltage
roboteq_queryEncoderPosition(MOTOR_LIFT)	Reads encoder position
Emergency Stop Functions
Function	Description
roboteq_applyEStop(MOTOR_LIFT)	Stops the motor immediately
roboteq_releaseEStop()	Releases emergency stop
5️⃣ How to Test the Library
Flash STM32 with the provided main.c and roboteq.c.
Comment/Uncomment functions in main.c to test one feature at a time.
Ensure Roboteq is in the correct mode before testing:
Open Loop Mode: roboteq_setMotorCommand()
Closed Loop Speed Mode: roboteq_setMotorSpeed()
Closed Loop Position Mode: roboteq_setMotorPosition()
Use a CAN Analyzer to monitor messages.
Check Serial Debug Output for errors or confirmations.
6️⃣ Common Issues & Solutions
Issue	Possible Cause	Solution
No CAN communication	CAN wiring issue	Check TX/RX connections, ensure 120Ω termination resistor is present
Motor doesn’t respond to commands	Incorrect mode configured	Set controller to Open/Closed loop mode based on function
Encoder values not updating	Wrong object dictionary index	Ensure 0x2104 is correct for encoder queries
E-Stop doesn’t work	Incorrect subindex	Use 0x200C for apply, 0x200D for release
Voltage query returns 0	Wrong subindex	Try 0x210D, 0x02
7️⃣ Future Improvements
✅ Implement watchdog for error handling
✅ Expand support for additional CANOpen PDOs
✅ Integrate encoder-based PID control

8️⃣ Final Notes
Double-check wiring and termination resistors for CAN communication stability.
Set correct control modes before testing motor functions.
Use a CAN Bus Analyzer to debug communication issues.
Test each function separately to isolate issues.