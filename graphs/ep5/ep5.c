#include "graph.h"
#include <time.h>

int main (int argv, int *argc[]) {
  srand(time(NULL));
  int V = atoi((char*)argc[1]);
  int E;
  int i = 300;
  double av = 0;
    for (E = 1; E <= 2*V*V; E = 2 * E) {
      Graph G = GRAPHrand2 (V, E);
      av = averageDIST (G);
      printf ("%d\t%f\t%d\n", E, av, V);
      GRAPHfree (G);
    }
  return 0;
}
