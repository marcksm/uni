#ifndef _GRAPH_H_   /* Include guard */
#define _GRAPH_H_
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define Vertex int

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

int GRAPHoutdegree (Graph G, Vertex v);

void GRAPHshow (Graph G);

void GRAPHshow_abc (Graph G);

int isGRAPHcomplete (Graph G);

Vertex randV (Graph G);

#endif
