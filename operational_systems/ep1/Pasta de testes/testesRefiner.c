#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fatalError (char *msg) {
    fprintf (stderr, "testesRefiner Error: %s\n", msg);
    exit (EXIT_FAILURE);
}

int qProcessos;
int tScheduler;
int contextChanges;
int deadlines;
int deadlinesVector[30];
int contextChangesVector[30];
double Xb;
double S;
double mm;


double mean (int n, int *v) {
    double me = 0.0;
    for (int i = 0; i < n; i++) me += v[i];
    me /= n;
    return me;
}


double varAmoCor (int n, int *v, double mean) {
    double s = 0.0;
    for (int i = 0; i < n; i++) s += ((double) v[i] - mean) * ((double) v[i] - mean);
    return s / (n - 1);
}





int main (int argc, char **argv) {
    if (argc < 2) fatalError ("Forneça o nome do arquivo com os testes");
    FILE *testes = fopen (argv[1], "r");
    FILE *refined = fopen ("refinedOutput.txt", "w");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 30; k++) {
                if (fscanf (testes, "%d %d %d %d", &qProcessos, &tScheduler,
                &contextChanges, &deadlines) == EOF)
                    fatalError ("erro lendo o arquivo testes");
                deadlinesVector[k] = deadlines;
                contextChangesVector[k] = contextChanges;
            }

            Xb = mean (30, deadlinesVector);
            S = sqrt (varAmoCor (30, deadlinesVector, Xb));
            mm = 2.045 * S / sqrt (30);
            fprintf (refined, "Quantidade de deadlines média cumpridas pelo escalonador %d com %d processos: %lf +- %lf\n", tScheduler, qProcessos, Xb, mm);

            Xb = mean (30, contextChangesVector);
            S = sqrt (varAmoCor (30, contextChangesVector, Xb));
            mm = 2.045 * S / sqrt (30);
            fprintf (refined, "Quantidade de mudanças de contexto média cumpridas pelo escalonador %d com %d processos: %lf +- %lf\n", tScheduler, qProcessos, Xb, mm);


        }
    }

    fclose (testes);
    fclose (refined);
    return 0;
}
