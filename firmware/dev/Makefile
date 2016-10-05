KW0X_COMMON_PATH = ../common

include $(KW0X_COMMON_PATH)/kw0x_head.mk

XPROJ = dev

.SECONDARY: $(XPROJ).s

# CFLAGS	+= -DDEBUG_UART
CFLAGS		+= -DTPM_TEST

# For Development
CWARN           += -Wno-comment -Wno-unused

include $(KW0X_COMMON_PATH)/kw0x_tail.mk


