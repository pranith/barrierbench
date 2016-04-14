#!/bin/bash

arg=$*

rm -f *.o *.exe
make gen_lfence.exe >& /dev/null
./gen_lfence.exe $arg > defines.h
rm -f fitsincache.o fitsincache.exe
make >& /dev/null
perf stat -r 10 --log-fd 1 -- ./fitsincache.exe $arg 
