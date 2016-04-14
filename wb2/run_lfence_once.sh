#!/bin/bash

arg=$*

gcc gen_lfence.c -o gen_lfence.exe
./gen_lfence.exe $arg
rm -f fitsincache.o fitsincache.exe
make >& /dev/null
perf stat -B -e cache-references,cache-misses,cycles,instructions ./fitsincache.exe $arg 
rm -f fitsincache.o fitsincache.exe
make CPPFLAGS=-DUSE_BARRIER >& /dev/null
perf stat -B -e cache-references,cache-misses,cycles,instructions ./fitsincache.exe $arg 
