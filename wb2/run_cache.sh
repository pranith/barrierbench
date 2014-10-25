#!/bin/bash

# arg=$*

rm -f nobarrier.txt barrier.txt
rm -f results.txt
make gen_define.exe
for ((arg = 1; arg <= 1024; arg = arg * 2))
do
    	./gen_define.exe $arg > defines.h
	rm -f fitsincache.o fitsincache.exe
   	make >& /dev/null
	./fitsincache.exe $arg | tee -a nobarrier.txt
	rm -f fitsincache.o fitsincache.exe
	make CPPFLAGS=-DUSE_BARRIER >& /dev/null
	./fitsincache.exe $arg | tee -a barrier.txt
done

cat barrier.txt >> results.txt
cat nobarrier.txt >> results.txt
