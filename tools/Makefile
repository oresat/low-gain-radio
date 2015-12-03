.SUFFIXES:
OPENOCD_DIR = .
OPENOCD_HEXFILE = ../firmware/c3.hex
OOCD_CFG = olimex_swd_kinetis.cfg
LINKER_SCRIPT = MKW01Z128.ld
#LINKER_SCRIPT = gcc/MKW01Z128xxx4_flash.ld
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
CFLAGS = -mthumb -mcpu=cortex-m0 -ffreestanding -fno-common -ggdb3
LDFLAGS = --specs=nosys.specs -static -nostdlib -T$(LINKER_SCRIPT) 

all: c3

c3: crt0.o c3.o
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.s: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -S $^ -o $@
%.o: %.s
	$(AS) $^ -o $@

%.hex: %
	arm-none-eabi-objcopy -O ihex $^ $@

write: c3.hex
	openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $^ verify reset" -c "exit"

clean:
	$(RM) c3 *.o *.hex *.s
