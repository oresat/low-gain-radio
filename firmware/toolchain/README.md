
### Code Style

* see psas.astylerc

### Openocd configuration

#### Programmer

* In the olimex programmer cfg file for openocd you may need to change this line if you are using a different programmer

* select appropriate programmer by hand

* This one:
* source [find interface/ftdi/olimex-arm-usb-tiny-h.cfg]
* OR:
source [find interface/ftdi/olimex-arm-usb-ocd.cfg]

#### Configuration files

* olimex_swd_kinetis.cfg
* gdboocd_ocd.cmd

