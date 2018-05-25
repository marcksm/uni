#include "graph.h"
#include <time.h>
#include <sys/time.h>

 void destroy (Graph G) {
  for (int i = 0; i < G->V; i++)
        free(G->adj[i]);
  free (G->adj);
  free (G);
 }

double mean (int V, int A) {
  double comp = 0;
  for (int T = 0; T < 100; T++) {
    Graph G = GRAPHrand2 (V, A);
    comp += GRAPHscT (G);
    destroy (G);
  }
  return (double)comp/100;
}

int main (int argv, int *argc[]) {
  double v[10];
  double mn = 0;
  int V = atoi((char*)argc[1]);
  srand(time(NULL));
  int A = 0;
  v[0] = 0.2;
  v[1] = 0.5;
  v[2] = 1;
  v[3] = 2;
  v[4] = 5;
  v[5] = 10;
  v[6] = 20;
  printf ("V\t A\t Média sc\n");
  for (int i = 0; i < 7; i++) {
    A = (double)v[i]*V;
    mn = mean (V, A);
    printf ("%d\t%d\t%.2f\n", V, A, mn);
  }
  return 0;
}
