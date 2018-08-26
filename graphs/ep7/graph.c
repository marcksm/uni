#include "graph.h"
#include <time.h>

#define INFINITY G->V

int INF;

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

Graph GRAPHinit (int V) {
  Graph G = malloc (sizeof (Graph));
  G->V = V;
  G->A = 0;
  G->adj = MATRIXinit (V, V, 0);
  INF = G->V;
  return G;
}

void GRAPHinsertArc (Graph G, Vertex v, Vertex w) {
  if (v != w && G->adj[v][w] == 0) {
    G->adj[v][w] = 1;
    G->A++;
  }
}

Vertex randV (Graph G) {
  double r;
  r = rand()/(RAND_MAX + 1.0);
  return (r*G->V);
}

Graph GRAPHrand2 (int V, int E) {
  double p = (double) E/V/(V-1);
  Graph G = GRAPHinit (V);
  Vertex v, w;
  for (v = 0; v < G->V; v++) {
    for (w = 0; w < G->V; w++) {
      if (v != w) {
        if (rand() < p * (RAND_MAX+1.0)) {
          GRAPHinsertArc(G, v, w);
          GRAPHinsertArc(G, w, v);
        }
      }
    }
  }
  return G;
}

void GRAPHfree (Graph G) {
  for (int i = 0; i < G->V; i++) {
    free(G->adj[i]);
  }
  free (G);
}
