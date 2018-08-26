#include "graph.h"
#include <time.h>
#include <sys/time.h>

int main (int argc, char *argv[]) {
  struct timeval tv;


  srand(time(NULL));

  Vertex v, w;
  int count = 0, prev = -1, size;
  if (argc <= 1) {
    printf ("run ./randtocomple [graph size]\n");
    return 0;
  }
  size = atoi(argv[1]);
  Graph G = GRAPHinit (size);
  while (!isGRAPHcomplete(G)) {
    v = randV(G);
    if (prev != -1) {
      count++;
      GRAPHinsertArc (G, prev, v);
    }
    prev = v;
  }
  printf ("It took [%d] random generate numbers to fully connect the graph\n", count);
return 0;
}
