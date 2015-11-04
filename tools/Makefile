OPENOCD_DIR = .
OPENOCD_HEXFILE = ../firmware/c3.hex
OOCD_CFG = olimex_swd_kinetis.cfg
CC = arm-none-eabi-gcc
CFLAGS = -mthumb -mcpu=cortex-m0

all: c3
	

write:
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $(OPENOCD_HEXFILE) verify reset"

clean:
	rm c3.o