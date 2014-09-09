ifneq (DEBUG, "-g")
	DEBUG += "-O2"
endif

IDIR = ../include
CC = gcc
CPPFLAGS = -Wall $(DEBUG) -I$(IDIR)

EXEC = gen_define.exe read64_independent.exe  fitsincache.exe

all: $(EXEC)

.PHONY: all 

$(EXEC): %.exe : %.o 
		  $(CC) $< -o $@ $(CPPFLAGS) 

$(OBJ): %.o : %.cpp 
		  $(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: debug
debug: clean
		  $(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: clean
clean:
	rm -f *.o *.exe
