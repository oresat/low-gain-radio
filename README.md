# OreSat "Low Gain Radio" board

![LGR Finished Board](http://i.imgur.com/TWKJRhW.png)

## Overview

The Low Gain Radio module is part of the sputnik capstone project and is the communications pipeline for the CubeSat.  

![OreSat to LGR block diagram](http://i.imgur.com/t1GpLoK.png)  

The module is centered around a microcontroller with an integrated transceiver and RF front end. Commands will be sent and received through this module. In most cases the system controller will assist in executing those commands. Communication with the system controller is done via a UART connection between the two modules.


## Main Topics
[Parts Selection](https://github.com/oresat/low-gain-radio/blob/master/docs/Parts_Selection.md#parts-selection-for-low-gain-radio)  
[Bill of Materials](https://github.com/oresat/low-gain-radio/blob/master/docs/low-gain-radio_BOM.xlsx)  
[Eagle Schematic](https://github.com/oresat/low-gain-radio/blob/master/eagle/low-gain-radio.sch)    
[Eagle Layout](https://github.com/oresat/low-gain-radio/blob/master/eagle/low-gain-radio.brd)    
[Test Plan](https://github.com/oresat/low-gain-radio/blob/master/docs/Test_Plan_Sputnik_Capstone.md#sputnik-capstone-test-plan)    

## Contents

datasheets - datasheets for components used

docs - documentation

eagle - contains Schematic and PCB layout for the Low Gain Radio

tools - contains firmware and tools for compiling/debugging

## Project team

Industry Sponsor: Andrew Greenberg (adg@ece.pdx.edu)

Faculty Advisor: Dr. Christof Teuscher (teuscher@pdx.edu)

* Capstone Team
* 
    * Jake Heath (jakeheath@gmail.com)

    * Shan Quinney (quinney@pdx.edu) 

    * William Harrington (wrh2@pdx.edu)

    * Mike Mathis (mdmathis@gmail.com)
