#!/bin/sh
#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

if [ ! -d stand/limine ]; then
    curl -L https://github.com/Limine-Bootloader/Limine/releases/latest/download/limine-binary.tar.gz | gunzip | tar -xf -
    mkdir -p stand/
    mv limine-binary stand/limine/
    make -C stand/limine/
fi
