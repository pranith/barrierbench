ifneq (DEBUG, "-g")
	DEBUG += "-O2"
endif

IDIR = ../include
CC = gcc
CFLAGS = -Wall $(DEBUG) -I$(IDIR)

EXEC = gen_define.exe fitsincache.exe

all: $(EXEC)

.PHONY: all 

$(EXEC): %.exe : %.o defines.h
		  $(CC) $< -o $@ $(CPPFLAGS) 

$(OBJ): %.o : %.cpp 
		  $(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: debug
debug: clean
		  $(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: clean
clean:
	rm -f *.o *.exe
