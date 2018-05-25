#include "graph.h"
#include <time.h>
#include <sys/time.h>

int howManyPaths (Graph G) {
  int caminhos = 0;
  for (int x = 0; x < G->V; x++)
    for (int y = x; y < G->V; y++)
      if (x!=y) {
          caminhos += GRAPHreach (G, x, y);
      }
  return caminhos;
}

int main (int argv, int *argc[]) {
  int percent = atoi((char*)argc[1]);
  printf ("#Vertices \tArestas \tMédia\n");
  srand(time(NULL));
  int randv1=0, randv2=0, caminhos = 0;
  double p = 0;
  for (int V = 2  ; V < 100; V++)  {
    for (int A = 1; A <= (V*(V-1))/2; A++) {
      Graph G = GRAPHrand2 (V, A);
      caminhos = howManyPaths (G);
      p = (double)caminhos/((V*(V-1))/2);
      for (int i = 0; i < G->V; i++)
        free(G->adj[i]);
      free (G->adj);
      free (G);
      caminhos = 0;
      if (p >= (double)percent/100) {
        printf ("%d \t\t%d \t\t%f\n", V, A, p);
        p = 0;
        break;
      }
    }
  }
  return 0;
}
