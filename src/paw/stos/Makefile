#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

include ../../mk/paw.mk

.PHONY: all
all: target nucleus machine postbuild

.PHONY: target
target:
	mkdir -p target/machine
	rsync -avr head/arch/$(CONFIG_ARCH)/$(CONFIG_CHIP)/*.h \
		target/machine

.PHONY: nucleus
nucleus:
	cd nucleus; $(MAKE)

.PHONY: machine
machine:
	cd arch/$(CONFIG_ARCH)/$(CONFIG_CHIP); $(MAKE)

.PHONY: postbuild
postbuild:
	rm -rf target
