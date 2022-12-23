#!/bin/sh

make clean -C ../../finder-app
make -C ../../finder-app CROSS_COMPILE=aarch64-none-linux-gnu-
file ../../finder-app/writer > fileresult.txt