#!/bin/bash

# arg=$*

make gen_define.exe
for arg in {1..50}
do
    ./gen_define.exe $arg > defines.h
    rm -f fitsincache.o fitsincache.exe
    make >& /dev/null
    ./fitsincache.exe $arg 
done
