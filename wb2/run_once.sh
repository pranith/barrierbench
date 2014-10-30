#!/bin/bash

arg=$*

make gen_write.exe
./gen_write.exe $arg > defines.h
rm -f fitsincache.o fitsincache.exe
make >& /dev/null
perf stat -B -e cache-references,cache-misses,cycles,instructions ./fitsincache.exe $arg 
rm -f fitsincache.o fitsincache.exe
make CPPFLAGS=-DUSE_BARRIER >& /dev/null
perf stat -B -e cache-references,cache-misses,cycles,instructions ./fitsincache.exe $arg 
