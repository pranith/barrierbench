#!/bin/bash

arg=$*

make gen_define.exe
./gen_define.exe $arg > defines.h
rm -f fitsincache.o fitsincache.exe
make >& /dev/null
perf stat -B -e cache-references,cache-misses,cycles,instructions ./fitsincache.exe $arg 
