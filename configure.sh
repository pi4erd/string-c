#!/bin/sh

# For some rea
COMPILER=gcc

mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=${COMPILER}
cd ..
