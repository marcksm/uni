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
  int **cst;
};

typedef struct graph *Graph;


//void nodefree(Node p);

//Node newnode (Vertex w);

int **MATRIXinit (int x, int y, int value);

Graph GRAPHinit (int V);

void GRAPHinsertArc (Graph G, Vertex v, Vertex w);

void GRAPHremoveArc (Graph G, Vertex v, Vertex w);

Vertex randV (Graph G);

Graph GRAPHrand2 (int V, int E);

void GRAPHfree (Graph G);

void GRAPHcsttoedge (Graph G, int *weight);

Vertex *GRAPHspt2 (Graph G, Vertex s);

void GRAPHminpath (Graph G, int *weight, int s, int e);

void GRAPHpathprint (int *parent, int k);

#endif
