#!/bin/bash

# arg=$*

repeat=5
rm -f nobarrier.txt barrier.txt
rm -f results.txt
make clean
make gen_write.exe
for ((arg = 1; arg <= 64; arg = arg + 1))
do
    	./gen_write.exe $arg
	rm -f fitsincache.o fitsincache.exe
   	make >& /dev/null
	./fitsincache.exe $arg $repeat | tee -a nobarrier.txt
	rm -f fitsincache.o fitsincache.exe
	make CPPFLAGS=-DUSE_BARRIER >& /dev/null
	./fitsincache.exe $arg $repeat | tee -a barrier.txt
done

cat barrier.txt >> results.txt
cat nobarrier.txt >> results.txt
