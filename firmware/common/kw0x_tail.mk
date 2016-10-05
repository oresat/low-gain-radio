
COBJS =  $(DRIVER_COBJS) $(COMM_COBJS) $(XPROJ).o

all: $(XPROJ)

$(XPROJ): $(COBJS) $(AOBJS)
	@echo "-------- LINKING $@ "
	$(CC) $(LDFLAGS) $^ -o $@
	@echo "------------------------------------------"
	arm-none-eabi-size $@
	@echo "------------------------------------------"

%.s: %.c
	@echo "----.c.s--- COMPILING $@ "
	@$(CC) $(CPPFLAGS) $(CFLAGS) -S $^ -o $@

%.o: %.s
	@echo "----.s.o--- COMPILING $@ "
	@$(AS) $(ASFLAGS) $^ -o $@

%.hex: %
	@echo "-------- CREATE HEX FILE $@ "
	@$(ARCH)-objcopy -O ihex $^ $@

write: $(XPROJ).hex
	@echo "-------- SEND HEX FILE TO FLASH"
	@openocd -s $(OPENOCD_DIR) -f $(OOCD_CFG) -c "program $^ verify reset exit"

gdb: $(XPROJ)
	@echo "-------- STARTING GDB"
	@$(ARCH)-gdb -q $^ -x $(GDB_CFG)

clean:
	$(RM) $(XPROJ) *.o *.hex *.s ../drivers/*.s ../drivers/*.o ../common/*.o

rebuild: clean
	$(MAKE)
