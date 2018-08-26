/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

#include "randomCyclers.h"
#include "erro.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int N;
static int **cyclers;

/* Recebe um inteiro cycler e um inteiro mode, e remove o cycler da fila mode
 */
static void randRemove (int cycler, int mode);


void initRandomCyclers (int n) {
    if ((cyclers = malloc (3 * sizeof (int *))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    for (int i = 0; i < 3; i++)
        if ((cyclers[i] = malloc (((2 * n) + 1) * sizeof (int))) == NULL)
            fatalError ("Couldn't allocate sufficient memory");
    for(int i = 1; i <= (2 * n) + 1 ; i++) {
        if (i <= n) cyclers[1][i] = i;
        else cyclers[2][i%(n+1)] = i-1;
        cyclers[0][i%((2*n)+1)] = i;
    }
    cyclers[1][0] = n;
    cyclers[2][0] = n;
    cyclers[0][0] = 2 * n;
    N = n;
    time_t seed = time (NULL);
    if (seed == (time_t) -1) fatalError ("Could't get time");
    srand (seed);
}

int getRandomCycler (int mode) {
    int i = -1, cycler = -1;
      if (mode > 0 && mode < 3) {
        if (cyclers[mode][0] == 0) fatalError ("Cycler unavaliable\n");
        i = rand() / (RAND_MAX / cyclers[mode][0]) + 1;
        cycler = cyclers[mode][i];
        randRemove (i, mode);
    }
    else if (mode == 0) {
      if (cyclers[0][0] == 0) fatalError ("Cycler unavaliable\n");
      i = rand() / (RAND_MAX / cyclers[0][0]) + 1;

      cycler = cyclers[mode][i];
      if (i > cyclers[1][0]) randRemove (i-cyclers[1][0], 2);
      else randRemove (i, 1);

    }
    else fatalError ("Invalid mode\n");

    return cycler;
}
void removeCycler (int cycler) {
  int i = -1;

  for (i = 1; i <= cyclers[0][0]; i++)
    if (cycler == cyclers[0][i]) break;
  cycler = cyclers[0][i];
  if (i > cyclers[1][0]) randRemove (i-cyclers[1][0], 2);
  else randRemove (i, 1);

}
static void randRemove (int cycler, int mode) {
    int temp, lastCycler, k;
    if (mode == 1) k = 1;
    else if (mode == 2) k = 2;

    if (cyclers[k][0] < 1) fatalError ("Cycler unavaliable\n");
    lastCycler = cyclers[k][0];
    temp = cyclers[k][lastCycler];
    cyclers[k][lastCycler] = cyclers[k][cycler];
    cyclers[k][cycler] = temp;
    cyclers[k][0]--;

    if (k == 1) {
      lastCycler = cyclers[0][0] - cyclers[2][0];
      temp = cyclers[0][lastCycler];
      cyclers[0][lastCycler] = cyclers[0][cycler];
      cyclers[0][cycler] = temp;
      for (int x = lastCycler; x < cyclers[0][0]; x++)
        cyclers[0][x] = cyclers[0][x+1];
      cyclers[0][0]--;
    }
    else if (k == 2) {
      lastCycler = cyclers[0][0];
      temp = cyclers[0][lastCycler];
      cyclers[0][lastCycler] = cyclers[0][cycler+cyclers[1][0]];
      cyclers[0][cycler+cyclers[1][0]] = temp;
      cyclers[0][0]--;
    }
}

int getNumberCyclers (int mode) {
    return cyclers[mode][0];
}

int isCyclerEmpty (int mode) {
    return cyclers[mode][0] == 0;
}

int *avaliableCyclers (int mode) {
    return cyclers[mode];
}

void destroyRandomCyclers () {
    for (int i = 0; i < 3; i++) {
        free (cyclers[i]);
    }
    free  (cyclers);
}

void resetRandomCyclers (int n) {
    destroyRandomCyclers ();
    if ((cyclers = malloc (3 * sizeof (int *))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    for (int i = 0; i < 3; i++)
        if ((cyclers[i] = malloc (((2 * n) + 1) * sizeof (int))) == NULL)
            fatalError ("Couldn't allocate sufficient memory");
    for(int i = 1; i <= (2 * n) + 1 ; i++) {
        if (i <= n) cyclers[1][i] = i;
        else cyclers[2][i%(n+1)] = i-1;
        cyclers[0][i%((2*n)+1)] = i;
    }
    cyclers[1][0] = n;
    cyclers[2][0] = n;
    cyclers[0][0] = 2 * n;
    N = n;
}
