#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

.SILENT:

PROMPT = printf "%s\t\t%s\n"

CC = 	\
	clang
LD = 	\
	ld.lld

#
# Determine the architecture target for the C compiler
#
ifeq ($(CONFIG_ARCH),amd64)
	CC_ARCH_TARGET = x86_64-unknown-elf
else
	CC_ARCH_TARGET =
endif

SYS_CFLAGS =    		\
	-Wall				\
	-pedantic			\
	-MMD				\
	-nostdinc			\
	-nostdlib			\
	-ffreestanding		\
	-I$(GLOBAL_ROOT)/sdk/head	\
	-I$(GLOBAL_ROOT)/paw/stos/target \
	-target $(CC_ARCH_TARGET)	\
	-D_BOOT_PROTO='"$(CONFIG_BAL_BACKEND)"'

ifeq ($(CONFIG_ARCH),amd64)
	SYS_CFLAGS += 		\
		-mno-red-zone	\
		-mno-sse		\
		-mno-sse2		\
		-mno-avx		\
		-mno-avx2		\
		-mno-3dnow		\
		-mcmodel=kernel
endif
