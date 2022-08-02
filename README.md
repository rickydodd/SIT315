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
Reading documentation is important. Once you leave the domain of what you know, documentation becomes more important;
this rings especially true for lower-level programming where specific registers have very defined purposes (defined and facilitated by their microarchitecture),
where the binary "contents" of a register can have a specific and defined effect (or even effect other functionalities provided by the microprocessor inadvertently).

### [/Module2/Naive_Parallel_Matrix_Multiplication/](/Module2/Naive_Parallel_Matrix_Multiplication/)
I created a naive sequential matrix multiplication program, then a naive parallelised matrix multiplication program using pthreads, and then a parallelised matrix multiplication program using [https://www.openmp.org/](OpenMP).

#### What did I learn from creating these programs?
- How to decompose and parallelise a single instruction, multiple data problem.
- In the pthreads implementation, I learnt that structs can be an effective data structure for passing values to a thread, especially if I declare said struct on the heap and avoid mutating it to get the necessary data to the respective thread.
- In the OpenMP implementation, I learnt that the OpenMP API can parallelise some problems very easily with the use of compiler directives that provide the compiler with sufficient information for it to make more optimal choices (such as denoting to the compiler which variables should be treated as private per thread, and which should be treated as shared across threads).
