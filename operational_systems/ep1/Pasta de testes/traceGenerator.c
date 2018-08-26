#define outputFileNameMax 500
#define processNameMax 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int quantTraceFiles;
double maxArrivedProcPerSec;
int procPerFile;
double dtMax;
double deadlineMaxProportion;

void fatalError (char *msg) {
    fprintf (stderr, "traceGenerator Error: %s\n", msg);
    exit (EXIT_FAILURE);
}

double getRandom (double a, double b) {
    double r;
    char *command = malloc (300 * sizeof (char));
    sprintf (command, "python3 getRandom.py %f %f", a, b);
    FILE *random = popen (command, "r");
    fscanf (random, "%lf", &r);
    pclose (random);
    free (command);
    return r;
}


int main (int argc, char **argv) {
    if (argc < 6) fatalError ("Parametros insuficientes");

    srand48 (time (NULL));

    if (sscanf (argv[1], "%d", &quantTraceFiles) == EOF) fatalError ("Erro nos parâmetos");
    if (sscanf (argv[2], "%lf", &maxArrivedProcPerSec) == EOF) fatalError ("Erro nos parâmetos");
    if (sscanf (argv[3], "%d", &procPerFile) == EOF) fatalError ("Erro nos parâmetos");
    if (sscanf (argv[4], "%lf", &dtMax) == EOF) fatalError ("Erro nos parâmetos");
    if (sscanf (argv[5], "%lf", &deadlineMaxProportion) == EOF) fatalError ("Erro nos parâmetos");

    FILE *output;
    char *outputFileName;
    char *processName;
    double t0, dt, deadline;
    double lim = 1.0 / (maxArrivedProcPerSec + 1);
    double rand;
    double lim2, lim3;
    double diff;

    int procs;
    double seg;
    int j;

    for (int i = 0; i < quantTraceFiles; i++) {
        outputFileName = malloc (outputFileNameMax * sizeof (char));
        if (sprintf (outputFileName, "trace%d.txt", i) < 0) fatalError ("Erro com sprintf");
        output = fopen (outputFileName, "w");
        free (outputFileName);

        procs = 0;
        seg = 0.0;
        while (procs < procPerFile) {
            rand = drand48 ();
            for (j = 1; rand > j * lim; j++);
            if (j > 1) {
                lim2 = 0.0;
                lim3 = 1.0 / (j - 1);
                diff = lim3 - lim2;
            }
            for (int k = 0; k < j - 1 && procs < procPerFile; k++) {
                t0 = seg + getRandom (lim2, lim3);
                lim3 += diff;
                lim2 += diff;
                dt = getRandom (0.000001, dtMax);
                deadline = (t0 + dt) * getRandom (1.0 , deadlineMaxProportion);
                processName = malloc (processNameMax * sizeof (char));
                if (sprintf (processName, "proc%d", procs) < 0) fatalError ("Erro com sprintf");
                fprintf (output, "%f %s %f %f\n", t0, processName, dt, deadline);
                free (processName);
                procs++;
            }
            seg += 1;
        }


        fclose (output);
    }
    return 0;
}
