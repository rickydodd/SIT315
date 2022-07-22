# SIT315
## Description of the Repository
This repository contains the code-related task work that I have completed for SIT315 - Concurrent and Distributed Programming.

## Descriptions of the Repository Contents
### [/Module1/Task1.1P.cpp](/Module1/Task1.1P.cpp)
A simple Arduino program that was designed with, and abides by, the sense-think-act paradigm.

#### What did I learn from creating this program?
It can be helpful to think about an embedded system in terms of "sense," "think," and "act," considering the components
in terms of sensors and actuators with an intermediary phase of "thinking"/computation.

### [/Module1/Task1.2P.cpp](/Module1/Task1.2P.cpp)
An interrupt-driven Arduino program. When motion is detected by the motion sensor (an external interrupt occurs),
the main loop is temporarily halted and an interrupt service routine is executed.

#### What did I learn from creating this program?
If a functionality is critical, it can be helpful to design this functionality as an interrupt of some form.
In the flow of the main loop, a certain input may have a significant amount of latency (or may even be missed entirely)
depending on where the program code is located for handling that input. As an interrupt, when the well-specified and
defined action occurs, then the main loop is temporarily halted and the interrupt is handled by an interrupt service
routine.

### [/Module1/Task1.3C.cpp](/Module1/Task1.3C.cpp)
An interrupt-driven Arduino program that uses external interrupts to handle two sensors and facilitate output to two actuators (LEDs).

#### What did I learn from creating this program?
The ATmega328P microprocessor's architecture allows for two pins to have their own external interrupts, so creating a simple
Arduino program that is interrupt-driven and handles two sensors deemed critical can be done with external interrupts.

### [/Module1/Task1.4D.cpp](/Module1/Task1.4D.cpp)
I modified the interrupt-driven Arduino program to make use of bitwise operations; an interrupt timer that switches the on-board LED
on every 1MHz (1 second), followed by turning off every 1MHz; and a pin change interrupt to allow for additional interrupts beyond those supported by
external interrupts.

#### What did I learn from creating this program?
Reading documentation is vitally important. Once you leave the domain of what you know, documentation becomes more and more vital,
and this rings especially true for lower-level programming where specific registers have very defined purposes (defined and facilitated by their microarchitecture),
and these register's binary "contents" have a meaning defined by their microarchitecture.
