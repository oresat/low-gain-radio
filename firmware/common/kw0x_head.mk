.PHONY:         clean
.SUFFIXES:
MKDIR_P         = mkdir -p
TOOLCHAIN_PATH  = ../toolchain
COMMON_PATH     = ../common
OPENOCD_DIR     = $(TOOLCHAIN_PATH)
OOCD_CFG        = $(TOOLCHAIN_PATH)/olimex_swd_kinetis.cfg
GDB_CFG         = $(TOOLCHAIN_PATH)/gdboocd_ocd.cmd
LINKER_SCRIPT   = $(COMMON_PATH)/MKW01Z128.ld
ARCH            = arm-none-eabi
CC              = $(ARCH)-gcc
AS              = $(ARCH)-as
INCDIR          = -I.\
		  -I./include\
		  -I../common/include\
		  -I../drivers/include\
		  -I../CMSIS/CMSIS/Include\
		  -I../CMSIS/Device/ARM/ARMCM0plus/Include\
		  -I/usr/arm-none-eabi/include

ASFLAGS         = -g -mcpu=cortex-m0plus $(INCDIR) 

CWARN           = -Wall -Wextra -Wstrict-prototypes -Wdisabled-optimization \
	          -Wdouble-promotion -Wformat=2 -Wfloat-equal \
	          -Waggressive-loop-optimizations -Wunsafe-loop-optimizations \
	          -Waggregate-return -Wlogical-op -Wmissing-include-dirs \
	          -Wpointer-arith -Wredundant-decls 
CPPFLAGS        = $(INCDIR) $(CWARN)

# Without _GNU_SOURCE we will get the posix version of string.h etc we want the arm-none-eabi libc for gcc
# see note in /usr/arm-none-eabi/include/string.h
CFLAGS          = -D_GNU_SOURCE -mthumb -mcpu=cortex-m0plus -ffreestanding -fno-common -ggdb3 -std=gnu11

LDFLAGS         =  --specs=nosys.specs -static -mthumb -mcpu=cortex-m0plus -nostartfiles -T$(LINKER_SCRIPT)
ASRCS           =
AOBJS           = $(ASRCS:.s=.o)
CMSIS_CSRCS     = ../cmsis-core/source/cmsis_nvic.c
CMSIS_COBJS     = $(CMSIS_CSRCS:.c=.o)
DRIVER_CSRCS    = $(wildcard ../drivers/*.c)
DRIVER_COBJS    = $(DRIVER_CSRCS:.c=.o)
COMM_CSRCS      = $(wildcard $(COMMON_PATH)/*.c)
COMM_COBJS      = $(COMM_CSRCS:.c=.o)

ifeq ($(shell git diff-index --quiet HEAD . ../common; echo $$?), 1)
INDEX_DIRTY = -M
else
INDEX_DIRTY =
endif

PSAS_VERSION = "\"$(VERSION_PREFIX)`git rev-parse --short HEAD`$(INDEX_DIRTY)\""
CFLAGS         += -DGIT_COMMIT_VERSION=$(PSAS_VERSION)






