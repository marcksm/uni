#ifndef _PQUEUE_H_   /* Include guard */
#define _PQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
struct queue {
  Vertex v;
  int cst;
};
typedef struct queue *QUEUE;

struct pqueue {
  int start, end, size, N;
  QUEUE v;
};


typedef struct pqueue *PQUEUE;

PQUEUE PQUEUEinit (Vertex V);

void PQUEUEinsert (PQUEUE PQ, Vertex w, int c);

int PQUEUEempty (PQUEUE PQ);

QUEUE PQUEUEdelmin (PQUEUE PQ);

void PQUEUEdec (PQUEUE PQ, Vertex v, int cst);

int PQUEUEsize (PQUEUE PQ);

int PQUEUEisPQ (PQUEUE PQ);

void PQUEUEupdate (PQUEUE PQ, Vertex v, int cst);

void PQUEUEfree(PQUEUE PQ);

#endif
