#ifndef _GRAPH_H_   /* Include guard */
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define Vertex int
#define UGraph Graph
#define maxV 500000

Vertex visit[maxV];
int pre[maxV], low[maxV], sc[maxV], min[maxV];
Vertex stack[maxV];
int cnt, id, top, s, e;
int num[maxV];
int parent[maxV], dist[maxV];

struct node {
  struct node *next;
  Vertex w;
};

typedef struct node *Node;
struct graph {
  int V;      //numero de vértices
  int A;      //numero de arcos
  int **adj;  //matriz de adjacencia
};

typedef struct graph *Graph;


int **MATRIXinit (int x, int y, int value);

Graph GRAPHinit (int V);

void GRAPHinsertArc (Graph G, Vertex v, Vertex w);

void GRAPHremoveArc (Graph G, Vertex v, Vertex w);

Vertex randV (Graph G);

Graph GRAPHrand2 (int V, int E);

int reachRO (Graph G, Vertex s, Vertex t);

int GRAPHreach (Graph G, Vertex s, Vertex t);

void GRAPHbfs (Graph G);

void bfs (Graph G, Vertex v);

double averageDIST (Graph G);

void GRAPHfree (Graph G);

#endif
