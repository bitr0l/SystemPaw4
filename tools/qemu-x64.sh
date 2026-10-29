#!/bin/sh
#
# Copyright (c) 2026, Chloe M., et al.
# Provided under the BSD-3 clause
#

qemu-system-x86_64            \
    -cdrom out/sp4.iso  \
    --enable-kvm              \
    -m 2G                     \
    -serial stdio             \
    -device virtio-vga-gl     \
    -display sdl,gl=on        \
    -smp 4                    \
    -cpu host
