ifneq (DEBUG, "-g")
	DEBUG += -O2
endif
CC=gcc
CXX=g++
CFLAGS = -std=gnu99 -lpthread -Wall $(DEBUG) 
LDFLAGS = -std=gnu99 
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

.PHONY: clean

clean:
	rm -f *.o *~ peterson
