#include "graph.h"
#include <time.h>


int **MATRIXinit (int x, int y, int value) {
  int **adj;
  adj = malloc (x*sizeof (int *));
  for (int i = 0; i < y; i++) {
    adj[i] = malloc (y*sizeof (int));
  }

  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      adj[i][j] = value;
  return adj;
}

UGraph UGRAPHinit (int V) {
  UGraph G = malloc (sizeof (Graph));
  G->V = V;
  G->A = 0;
  G->adj = MATRIXinit (V, V, 0);
  return G;
}

void UGRAPHinsertArc (UGraph G, Vertex v, Vertex w) {
  if (v != w && G->adj[v][w] == 0) {
    G->adj[v][w] = 1;
    G->A++;
    G->adj[w][v] = 1;
  }
}

void UGRAPHfree (UGraph G) {
  for (int i = 0; i < G->V; i++) {
    free(G->adj[i]);
  }
  free (G);
}
