/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

#include "rankCyclers.h"
#include <stdio.h>
#include <stdlib.h>
#include "erro.h"

static int N;
static double **rank, **cyclers;

void initRankCyclers (int n) {
    if ((rank = malloc (6 * sizeof (double *))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((cyclers  = malloc (3 * sizeof (double *))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[0] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[1] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[2] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[3] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[4] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((rank[5] = malloc (((2 * n) +1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");

    if ((cyclers[0] = malloc (((2 * n) + 1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((cyclers[1] = malloc (((2 * n) + 1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    if ((cyclers[2] = malloc (((2 * n) + 1) * sizeof (double))) == NULL)
        fatalError ("Couldn't allocate sufficient memory");

    for (int k = 0; k < 2 * n + 1; k++) {
        rank[0][k] = 0;
        rank[1][k] = 0;
        rank[2][k] = 0;
        rank[3][k] = 0;
        rank[4][k] = 0;
        rank[5][k] = 0;

        cyclers[0][k] = 0;
        cyclers[1][k] = 0;
        cyclers[2][k] = 0;
    }
    N = n;
}
void setCycler (int cycler, double rk) {
    int d = 0;
    if (cycler <= N) d = 1;
    else d = 2;
    cyclers[0][cycler] = rk;
    rank[0][(int)rk] = cycler;
    cyclers[d][cycler] = rk;
    rank[2*d][(int)rk] = cycler;

}

void updateCycler (int cycler, double dist, int initPos) {
  int d = 0, count = 0;
  double auxd = 0, auxr = 0;
  if (cycler <= 0) fatalError ("Invalid Cycler");
  if (cycler <= N) d = 1; /*time 1*/
  else d = 2; /*time2*/
    for (int k = 0; count < 2; k = k + d, count++) {
        rank[2*k+1][(int)cyclers[k][cycler]] = dist + initPos;
        if (cyclers[k][cycler] > 1) {
          for (int i = 1; ((cyclers[k][cycler]-i) > 0 &&
          (rank[(2*k+1)][(int)cyclers[k][cycler]-i+1] > rank[(2*k+1)][(int)cyclers[k][cycler]-i])); ) {
            auxd = rank[(2*k+1)][(int)cyclers[k][cycler]-i];
            rank[(2*k+1)][(int)cyclers[k][cycler]-i] = rank[(2*k+1)][(int)cyclers[k][cycler]-i+1];
            rank[(2*k+1)][(int)cyclers[k][cycler]-i+1] = auxd;
            auxr = rank[2*k][(int)cyclers[k][cycler]-i];
            rank[2*k][(int)cyclers[k][cycler]-i] = rank[2*k][(int)cyclers[k][cycler]-i+1];
            rank[2*k][(int)cyclers[k][cycler]-i+1] = auxr;
            cyclers[k][cycler]--;
            cyclers[k][(int)auxr]++;
          }
        }
    }
}


int rankTeam (int cycler) {
  int x;
  if (cycler <= N) x = 1;
  else x = 2;
  return ((int)cyclers[x][cycler]);
}


int rankCycler (int rk, int team) {
   return (int)rank[2*team][rk];
}

int rankCyclerOverall (int rk) {
    int count = 0, i = 1, j = 1;
    double a, b;
    while (1) {
        a = rank[3][i];
        b = rank[5][j];
        if (a > b) {
            i++; count++;
            if (count == rk) return (int)rank[2][i-1];
        }
        else if (b > a) {
            j++; count++;
            if (count == rk) return (int)rank[4][j-1];
        }
        else {
            i++; j++; count++;
            if (count == rk) return (int)rank[2][i-1];
        }

    }

}

double *queue_i_rank (int mode) {
  if (mode == 1) return rank[2];
  else if (mode == 2) return rank[4];
  else fatalError ("Invalid mode\n");
  return NULL;
  }


double *queue_i_cycler (int mode) {
  return cyclers[mode];
}


void destroyRankCyclers () {
    for (int i = 0; i < 6; i++) {
        free (rank[i]);
    }
    for (int i = 0; i < 3; i++) {
        free (cyclers[i]);
    }
    free (rank);
    free (cyclers);
}
