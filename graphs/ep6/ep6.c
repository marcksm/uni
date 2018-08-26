//#include "graph.h"
#include <time.h>
#include "pqueue.h"


int main (int argv, int *argc[]) {
  Graph G = GRAPHinit (8);
  int weight[] = {5, 4, 7, 2, 1, 3, 1, 4};
  GRAPHinsertArc (G, 0, 1);
  GRAPHinsertArc (G, 0, 2);
  GRAPHinsertArc (G, 0, 3);
  GRAPHinsertArc (G, 2, 3);
  GRAPHinsertArc (G, 2, 4);
  GRAPHinsertArc (G, 2, 5);
  GRAPHinsertArc (G, 3, 5);
  GRAPHinsertArc (G, 4, 5);
  GRAPHinsertArc (G, 5, 6);
  GRAPHinsertArc (G, 6, 7);
  GRAPHminpath (G, weight, 0, 7);
  return 0;
}
