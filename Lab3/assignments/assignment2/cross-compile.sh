#!/bin/sh

aarch64-none-linux-gnu-gcc --version > cross-compile.txt
aarch64-none-linux-gnu-gcc -v 2>> cross-compile.txt
echo "" >> cross-compile.txt
aarch64-none-linux-gnu-gcc -print-sysroot >> cross-compile.txt