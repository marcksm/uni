#include "pqueue.h"
#include <time.h>

PQUEUE PQUEUEinit (Vertex V) {
  PQUEUE PQ = malloc (sizeof (struct pqueue));
  PQ->N = V;
  PQ->start = 1;
  PQ->end = 1;
  PQ->size = 0;

  PQ->v = malloc (PQ->N * sizeof (struct queue));
  return PQ;
}

static int greater (PQUEUE PQ, int x, int y) {
  if (PQ->v[x].cst > PQ->v[y].cst) return 1;
  return 0;
}

static int less(PQUEUE PQ, int x, int y) {
  if (PQ->v[x].cst < PQ->v[y].cst) return 1;
  return 0;
}
static void PQUEUEexch(PQUEUE PQ, int x, int y) {
  int csttmp = PQ->v[x].cst;
  Vertex v = PQ->v[x].v;
  PQ->v[x].cst = PQ->v[y].cst;
  PQ->v[x].v = PQ->v[y].v;
  PQ->v[y].cst = csttmp;
  PQ->v[y].v = v;
}

static void PQUEUEbottomup (PQUEUE PQ) {
  int k = PQ->end;
  while (k > 1 && greater(PQ, k/2, k)) {
    PQUEUEexch(PQ, k, k/2);
    k = k/2;
  }
}

int PQUEUEempty (PQUEUE PQ) {
  if (PQUEUEsize (PQ) == 0) return 1;
  else return 0;
}

void PQUEUEinsert (PQUEUE PQ, Vertex w, int c) {
  if (PQUEUEsize (PQ) > PQ->N) {printf ("FAZER O RESIZE!\n"); exit(0);}//PQUEUEresize (PQ);//fazer dps
  PQ->v[PQ->end+1].v = w;
  (PQ->v[PQ->end+1]).cst = c;
  PQ->end++;
  PQUEUEbottomup(PQ);
  // for (int i = 1; i <= PQ->end; i++) {
  //   printf ("%d, ", PQ->v[i].cst);
  // }
  // printf ("\n");
}

static void PQUEUEtopdown (PQUEUE PQ, int k) {
  int n = PQ->end;
  while (2*k <= n) {
    int j = 2*k;
    if (j < n && greater(PQ, j, j+1)) j++;
    if (!greater(PQ, k, j)) break;
    PQUEUEexch (PQ, k, j);
    k = j;
  }
}

QUEUE PQUEUEdelmin (PQUEUE PQ) {
 if (PQUEUEempty (PQ)){ printf ("PQ is empty!\n"); exit(0); }
 QUEUE min = &PQ->v[1];
 PQUEUEexch (PQ, 1, PQ->end);
 PQ->end--;
 PQUEUEtopdown (PQ, 1);
 return min;
}

void PQUEUEdec (PQUEUE PQ, Vertex v, int cst) {
  PQUEUEtopdown (PQ, 1);
  PQUEUEbottomup (PQ);
}

int PQUEUEsize (PQUEUE PQ) {
  PQ->size = PQ->end - PQ->start;
  return PQ->size;
}
static int isPQ (PQUEUE PQ, int k) {
  int n = PQ->end;
  if (k > n) return 1;
  int left = 2*k;
  int right = 2*k + 1;
  if (left <= n && greater (PQ, k, left)) return 0;
  if (right <= n && greater (PQ, k, right)) return 0;
  return isPQ (PQ, left) && isPQ (PQ, right);
}

int PQUEUEisPQ (PQUEUE PQ) {
  return isPQ (PQ, 1);
}

void PQUEUEupdate (PQUEUE PQ, Vertex v, int cst) {
  for (int i = 1; i < PQ->end; i++) {
    if (PQ->v[i].v == v) {
      PQ->v[i].cst = cst;
    }
  }
}

void PQUEUEfree(PQUEUE PQ) {
    free (PQ->v);
    free (PQ);
}
