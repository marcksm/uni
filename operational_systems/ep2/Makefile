#*******************************************************************************
#
#    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
#    Matheus Tavares Bernardino      nº USP: 9292987
#
#
#*******************************************************************************

CC = gcc
CFLAGS = -Wall -pedantic -std=gnu99
LDFLAGS = -pthread -lm

ep2: ep2.o rankCyclers.h randomCyclers.h rankCyclers.o randomCyclers.o erro.o erro.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o ep2 *~
