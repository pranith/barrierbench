#!/bin/bash

arg=$*

rm -f *.o *.exe
make gen_define.exe
./gen_define.exe $arg > defines.h
rm -f fitsincache.o fitsincache.exe
make #>& /dev/null
./fitsincache.exe $arg 
