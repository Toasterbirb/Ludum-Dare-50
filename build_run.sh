#!/bin/sh
set -e

make clean
make -j4
./build/application
