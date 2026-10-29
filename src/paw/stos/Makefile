#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

include ../../mk/paw.mk

.PHONY: all
all: nucleus machine

.PHONY: nucleus
nucleus:
	cd nucleus; $(MAKE)

.PHONY: machine
machine:
	cd arch/$(CONFIG_ARCH)/$(CONFIG_CHIP); $(MAKE)
