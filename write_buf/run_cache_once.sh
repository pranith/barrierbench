#!/bin/bash

arg=$*

echo $arg
rm -f *.o *.exe
make gen_lfence.exe >& /dev/null
./gen_lfence.exe $arg > defines.h
rm -f fitsincache.o fitsincache.exe
make >& /dev/null
./fitsincache.exe $arg 
./fitsincache.exe $arg 
./fitsincache.exe $arg 
./fitsincache.exe $arg 
./fitsincache.exe $arg 
