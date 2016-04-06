.SUFFIXES:
OPENOCD_DIR = ./toolchain
OPENOCD_HEXFILE = ../firmware/c3.hex
OOCD_CFG = olimex_swd_kinetis.cfg
GDB_CFG = toolchain/gdboocd_ocd.cmd
LINKER_SCRIPT = toolchain/MKW01Z128.ld
ARCH = arm-none-eabi
CC = $(ARCH)-gcc
AS = $(ARCH)-as
CPPFLAGS = -I. -Idrivers -I/usr/local/arm-none-eabi/include
CFLAGS = -mthumb -mcpu=cortex-m0 -ffreestanding -fno-common -ggdb3 -std=gnu11
LDFLAGS = --specs=nosys.specs -static -nostartfiles -T$(LINKER_SCRIPT)

all: c3

c3: crt0.o c3.o drivers/port.o drivers/spi.o drivers/uart.o drivers/transceiver.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

rx: crt0.o rx.o drivers/port.o drivers/spi.o drivers/uart.o drivers/transceiver.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

tx: crt0.o tx.o drivers/port.o drivers/spi.o drivers/uart.o drivers/transceiver.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S $^ -o $@
%.o: %.s
	$(AS) $^ -o $@

%.hex: %
	$(ARCH)-objcopy -O ihex $^ $@

write: c3.hex
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $^ verify reset exit"

write_tx: tx.hex
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $^ verify reset exit"

write_rx: rx.hex
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $^ verify reset exit"

gdb: c3
	$(ARCH)-gdb -q $^ -x $(GDB_CFG)

clean:
	$(RM) c3 *.o *.hex *.s ./drivers/*.o

