#include "graph.h"
#include <time.h>
#define maxV 500000

Vertex visit[maxV];
int pre[maxV], low[maxV], sc[maxV];
Vertex stack[maxV];
int cnt, id, top;


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
  G->adj = MATRIXinit(V, V, 0);
  return G;
}
void GRAPHinsertArc (Graph G, Vertex v, Vertex w) {
  if (v != w && G->adj[v][w] == 0) {
    G->adj[v][w] = 1;
    G->A++;
  }
}
void GRAPHremoveArc (Graph G, Vertex v, Vertex w) {
  if (G->adj[v][w] == 1) {
    G->adj[v][w] = 0;
    G->A--;
  }
}

int GRAPHoutdegree (Graph G, Vertex v) {
  int i, all;
  all = 0;
  for (i = 0; i < G->V; i++)
    if (G->adj[v][i] == 1) all++;
  return all;
}

void GRAPHshow (Graph G) {
  Vertex v, w;
  for (v = 0; v < G->V; v++) {
    printf ("[%d]-%d:", GRAPHoutdegree(G, v), v);
    for (w = 0; w < G->V; w++)
      if (G->adj[v][w] == 1)
        printf ("%d ", w);
    printf("\n");
  }
  printf("\n");
}

void GRAPHshow_abc (Graph G) {
  Vertex v, w;
  char pt_br[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  for (v = 0; v < G->V; v++) {
    printf ("[%d]-%c:", GRAPHoutdegree(G, v), pt_br[v]);
    for (w = 0; w < G->V; w++)
      if (G->adj[v][w] == 1)
        printf ("%c ", pt_br[w]);
    printf("\n");
  }
  printf("\n");
}

Vertex randV (Graph G) {
  double r;
  r = rand()/(RAND_MAX + 1.0);
  return (r*G->V);
}

int isGRAPHcomplete (Graph G) {
  int size, i, j;
  size = G->V;
  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      if (i != j && G->adj[i][j] != 1) return 0;
  return 1;
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

int reachRO (Graph G, Vertex s, Vertex t) {
  visit[s] = 1;
  if (visit[t] == 1) return 1;
  for (Vertex w = 0; w < G->V; w++)
    if (G->adj[s][t] == 1 && visit[w] == 0)
      if (reachRO (G, w, t) == 1) return 1;
  return 0;
}

int GRAPHreach (Graph G, Vertex s, Vertex t) {
  Vertex v;
  for (v = 0; v < G->V; v++) visit[v] = 0;
  return reachRO (G, s, t);
}

void strongR (Graph G, Vertex v) {
  Vertex w;
  int min;
  Vertex p;

  pre[v] = cnt++;
  min = pre[v];
  stack[top++] = v;
  for (p = 0; p < G->V; p++) {
    if (G->adj[v][p] == 1) {
      w = p;
      if (pre[w] == -1) {
        strongR (G, w);
        if (low[w] < min) min = low[w];
      }
      else if (pre[w] < pre[v] && sc[w] == -1) { //existem um arco que abraça
        if (pre[w] < min) min = pre[w];
      }
    }
  }
  low[v] = min;
  if (pre[v] == low[v]) {
    do {
      w = stack[--top];          //0(V)
      sc[w]=id;
    } while (w != v);
    id++;
  }

}

int GRAPHscT (Graph G) {
//  devolve o numero de componentes
  Vertex v;
  for (v = 0; v < G->V; v++)
    pre[v] = sc[v] = -1;
  id = cnt = top = 0;
  for (v = 0; v < G->V; v++)
    if (pre[v] == -1)
      strongR (G, v);
  return (id);
}
