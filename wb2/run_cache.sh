#!/bin/bash

# arg=$*

make gen_define.exe
for arg in {1 2 4 8 10 16 20 25 32}
do
    ./gen_define.exe $arg > defines.h
    rm -f fitsincache.o fitsincache.exe
    make >& /dev/null
    ./fitsincache.exe $arg 
done
