# Tools

Tool chain for programming MKW01Z128

## Dependencies

[OpenOCD](http://openocd.org)

[GCC ARM Embedded](https://launchpad.net/gcc-arm-embedded)

## Contents

c3.c -- some really simple c code to inject into the microcontroller

crt0.c -- stuff needed to initialize the MCU

kw0x.h -- register definitions, needed for bit banging

Makefile -- make utility for easy compiling

MKW01Z128.ld -- linker script

olimex_swd_kinetis.cfg -- config file for OpenOCD

## Example usage

> make

> make write

## Manual Debug procedure

Eventually, we will script this part away with a simple make gdb command. For now, this is the procedure you need to follow to debug c3.c.

After doing a make write, to debug the code using GDB, follow the steps below. You will want multiple terminals or a terminal multiplexer to do this.

1. start up openOCD in a terminal as such
> openocd -f olimex_swd_kinetis.cfg

You should see something like...
```
Open On-Chip Debugger 0.9.0 (2015-05-28-12:05)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
Info : FTDI SWD mode enabled
Info : add flash_bank kinetis kw01.flash
adapter speed: 1000 kHz
none separate
cortex_m reset_config sysresetreq
Info : clock speed 1000 kHz
Info : SWD IDCODE 0x0bc11477
Info : kw01.cpu: hardware has 2 breakpoints, 2 watchpoints
Info : MDM: Chip is unsecured. Continuing.
```

At which point you can proceed to step 2. Note: you need to be in whatever directory that has the olimex_swd_kinetis.cfg file in order to do this.

2. telnet to the openOCD server in another terminal

>telnet localhost 4444

You should see something like this:
```
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Open On-Chip Debugger
> 
```

You will want to halt the chip to attach gdb. Do this by entering "reset halt". It should result in something like this...

```
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Open On-Chip Debugger
> reset halt
MDM: Chip is unsecured. Continuing.
target state: halted
target halted due to debug-request, current mode: Thread 
xPSR: 0x01000000 pc: 0x000000c4 msp: 0x1ffff400
> 
```

3. Attach gdb

You must be in the working directory of the code to do this. (e.g. if you are debugging c3.c go to the directory where that file is)

Once you are in the working directory of the code you can issue the following command:

> arm-none-eabi-gdb c3

You will see something like this...

```
GNU gdb (GNU Tools for ARM Embedded Processors) 7.8.0.20150604-cvs
Copyright (C) 2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-apple-darwin10 --target=arm-none-eabi".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
c3: No such file or directory.
(gdb) 
```

Now type target remote:3333 to attach gdb. You will want to set a breakpoint for main by typing b main. Then type c for continue and you will be within the main function of c3.c
