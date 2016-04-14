ifneq (DEBUG, "-g")
	DEBUG += "-O2"
endif

IDIR = ../include
CC = gcc
CPPFLAGS = -ggdb -O0 -Wall $(DEBUG) -I$(IDIR) -std=gnu11

EXEC = gen_lfence.exe gen_define.exe fitsincache.exe

all: $(EXEC)

.PHONY: all 

$(EXEC): %.exe : %.o defines.h
		  $(CC) $< -o $@ $(CPPFLAGS) 

$(OBJ): %.o : %.cpp defines.h
		  $(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: debug
debug: clean
		  $(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: clean
clean:
	rm -f *.o *.exe
