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
OUT1 = peterson
OBJ1 = peterson.o
OUT2 = peterson_c11
OBJ2 = peterson_c11.o
OUT3 = relaxed
OBJ3 = peterson_relaxed.o

all: $(OUT1) $(OUT2)

.PHONY: all

$(OUT1): $(OBJ1)
	$(CC) $(OBJ1) -o $@ $(CFLAGS)

$(OUT2): $(OBJ2)
	$(CC) $(OBJ2) -o $@ $(CFLAGS)

$(OUT3): $(OBJ3)
	$(CC) $(OBJ3) -o $@ $(CFLAGS)

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
	rm -f *.o *~ relaxed peterson peterson_c11 *.lst
