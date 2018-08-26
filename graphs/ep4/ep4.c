#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <time.h>

int UGRAPHisARC (UGraph G, Vertex v, Vertex w) {
  if (G->adj[v][w] == 1 && G->adj[w][v] == 1) return 1;
  return 0;
}

void UGRAPHremoveARC (UGraph G, Vertex v, Vertex w) {
  G->adj[v][w] = 0;
  G->adj[w][v] = 0;
}

void UGRAPHaddARC (UGraph G, Vertex v, Vertex w) {
  G->adj[v][w] = 1;
  G->adj[w][v] = 1;
}

UGraph UGRAPHrand2 (int V, int E) {
  double p = (double) E/V/(V-1);
  UGraph G = GRAPHinit (V);
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

int UGRAPHbridges (UGraph G) {
  Vertex v = 0, w = 0;
  int before = 0, after = 0, bridge = 0;
  for (v = 0; v < G->V; v++) {
    for (w = 0; w < G->V; w++) {
      if (v != w && UGRAPHisARC (G, v, w) == 1) {
        before = GRAPHscT (G);
        UGRAPHremoveARC (G, v, w);
        after = GRAPHscT (G);
        UGRAPHaddARC(G, v, w);
        if (after > before) bridge++;
      }
    }
  }
  return bridge;
}

int main () {
  srand (time(NULL));
  UGraph G = UGRAPHrand2 (20, 24);
  printf("%d\n", UGRAPHbridges (G));
  return 0;
}
