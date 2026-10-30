#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

include ../../../../../mk/paw.mk

ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)
DFILES = $(CFILES:.c=.d)
MISC_OFILES = $(shell find ../../../ -name "*.o")

REAL_ROOT = $(GLOBAL_ROOT)/..
KERNEL_OUT = $(REAL_ROOT)/out/stoskrnl.sys
CFLAGS = 							\
	$(SYS_CFLAGS)					\
	-I$(GLOBAL_ROOT)/paw/stos/head

.PHONY: all
all: $(KERNEL_OUT)

.PHONY: $(KERNEL_OUT)
$(KERNEL_OUT): $(ASMOFILES) $(OFILES)
	$(LD) $(MISC_OFILES) -T host/link.ld -o $@

%.S.o: %.S
	$(PROMPT) "AS" $<
	$(CC) -c $(CFLAGS) $< -o $@

-include $(DFILES)
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
