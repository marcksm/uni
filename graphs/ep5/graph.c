#include "graph.h"
#include <time.h>

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
          //printf (" (%d-%d) ", v, w);
          GRAPHinsertArc(G, v, w);
          GRAPHinsertArc(G, w, v);
        }
      }
    }
  }
  //printf ("\n");
   return G;
}

Queue QUEUEinit (int V) {
  s = 0;
  e = 0;
  queuesize = V*V*V;
  Queue Q = malloc (queuesize * sizeof (Queue));
  return Q;
}

Vertex QUEUEget (Queue Q) {
  Vertex w = Q[s].w;
  s = (s+1)%queuesize;
  return w;
}
void QUEUEput (Queue Q, Vertex v) {
  Q[e].w = v;
  e = (e + 1)%queuesize;
}

void QUEUEfree (Queue Q) {
  free (Q);
}

int QUEUEempty (Queue Q) {
  if (s == e) return 1;
  return 0;
}
void GRAPHbfs (Graph G) {
  Vertex v;
  cnt = 0;
  for (v = 0; v < G->V; v++)
    min[v] = num[v] = parent[v] = -1;
  for (v = 0; v < G->V; v++)
    if (num[v] == -1)
      bfs (G, v);
}

void bfs (Graph G, Vertex v) {
  Node p;
  Vertex u;
  Queue Q;
  Q = QUEUEinit (G->V);
  min[v] = cnt++;
  parent[v] = v;
  QUEUEput (Q, v);
  while (!QUEUEempty (Q)) {
    //printf ("a\n");
    u = QUEUEget(Q);
    //for (p = G->adj[u]; p != NULL; p = p->next) {
    for (int w = 0; w < G->V; w++) {
      if (G->adj[u][w] == 1) {
        if (num[w] == -1) {
          parent[w] = u;
          num[w] = cnt++;
        //  printf ("%d, ", num[p->w]);
          QUEUEput(Q, w);
        }
      }
    }
  }
  //printf ("\n");
  QUEUEfree(Q);
}

void resetDIST(Graph G) {
  for (int i = 0; i < G->V; i++) {
    parent[i] = -1;
    dist[i]= INF;
    min[i] = 0;
  }
}

void GRAPHminPath (Graph G, Vertex s) {
  Vertex v;
  Queue Q;
  Node p;
  resetDIST(G);
  Q = QUEUEinit (G->V);
  for (v = 0; v < G->V; v++) {
    dist[v] = 99;
    parent[v] = -1;
  }
  dist[s] = 0;
  parent[s] = s;
  QUEUEput(Q, s);

  while (!QUEUEempty (Q)) {
    //printf("a\n");
    v = QUEUEget(Q);
    for (int w = 0; w < G->V; w++) {
      if (G->adj[v][w] == 1) {
        if (parent[w] == -1) {
          dist[w] = dist[v] + 1;
          //printf ("%d-", dist[w]);
          parent[w] = v;
          QUEUEput (Q, w);
        }
      }
    }
  }
  QUEUEfree(Q);
}

void GRAPHfree (Graph G) {
  for (int i = 0; i < G->V; i++) {
    free(G->adj[i]);
  }
  free (G);
}


double averageDIST (Graph G) {
  double av = 0, total = 0, reach = 0;
  resetDIST(G);
  GRAPHbfs (G);
  for (int i = 0; i < G->V; i++) {
    GRAPHminPath (G, i);
    for (int k = 0; k < G->V; k++) {
        if (k != i && dist[k] != 99) {
          av += dist[k];
          reach = reach + 1;
        }

    }

    if (reach == 0) av = 0;
    else av = (double)av/(double)reach;

    reach = 0;
    total = total + av;
    av = 0;
  }
  total = (double)total/(double)G->V;
  return total;
}
