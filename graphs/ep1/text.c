#include "graph.h"

int main () {

  Graph G = GRAPHinit (26);
  int c, prev = -1;
    while ((c = getc(stdin)) != EOF) {
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        c = tolower(c);
        if (prev != -1) GRAPHinsertArc (G, prev -  97, c - 97);
        prev = c;
      }
      else {
        prev = -1;
        c = 0;
      }
    }
  GRAPHshow_abc (G);
  return 0;
}
