CC=gcc
CFLAGS= -Wall -Wno-unused-result -pedantic -O3
LDFLAGS= -lm -fopenmp

.PHONY: all
all: EP

%: %.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

.PHONY: clean
clean:
	rm -rf EP *.o
