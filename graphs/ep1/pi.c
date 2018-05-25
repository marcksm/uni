#include "graph.h"

int main (int argc, char *argv[]) {
  FILE *entrada;
  Graph G = GRAPHinit (10);
  int c, prev = -1, count = 0;
  entrada  = fopen ("pi1000.txt", "r");
  if (argc > 1) {
    count = atoi(argv[1]);
    if (entrada) {
      c = getc (entrada);
      c = getc (entrada);
      while ((c = getc (entrada)) != EOF) {
        if (count == 0) break;
        if (prev != -1){
          GRAPHinsertArc (G, prev-48, c-48);
        }
        prev = c;
        count--;
      }
      GRAPHshow(G);
    }
    else printf ("pi txt file not found\n");
  }
  else {
    printf ("run ./pi [casas do PI]\n");
  }
  fclose (entrada);
  return 0;
}
