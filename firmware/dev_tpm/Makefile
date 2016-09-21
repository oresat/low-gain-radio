KW0X_COMMON_PATH = ../common

include $(KW0X_COMMON_PATH)/kw0x_head.mk

XPROJ = dev_tpm

.SECONDARY: $(XPROJ).s

# CFLAGS	+= -DDEBUG_UART
CFLAGS  += -Wa,-adhln -g

# For Development
CWARN           += -Wno-comment -Wno-unused

include $(KW0X_COMMON_PATH)/kw0x_tail.mk


