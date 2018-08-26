#include "graph.h"

int dfsRaugment (UGraph G, Vertex v, Vertex *match) {
    Vertex s, w;
    for (w = 0; w < G->V; w++) {
        if (G->adj[v][w] == 1) {
             /*color[w] = 1*/
            if (visit[w] == 0) {
                visit[w] = 1;
                if (match[w] == -1) {
                    match[w] = v;
                    match[v] = w;
                    return 1;
                }
                /* w esta emparelhado */
                s = match[w];
                if (dfsRaugment (G, s, match)) {
                    match[w] = v;
                    match[v] = w;
                    return 1;
                }
            }
        }
    }
    return 0;
}
int augmentMatching (UGraph G, int *color, Vertex *match) {
   Vertex v, s;
   for (s = 0; s < G->V; s++) visit[s] = 0;
   for (v = 0; v < G->V; v++)
      if (color[v] == 0 && match[v] == -1 && visit[v] == 0)
         if (dfsRaugment(G, v, match))
            return 1;
   return 0;
}

int main () {
  //Exemplo retirado da pagina https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/matching-bipartite.html
    UGraph G = UGRAPHinit (10);
    UGRAPHinsertArc (G, 0, 5);
    UGRAPHinsertArc (G, 0, 6);
    UGRAPHinsertArc (G, 1, 5);
    UGRAPHinsertArc (G, 1, 6);
    UGRAPHinsertArc (G, 2, 5);
    UGRAPHinsertArc (G, 2, 6);
    UGRAPHinsertArc (G, 3, 5);
    UGRAPHinsertArc (G, 3, 6);
    UGRAPHinsertArc (G, 3, 7);
    UGRAPHinsertArc (G, 3, 8);
    UGRAPHinsertArc (G, 3, 9);
    UGRAPHinsertArc (G, 4, 7);
    UGRAPHinsertArc (G, 4, 8);
    UGRAPHinsertArc (G, 4, 9);
    int *color = malloc (G->V * sizeof (int));
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
    color[3] = 0;
    color[4] = 0;
    color[5] = 1;
    color[6] = 1;
    color[7] = 1;
    color[8] = 1;
    color[9] = 1;
    int *match = malloc (G->V * sizeof (int));
    match[0] =- 1;
    match[1] = 5;
    match[2] = 6;
    match[3] = -1;
    match[4] = 8;
    match[5] = 1;
    match[6] = 2;
    match[7] = -1;
    match[8] = 4;
    match[9] = -1;
    for (int i = 0; i < G->V; i++) printf ("[%d]", match[i]);
    printf ("\n");
    printf ("%d\n", augmentMatching (G, color, match));
    for (int i = 0; i < G->V; i++) printf ("[%d]", match[i]);
    printf ("\n");
    UGRAPHfree(G);
    return 0;
}
