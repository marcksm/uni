#ifndef _GRAPH_H_   /* Include guard */
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#define Vertex int
#define UGraph Graph
#define maxV 500000

Vertex visit[maxV];
int parent[maxV];

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

typedef struct graph *UGraph;

int **MATRIXinit (int x, int y, int value);

UGraph UGRAPHinit (int V);

void UGRAPHinsertArc (UGraph G, Vertex v, Vertex w);

void UGRAPHfree (UGraph G);


#endif
