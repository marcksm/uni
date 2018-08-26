#include "graph.h"
#include "pqueue.h"
#include <time.h>

#define INFINITY G->V
int queuesize;
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
  G->cst = MATRIXinit (V, V, 0);
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

void GRAPHcsttoedge (Graph G, int *weight) {
  for (int v = 0; v < G->V; v++) {
    for (int w = 0; w < G->V; w++) {
      if (G->adj[v][w] == 1) {
        G->cst[v][w] = weight[v];
      }
    }
  }
}

void GRAPHminpath (Graph G, int *weight, int s, int e) {
  GRAPHcsttoedge (G, weight);
  int *parent = GRAPHspt2 (G, s);
  GRAPHpathprint(parent, e);
  if (parent[e] != -1) printf ("%d\n", e);
}

void GRAPHpathprint (int *parent, int k) {
  if (parent[k] == k) { return;}
  if (parent[k] != -1) GRAPHpathprint (parent, parent[k]);
  if (parent[k]!= -1) printf ("%d->", parent[k]);
}

Vertex *GRAPHspt2 (Graph G, Vertex s) {
   Vertex *hook = malloc (G->V * sizeof (int));
   int *dist = malloc (G->V * sizeof (int));
   Vertex *parent = malloc (G->V * sizeof (Vertex));
   // inicialização:
  for (Vertex v = 0; v < G->V; ++v)
      parent[v] = -1, dist[v] = INFINITY;
   parent[s] = s, dist[s] = 0;
   PQUEUE PQ = PQUEUEinit(G->V);
   //for (link a = G->adj[s]; a != NULL; a = a->next) {
   for (int w = 0; w < G->V; w++) {
      if (G->adj[s][w] == 1) {
        dist[w] = G->cst[s][w];
        PQUEUEinsert (PQ, w, dist[w]);

        hook[w] = s;
      }
   }

   while (!PQUEUEempty(PQ)) {

      QUEUE min = PQUEUEdelmin(PQ);
      Vertex y = min->v;
      parent[y] = hook[y];
      // atualização de dist[]:
      //for (link a = G->adj[y]; a != NULL; a = a->next) {
      for (int w = 0; w < G->V; w++) {
        if (G->adj[y][w] == 1) {
           int cst = G->cst[y][w];
           if (dist[w] == INFINITY) {
              dist[w] = dist[y] + cst; // relaxa y-w
              PQUEUEinsert (PQ, w, dist[w]);
              hook[w] = y;
           }
           else if (!(dist[y] + cst >= dist[w])) {
              dist[w] = dist[y] + cst; // relaxa y-w
              PQUEUEupdate (PQ, w, dist[w]);
              hook[w] = y;
           }
      }
   }
  }
   PQUEUEfree(PQ);
   free(hook);
   return parent;
}

void GRAPHfree (Graph G) {
  for (int i = 0; i < G->V; i++) {
    free(G->adj[i]);
  }
  free (G);
}
