#!/bin/bash

# arg=$*

make gen_define.exe
for ((arg = 1; arg < 128; arg = arg * 2))
do
    	./gen_define.exe $arg > defines.h
	rm -f fitsincache.o fitsincache.exe
   	make >& /dev/null
	./fitsincache.exe $arg 
	rm -f fitsincache.o fitsincache.exe
	make CPPFLAGS=-DUSE_BARRIER >& /dev/null
	./fitsincache.exe $arg 
done
