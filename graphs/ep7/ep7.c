#include "graph.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recurcolor (Graph G, int *color, int k, Vertex v) {
  int c = 0;
  int not = 0;
  if (v == G->V) return 1;

  for (c = 1; c <= k; c++) {

    //printf ("[%d,%d]\n",v, c);
    not = 0;
    for (int j = 0; j < G->V; j++) {
      if (G->adj[v][j] == 1 && color[j] == c) {
        not = 1;
        break;
      }
    }
    if (not == 1) { not = 0; continue; }
    color[v] = c;
    if (recurcolor (G, color, k, v + 1)) return 1;
    color[v] = 0;
  }
  return 0;
}

int iskcolor (Graph G, int k) {
  int *color = malloc (G->V * sizeof (int));
  for (int i = 0; i < G->V; i++) color[i] = 0;
  if (recurcolor (G, color, k, 0)) {free(color); return 1;}
  free(color);
  return 0;
}


int UGRAPHseqColoring (Graph G) {
  Vertex v;
  int *color = malloc (G->V * sizeof (int));

  int *disp = malloc (G->V * sizeof (int));
  int k = 0, i;

  for (v = 0; v < G->V; v++)
    color[v] = -1;

  for (v = 0; v < G->V; v++) {
    for (i = 0; i < k; i++)
      disp[i] = 1;
    for (int j = 0; j < G->V; j++)
      if (G->adj[v][j] == 1 && color[j] != -1)
        disp[color[j]] = 0;
    for (i = 0; i < k; i++)
      if (disp[i]) break;
    if (i == k)
      color[v] = k++;
    else
      color[v] = i;
  }
  free (disp);
  free(color);
  return k;
}


int main (int argc, char **argv) {
  srand(time(NULL));
  FILE *f;
  f = fopen("output", "w");
  int V, E;
  for (int x = 0; x < 12; x++)
    for (int a = 1; a < x*x; a++ ) {
      int mean = 0;
      int r = 0;
      printf("#V:%d E:%d\n", x, a);
      fprintf (f, "#V:%d E:%d\n", x, a);
      for (int t = 0; t < 100; t++) {
        V = x;
        E = a;
        Graph G = GRAPHrand2 (V, E);
        int q = UGRAPHseqColoring(G);
        mean += q;
        if (t == 0) {
          for (int i = 1; i <= V; i++) {
            int k = iskcolor(G, i);
            if (k) {
              r = i;
              printf ("Exact:%d\n",i);
              fprintf (f, "Exact:%d\n",i);
              break;
            }
          }
        }


        GRAPHfree(G);
      }
      double g = (double)mean/100;
      printf ("Heuristic:%f\n", g);
      fprintf (f, "Heuristic:%f\n", g);
      printf ("#--------------\n");

    }
    fclose(f);
  return 0;
}
