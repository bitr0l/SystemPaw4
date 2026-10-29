#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

include ../../../../../mk/paw.mk

ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
MISC_OFILES = $(shell find ../../../ -name "*.o")

REAL_ROOT = $(GLOBAL_ROOT)/..
KERNEL_OUT = $(REAL_ROOT)/out/stoskrnl.sys
CFLAGS = $(SYS_CFLAGS)

.PHONY: all
all: $(KERNEL_OUT)

.PHONY: $(KERNEL_OUT)
$(KERNEL_OUT): $(ASMOFILES)
	$(LD) $(MISC_OFILES) -T host/link.ld -o $@

%.S.o: %.S
	$(CC) -c $(CFLAGS) $< -o $@
