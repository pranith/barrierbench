#!/bin/bash

# arg=$*

repeat=3
rm -f nobarrier.txt barrier.txt
rm -f results.txt
make gen_write.exe
for ((i = 0; arg <= 128; i = i + 1))
do
	let arg=$i*2;
	if(("$arg" == "0")); then 
		arg=1; 
	fi
    	./gen_write.exe $arg > defines.h
	rm -f fitsincache.o fitsincache.exe
   	make >& /dev/null
	./fitsincache.exe $arg $repeat | tee -a nobarrier.txt
	rm -f fitsincache.o fitsincache.exe
	make CPPFLAGS=-DUSE_BARRIER >& /dev/null
	./fitsincache.exe $arg $repeat | tee -a barrier.txt
done

cat barrier.txt >> results.txt
cat nobarrier.txt >> results.txt
