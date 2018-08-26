CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
LDFLAGS_ep1sh = -lreadline
LDFLAGS_ep1 = -pthread

.PHONY: all
all: ep1 ep1sh

ep1: ep1.o process.h processQueue.h processQueue.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_ep1)

ep1sh: ep1sh.o StringSeparation.h StringSeparation.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS_ep1sh)

.PHONY: clean
clean:
	-rm -f *.o ep1sh ep1 *~
