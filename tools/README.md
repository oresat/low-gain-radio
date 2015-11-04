# Tools

Tool chain for programming MKW01Z128

## Dependencies

[OpenOCD](http://openocd.org)

[GCC ARM Embedded](https://launchpad.net/gcc-arm-embedded)

## Contents

c3.c -- some really simple c code to inject into the microcontroller

Makefile -- make utility for easy compiling

MKW01Z128.ld -- linker script

olimex_swd_kinetis.cfg -- config file for OpenOCD

## Example usage

> make

> make write