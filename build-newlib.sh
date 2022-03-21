#!/bin/bash
# build the esp32 newlib
# taken from: https://gist.github.com/igrr/92f6115dd0986b3a82a46d2ba729b519
set -e

OUTPUT_DIR="$(dirname $(realpath $0))/build-newlib"

cd newlib-esp32

./configure \
    --with-newlib \
    --enable-multilib \
    --disable-newlib-io-c99-formats \
    --disable-newlib-supplied-syscalls  \
    --enable-newlib-nano-formatted-io \
    --enable-newlib-reent-small \
    --enable-target-optspace \
    --program-transform-name="s&^&xtensa-esp32-elf-&" \
    --disable-option-checking \
    --with-target-subdir=xtensa-esp32-elf \
    --target=xtensa-esp32-elf \
    --prefix=$OUTPUT_DIR

CROSS_CFLAGS="-DSIGNAL_PROVIDED -DABORT_PROVIDED -DMALLOC_PROVIDED"
make all install