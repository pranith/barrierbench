ifneq (DEBUG, "-g")
	DEBUG += "-O2"
endif

IDIR = ../include
CC = gcc
CFLAGS = -Wall $(DEBUG) -I$(IDIR) -lrt
LDFLAGS = -lrt

EXEC = gen_define.exe fitsincache.exe gen_write.exe

all: $(EXEC)

.PHONY: all 

$(EXEC): %.exe : %.o defines.h common.h
		  $(CC) $< -o $@ $(CPPFLAGS)  $(LDFLAGS)

$(OBJ): %.o : %.cpp %.h
		  $(CC) -o $@ -c $< $(CPPFLAGS)

.PHONY: debug
debug: clean
		  $(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: clean
clean:
	rm -f *.o *.exe
