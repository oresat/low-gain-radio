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
* lgr.c -- firmware for LGR
* rx.c -- firmware for KW0x breakout board, receiver configuration for KW0x
* tx.c -- firmware for KW0x breakout board, transmitter configuration for KW0x
* Makefile -- make utility for easy compiling


## Example usage

* To compile

        > make

* To compile and write to the flash on the LGR
        > make write_lgr

* To compile, write to the flash on the MCU, and start up a gdb session

        > make gdb_lgr

* To clean up

        > make clean
