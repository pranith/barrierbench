ifneq (DEBUG, "-g")
	DEBUG += -O2
else
	DEBUG += -Wa,-adhln
endif
CC=gcc
CXX=g++
CFLAGS = -std=gnu11 -lpthread -lrt -Wall $(DEBUG)
LDFLAGS = -std=gnu11 $(DEBUG)
CXXFLAGS = -std=g++11
OUT = peterson
OBJ = peterson.o 

all: $(OUT)

.PHONY: all

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $@ $(CFLAGS)

%.o : %.cc %.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: debug

debug: clean
	$(MAKE) $(MAKEFILE) all DEBUG="-g"

.PHONY: lst

lst: clean
	$(MAKE) $(MAKEFILE) all DEBUG="-Wa,-adhln -g" > file.lst

.PHONY: clean

clean:
	rm -f *.o *~ peterson *.lst
