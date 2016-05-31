# Sputnik Capstone Test Plan

written by Shan Quinney, William Harrington, and James Heath

**Table of Contents**
* [Revision History](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#revision-history)
    * [Introduction](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#introduction)
    * [Purpose](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#purpose)
    * [Testing Procedure](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#testing-procedure)
    * [Recording of Results, witnessing, and authorities](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#recording-of-results-witnessing-and-authorities)
* [Reference Documents](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#reference-documents)
    * [Design Documentation](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#design-documentation)
* [Overview](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#overview)
    * [Operational Description](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#operational-description)
* [Preparation](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#pre-test-preparation)
    * [Test Equipment](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#test-equipment)
    * [Test setup and calibration](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#test-setup-and-calibration)
* [Component Tests](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#component-tests)
     * [Supply Range Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#supply-range-test)
     * [Temperature Range Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#temperature-range-test)
     * [Vacuum Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#vacuum-test)
* [System Tests](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#system-tests)
    * [Radio Communication Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#radio-communication-test)
    * [Control Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#control-test)
    * [Command Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#command-test)
    * [Functionality Test](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#functionality-test)

### Revision History

03/03/16 - Created document (Shan)

03/04/16 - Converted to markdown, proofreading changes (Will)

04/17/16 - Changed Communications Test, added functionalty test and grid, added Command test, changed incorrect links in ToC (Jake)

04/17/16 - Added component test section and all component tests and grids: Crystal, supply range, temperature, force, and vacuum. (Jake) 

04/20/16 - Fixed ToC link error (Jake)

04/21/16 - Moved to oresat repo and fixed ToC links (Jake)

04/29/16 - Changes based on Test Plan Review (Jake)

04/29/16 - Changes based on proofreading the test plan (Will)

04/30/16 - More proofreading changes. Changed crystal test to make it explicit that it will be performed on BOTH microcontrollers. Changed Supply Range Test to encompass BOTH modules. Changed Temperature Range Test to encompass BOTH modules and changed steps, actions, and expected results. Revised Acceleration test.

05/14/16 - Grammar corrections in introduction.

05/16/16 - Removed "Test Setup and Calibration" section from the document. Revised Temperature Test with updated procedure. (Shan)

### Introduction

#### Purpose

The purpose of this document is to outline testing that will be essential for determining the effectiveness of the Sputnik Capstone project. This test plan is not intended to be all inclusive and additional testing procedures will be added if deemed necessary by any of the parties involved in the project.

#### Testing Procedure

All of the testing procedures described in this document will be carried out by one or more of the Sputnik capstone team members. An effort will be made to have the entire team present for as many of the tests as possible.

#### Recordings of Results, Witnessing, and Authorities

The results of all testing will be posted in [this git respository](https://github.com/oresat/low-gain-radio) in the docs folder. The tests will be conducted on a pass/fail basis and any tests that do not pass will be noted along with an explanation/conjecture as to why they did not pass. No authorities or witnesses outside of the group will be required to be present during testing.

### Reference Documents

#### Design Documentation

![Phase 1 Low Level Diagram](http://i.imgur.com/LNKEclE.png)

The Sputnik Capstone project is composed of two separate modules: The low-gain-radio (LGR) module and the system-controller (SysCon) module. The LGR is contains a microcontroller with an integrated transceiver referred to as the KW0x that facilitates wireless communication. The SysCon contains a radiation hardened watchdog controller that will be responsible for power cycling components after [Single-Event Upsets](https://en.wikipedia.org/wiki/Single_event_upset) happen. It will also contain only radiation hardened parts to ensure that its power domain is secure. However, for this project, the radiation-hardened components will be replaced with off-the shelf components to help reduce cost.

### Overview

#### Operational Description

The Portland State Aerospace Society is sponsoring this capstone based on the need for a command, control, and communications system for their CubeSat project. The focus of this project will be rapidly prototyping the LGR and SysCon which compose what is referred to as [Sputnik](https://en.wikipedia.org/wiki/Sputnik_1) because of it's requirements to be a simple, reliable space system. Sputnik will be responsible for long distance communications to and from earth while the CubeSat is in orbit, as well as, controlling and communicating with a payload that is housed within the CubeSat. On top of fulfilling these duties, once space bound, it will need to be able to deal with a temperature range of -40C to 80C and radiation events that could cause components to latch up.

### Pre-test preparation

#### Test equipment

The equipment needed for the tests is as follows: 
* Power Supply
    * Able to supply a minimum current of 1A at 3V for approximately 15 minutes
* Multimeter
* Oscilloscope
* Programmers for KW0x and ATMega128
* Environmental Chamber
* Vacuum Chamber
* Antennas

### Component Tests

The Component Tests will test components that are imperative to the core operation of intergrated circuits (microcontrollers, voltage regulators, etc.) that implement the desired functionality for the module they are a part of. These are usually small simple tests that ensure that everything is working properly before attempting any tests for functionality.

#### Supply Range Test

The Supply Range Test is for testing the voltage range operation of the LGR and SysCon. This is needed since both modules will be receiving a range of voltages from 3-5V from the power management system (another module in the CubeSat). This test will be done by gradually changing the output voltage on the power supply from 3V-5V and checking that the board still operates. This test also doubles as a test for the crystal, since by checking the crystal we can ensure that the MCU on either board is on.

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Supply Range Test            |
Test ID#                  | Supply_1.00                  |
Test Writer               | James Heath, Will Harrington | 
Description               | The purpose of this test is to demonstrate the functionality of the boards and their crystals at the required supply range limits. |
Tester Information        |  N/A  |
Name of Tester            |  James Heath (LGR), Shan Quinney (SC)  |
Time/Date                 |  5/29/2016, 5/29/2016  |
Hardware Version          |  LGR1.00, SC1.00  |
Setup                     |  Oscilloscope and Power supply in LID  |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Set voltage supply to 3.0V for LGR | Power LEDs light up (LED1, LED4 on LGR schematic)  | PASS (all 3) | 3.0V at 3.0V supply |
2 | Check that XTAL is operating with oscillscope | Desired frequency is shown on oscilloscope  | PASS (all 3)  | 32 MHz |
3 | Set voltage supply to 5V for LGR | Power LEDs light up (LED1, LED4 on LGR schematic)  | PASS (all 3) | 3.0V at 5.0V supply. |
4 | Check that XTAL is operating with oscillscope | Desired frequency is shown on oscilloscope  | PASS (all 3) | 32 MHz |
5 | Set voltage supply to 3.0V for SysCon | Measure V+ at 3.3V with multimeter  | PASS (all 2) | 3.0V at 3.0V |
6 | Check that XTAL is operating with oscillscope | Desired frequency is shown on oscilloscope  |  |  |
7 | Set voltage supply to 5V for SysCon | Measure V+ at 5V with multimeter  | PASS (all 2) | 3.0V at 5.0V |
8 | Check that XTAL is operating with oscillscope | Desired frequency is shown on oscilloscope  |  |  |  

#### Temperature Range Test

The Temperature Range Test is for checking that the LGR and SysCon operate in the range specified within the sputnik project requirements. Ideally, the LGR and SysCon will be inserted into an environmental chamber and chilled/heated to the min/max of this range. Because of time and resources, we will instead use an oven to test both the LGR and SC boards at the upper temperature bound and a mixture of dry ice and conventinal ice to test both boards at the lower temperature bounds. 

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Temperature Range Test       |
Test ID#                  | Temp_1.00                    |
Test Writer               | James Heath, Will Harrington, Shan Quinney | 
Description               | The purpose of this test is to demonstrate the functionality of the board at the requirement range limits. |
Tester Information        |    |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |    |
Setup                     |    |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Setup LGR for transmit operation. Place LGR in waterproof container. Place container in styrofoam cooler filled with mixture of dry ice and conventional ice to approximate -40C. | Power LEDs remain on while in chamber and bytes received outside of chamber by another LGR module |  |  |
2 | Setup SysCon for operation. Place SysCon in waterproof container. Place container in styrofoam cooler filled with mixture of dry ice and conventional ice to approximate -40C.| UART LEDs blink while in chamber  |  |  |
3 | Setup LGR for transmit operation.  Set oven temperature to 80C. Place LGR board in oven.| Power LEDs remain on while in chamber and bytes received outside of chamber by another LGR module |  |  |
4 | Setup SysCon for operation. Set oven temperatrue to 80C. Place SysCon board in oven.| UART LEDs blink while in chamber  |  |  |

#### Vacuum Test

To ensure application in space, the sputnik board will need to be able to run within a vacuum. For this test, the board will be set in a vacuum chamber and again have its operations tested. 

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Vacuum Test                  |
Test ID#                  | Vacuum_1.00                  |
Test Writer               | James Heath, Will Harrington | 
Description               | The purpose of this test is to demonstrate the functionality of the boards in a vacuum. |
Tester Information        | Need to make sure power supply can supply modules with power while inside of chamber  |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |    |
Setup                     | Power supply for powering modules |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Hook up LGR and SysCon as specified in schematic | Power LEDs on for both modules  |  |  |
2 | Setup modules inside of vacuum chamber | Power LEDs on for both modules  |  |  |
3 | Commence vacuum test in chamber | Power LEDs remain on for both modules  |  |  |

### System Tests

#### Radio Test

The purpose of this test is to confirm that the radio is capable of transmission and reception, as well as switching between the Tx and Rx lines. This test will be performed by sending a carrier signal from one board to the other and lighting an LED when receiving the signal. The test locations will be predetermined based on both convenience and also where the least restricted signal propagation path will occur.

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Radio Communication          |
Test ID#                  | RadCom_1.00                  |
Test Writer               | Shan Quinney/James Heath     | 
Description               | The purpose of this test is to ensure that the radio is capable of transmitting and receiving signals. |
Tester Information        |    |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |  Sputnik radio board version 1.00  |
Setup                     | Have boards at some short distance apart. Each location will have a Sputnik radio board with sufficient power supply. Each location will also have a method to verify GPS and time (cell phone).   |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Board A is made to transmit carrier signal. | Board B confirms receiving signal from board A by blinking LED.  |  |  |
2 | Board B is made to transmit carrier signal. | Board A confirms receiving signal from board B by blinking LED.  |  |  |

**Overall Test Result:**

#### Control Test

The system controller is the guardian of the system. It is present to ensure that the system is functioning correctly and that if any unintended event causes component latch-up or system errors, the system can be cycled or rebooted to return stability. This control system is the other half of the project. Eventually, this system will consist of a radiation hardened microcontroller (ATMegaS128) with supporting radiation hardened LDO. For the purpose of prototyping, the controller is a standard, off-the-shelf ATMega128 chip.

To test the control system, a method to simulate a latch-up event will be used to trigger the watchdog into action. Outlined is the kw0x lock-up test. In this test, the crystal on the kw0x will be shorted to cause an error in the radio system. The ATMega should sense that the radio is no longer functioning properly and trigger the reset line on the kw0x to initiate a reboot.

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Control Test       |
Test ID#                  | ATM_1.00                     |
Test Writer               | Shan Quinney                 | 
Description               | The purpose of this test is to demonstrate the effectiveness of the watchdog to restart key system functionality after radiation events. |
Tester Information        |    |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |  Board Rev.1, Filter Rev.1, Wire antenna  |
Setup                     |    |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Use a metal tool to cause a short across the crystal | The kw0x will loose the signal from the crystal.  |  |  |
2 | Probe the UART line between the controller and the kw0x to determine that the life line signal is lost | The UART line will be free of any signal between the kw0x and the controller.  |  |  |
3 | Monitor the controller to ensure that the reset line on the kw0x has been activated | The reset line on the kw0x will be activated in an effort to reboot the device.  |  |  |

**Overall Test Result:**

#### Command Test

The Command Test helps us understand whether the board is able to issue commands and update or respond based on these commands. To test this, the Microcontroller will send a command to an LED to light up. If the LED lights up, then the command was successful indicating that the board is able to issue commands.

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Command Test                 |
Test ID#                  | CMD_1.00                     |
Test Writer               | Will Harrington              | 
Description               | The purpose of this test is to demonstrate the effectiveness of the system controller to execute commands |
Tester Information        |    |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |    |
Setup                     |    |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Send command | Successful send  |  |  |
2 | Observe LED on prototype | LED lights up  |  |  |

**Overall Test Result:**

#### Functionality Test

                          |                              |
------------------------- | ---------------------------- |
Test Case Name            | Functionality Test           |
Test ID#                  | Func_1.00                    |
Test Writer               | James Heath, Will Harrington | 
Description               | The purpose of this test is to observe the desired functionality as outlined in the project requirements of the LGR and SysCon. |
Tester Information        | The test needs to be performed over a distance of 10km. Two LGR/SysCon setups will be needed we refer to them as Setup A and Setup B. By configure Setup X for TX, we mean that it is to send a command to the other module that will cause it to power cycle. By configure Setup X for RX, we mean that it is to listen for a command that will cause it to power cycle.  |
Name of Tester            |    |
Time/Date                 |    |
Hardware Version          |    |
Setup                     | Directional Antennas, Power supply, Test sites that are 10km a part   |

Step | Action | Expected Result | Pass/Fail | Comments |
---- | ------ | --------------- | --------- | -------- |
1 | Record GPS coordinates of Setup A and Setup B. Use Coordinate Distance Calculator to get distance.  | Distance is at least 10km  |  |  |
2 | Configure Setup A for TX and Setup B for RX. | Setup B power cycles  |  |  |
3 | Configure Setup B for TX and Setup A for RX. | Setup A power cycles  |  |  |
