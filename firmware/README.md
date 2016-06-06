# Tools

This folder contains resources for the toolchain we are using for programming the Freescale/NXP MKW01Z128 microcontroller. For an in-depth explanation on the toolchain, [please see this wiki page](https://github.com/wrh2/sputnik/wiki/MKW01Z128-toolchain).

## Dependencies

[OpenOCD](http://openocd.org)

[GCC ARM Embedded](https://launchpad.net/gcc-arm-embedded)

## Contents

**Folders**
* drivers -- contains peripherial drivers that we've developed so far for the MKW01Z128
* examples -- contains some simple example code for using the microcontroller (MKW01Z128) on the breakout board
* toolchain -- contains linker script, config for OpenOCD

**Files**
* c3.c -- some really simple c code to inject into the microcontroller
* crt0.c -- stuff needed to initialize the MCU
* kw0x.h -- register definitions, needed for bit banging
* Makefile -- make utility for easy compiling


## Example usage

* To compile

        > make

* To compile and write to the flash on the MCU

        > make write

* To compile, write to the flash on the MCU, and start up a gdb session

        > make gdb

* To clean up

        > make clean
