CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
LDFLAGS_traceGenerator = -lm
LDFLAGS_ep1 = -pthread

.PHONY: all
all: ep1 traceGenerator

ep1: ep1.o process.h processQueue.h processQueue.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_ep1)

traceGenerator: traceGenerator.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_traceGenerator)

.PHONY: clean
clean:
	-rm -f *.o traceGenerator ep1 *~ *.txt
