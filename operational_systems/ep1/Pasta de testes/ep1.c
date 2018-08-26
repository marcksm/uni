/*******************************************************************************
*   ep1 - MAC0422 - Sistemas Operacionais
*       Professor: Daniel Batista
*
*   09/set/2016
*
*   por:
*   Matheus Tavares Bernardino,      nº USP: 9292987
*   Marcos Vinicius do Carmo Sousa,  nº USP: 9298274
*
*******************************************************************************/


/******************************************************************************/
/*              Bibliotecas, defines e declarações de funções                 */
/******************************************************************************/


#include <stdio.h> // fprintf, fscanf, fopen, fclose
#include <stdlib.h> // exit
#include <string.h> // strcmp
#include <sys/time.h> // gettimeofday
#include <pthread.h> // pthread_create, pthread_join, pthread_mutex_lock,
// pthread_mutex_lock, pthread_mutex_init, pthread_mutex_unlock
#define _GNU_SOURCE // para o sched_getcpu
#include <sched.h> // sched_getcpu
#include "process.h"
#include "processQueue.h"

int sched_getcpu ();
void error (char *message);
void fatalError (char *message);
unsigned long int simElapsedTime ();
void readTraceFile (FILE *trace);
void *fcfsGate (void *a);
void *fcfsProcessFunction (void *a);
void fcfsScheduler (FILE *output);
void *srtnProcessFunction (void *a);
void srtnScheduler (FILE *output);
void *multQueueGate (void *a);
void multQueueScheduler (FILE *output);
void *multQueueProcessFunction (void *a);


/******************************************************************************/
/*                            Variáveis Globais                               */
/******************************************************************************/



/******************************************************************************/
/*          Variáveis globais comuns à mais de um escalonador                 */

process **processList; //Lista que contem todos os processos do arquivo de trace
int quantProcess; // Quantidade de processos da lista acima

struct timeval simInitTime; // Tempo do início da simulação

int extraInfo; // Var. binaria para representar a requisição ou não, do usuario,
               // de informações extras ao longo da simulação

processQueue *pQueue; // Fila de processos para os simuladores dos escalonadores
                        //fcfs e srtn

process exePr; // Esta variável guarda informações do processo atualmente em
               // execução, se houver um

int contextChanges; // Quantidade de mudanças de contexto


/******************************************************************************/
/*                    Variáveis globais para o FCFS                           */

pthread_mutex_t  pQueueMutex; // mutex para proteger o acesso à pQueue


/******************************************************************************/

/*                    Variáveis globais para o SRTN                           */

int processFinished; // Var. para o processo comunicar ao escalonador srtn que
                     // ele acabou
int stop; // Var. para o escalonador srtn comunicar um processo para ele parar

pthread_mutex_t processFinishedMutex, stopMutex; // Mutex para proteger as vars.
                                                 // acima


/******************************************************************************/
/*                Variáveis globais para o multiplas filas                    */


processQueue *multQueue[5]; // multiplas filas de processo para o escalonador de
                           // multiplas filas
pthread_mutex_t multQueueMutex[5]; // mutex para proteger acessos às filas acima
unsigned long int quantum[5]; // quantum associado a cada fila das múltiplas
                              // filas


/******************************************************************************/
/*                 Funções comuns à mais de um escalonador                    */
/******************************************************************************/



/* Imprime na saida padrão de erro uma mensagem de erro. */
void error (char *message) {
    fprintf (stderr, "Error: %s\n", message);
}


/* Imprime na saida padrão de erro uma mensagem de erro e finaliza o programa
com status de saída igual a EXIT_FAILURE. */
void fatalError (char *message) {
    fprintf (stderr, "Error: %s\n", message);
    exit (EXIT_FAILURE);
}

/* Retorna o tempo decorrido desde o inicio da simulação em microsegundos. */
unsigned long int simElapsedTime () {
    struct timeval t;
    if (gettimeofday (&t, NULL) == -1)
        fatalError ("Couldn't get actual time");
    unsigned long int el = (t.tv_sec - simInitTime.tv_sec) * 1000000 +
                            (t.tv_usec - simInitTime.tv_usec);
    return el;
}


/* Lê o arquivo de trace fornecido e salva os processos em uma lista global. */
void readTraceFile (FILE *trace) {
    int ret;
    int i = 0, max = 100;
    processList = malloc (max * sizeof (process *));
    process *new;
    double t0, dt, deadline;

    do {
        new = malloc (sizeof (process));
        ret = fscanf (trace, "%lf %s %lf %lf", &t0, new->name, &dt, &deadline);
        if (ret != EOF) {
            if (ret != 4) fatalError ("Error reading trace file");
            else {
                new->t0 = (unsigned long int) (t0 * 1000000);
                new->rt = new->dt = (unsigned long int) (dt* 1000000);
                new->deadline = (unsigned long int) (deadline * 1000000);
                if (i >= max) {
                    max *= 2;
                    processList = realloc (processList, max *
                                           sizeof (process *));
                }
                processList[i++] = new;
            }
        }
        else free (new);
    } while (ret != EOF);
    quantProcess = i;
}




/******************************************************************************/
/*                              Funções do FCFS                               */
/******************************************************************************/


/* Esta função verifica se o tempo atual de simulação já é maior ou igual ao
tempo de chegada (t0) de algun(s) processo(s) da lista de processos, e, caso
seja, coloca o(s) processo(s) na fila de processos do escalonador, para o
escalonador FCFS. */
void *fcfsGate (void *a) {
    unsigned long int t;

    for (int j = 0; j < quantProcess; j++) {
        do {
            t = simElapsedTime ();
        } while (processList[j]->t0 > t);
        if (extraInfo) {
            fprintf (stderr, "Instante %fs: o processo \"%s\" chegou no sistema"
                     ".\n", ((double)t/1000000), processList[j]->name);
        }
        pthread_mutex_lock (&pQueueMutex);
        enqueue (pQueue, (*processList[j]));
        pthread_mutex_unlock (&pQueueMutex);
        free (processList[j]);
    }

    return NULL;
}

/* Esta função é a função que será executada por cada processo na simulação do
    escalonador FCFS. A thread que executa esta função termina quando o tempo de
    execução total do processo chega ao fim. */
void *fcfsProcessFunction (void *a) {
    unsigned long int t0 = simElapsedTime ();
    unsigned long int tf = t0 + exePr.dt;
    unsigned long int t;

    unsigned long x = 92321, y = 12329;
    if (extraInfo) {
        int s = sched_getcpu ();
        if (s == -1) error ("Couldn't get CPU number. Using -1 instead.");
        t = simElapsedTime ();
        fprintf (stderr, "Instante %fs: Uso de Cpu. Processo \"%s\" começou "
             "a usar a CPU %d.\n", (double) t / 1000000, exePr.name, s);
    }
    while (1) {
        t = simElapsedTime ();
        if (t >= tf) break;

        /* Operações arbitrárias para gastar CPU, simulando um processo real. */
        x = ((x % 9112) + (y % 192)) % 1883;
        y = ((x % 9112) + (y % 192)) % 1821;

    }

    return NULL;
}



/* Esta função executa a simulação do escalonador de procesos seguindo o
   método FCFS e escreve no arquivo output alguns resultados. */
void fcfsScheduler (FILE *output) {
    pthread_t exeTh;
    int i = 0;
    int execute = 0;
    unsigned long int t = 0;
    unsigned long int realt0, tf;

    while (i < quantProcess) {
        pthread_mutex_lock (&pQueueMutex);
        if (!isEmpty (pQueue)) {
            exePr = dequeue (pQueue);
            execute = 1;
        }
        pthread_mutex_unlock (&pQueueMutex);

        if (execute) {
            do {
                t = simElapsedTime ();
            } while (exePr.t0 > t);
            realt0 = t;
            pthread_create (&exeTh, NULL, fcfsProcessFunction, NULL);
            pthread_join (exeTh, NULL);
            tf = simElapsedTime ();
            i++;
            if (extraInfo)
                fprintf (stderr, "Instante %fs: Processo \"%s\" finalizou, "
                         "escrevendo a linha %d no arquivo de saída.\n",
                         (double) tf / 1000000, exePr.name, i);
             fprintf (output, "%d\n", tf <= exePr.deadline);

            execute = 0;
        }
    }
}


/******************************************************************************/
/*                           Funções do SRTN                                  */
/******************************************************************************/

/* Esta função é a função que será executada por cada processo na simulação do
    escalonador srtn. */
void *srtnProcessFunction (void *a) {
    unsigned long int t0 = simElapsedTime ();
    unsigned long int tf = t0 + exePr.rt;
    unsigned long int t;
    int exitType = 0;

    unsigned long x = 92321, y = 12329;
    if (extraInfo) {
        int s = sched_getcpu ();
        if (s == -1) error ("Couldn't get CPU number. Using -1 instead.");
        t = simElapsedTime ();
        fprintf (stderr, "Instante %fs: Uso de Cpu. Processo \"%s\" começou "
             "a usar a CPU %d.\n", (double) t / 1000000, exePr.name, s);
    }
    while (1) {
        t = simElapsedTime ();
        if (t >= tf) {
            pthread_mutex_lock (&processFinishedMutex);
                processFinished = 1;
            pthread_mutex_unlock (&processFinishedMutex);
            exitType = 0;
            break;
        }

        pthread_mutex_lock (&stopMutex);
        if (stop == 1) {
            exePr.rt = tf - t;
            pthread_mutex_unlock (&stopMutex);
            exitType = 1;
            break;
        }
        pthread_mutex_unlock (&stopMutex);

        /* Operações arbitrárias para gastar CPU, simulando um processo real. */
        x = ((x % 9112) + (y % 192)) % 1883;
        y = ((x % 9112) + (y % 192)) % 1821;

    }

    if (extraInfo && exitType == 1) {
        int s = sched_getcpu ();
        if (s == -1) error ("Couldn't get CPU number. Using -1 instead.");
        fprintf (stderr, "Instante %fs: Liberação de Cpu. Processo \"%s\" está "
                 "saindo da CPU %d.\n", (double) t / 1000000, exePr.name, s);
    }
    return NULL;
}

/* Esta função executa a simulação do escalonador de procesos seguindo o
   método SRTN e escreve no arquivo output alguns resultados. */
void srtnScheduler (FILE *output) {
    unsigned long int t;
    int isExe = 0;
    pthread_t exeTh;
    pthread_mutex_init (&processFinishedMutex, NULL);
    pthread_mutex_init (&stopMutex, NULL);
    int j = 0, i = 1;
    processFinished = 0;

    while (isExe || !isEmpty (pQueue) || j < quantProcess) {

        if (j < quantProcess) {
            do {
                t = simElapsedTime ();

                pthread_mutex_lock (&processFinishedMutex);
                if (processFinished) {
                    pthread_join (exeTh, NULL);
                    isExe = 0;
                    processFinished = 0;
                    if (extraInfo)
                        fprintf (stderr, "Instante %fs: Processo \"%s\""
                                 "finalizou, escrevendo a linha %d no arquivo"
                                 " de saída.\n", (double) t / 1000000,
                                 exePr.name, i);
                    fprintf (output, "%d\n", simElapsedTime() <= exePr.deadline);

                    i++;
                }
                pthread_mutex_unlock (&processFinishedMutex);

            } while (processList[j]->t0 > t);
            if (extraInfo) {
                fprintf (stderr, "Instante %fs: o processo \"%s\" chegou no"
                         "sistema.\n", ((double)t/1000000),
                         processList[j]->name);
            }
            if (isExe) {
                if (processList[j]->rt < exePr.rt) {

                    pthread_mutex_lock (&stopMutex);
                    stop = 1;
                    pthread_mutex_unlock (&stopMutex);
                    contextChanges++;

                    pthread_join (exeTh, NULL);
                    stop = 0;
                    orderedInsertion (pQueue, exePr);
                    exePr = *(processList[j]);
                    free (processList[j]);
                    pthread_create (&exeTh, NULL, srtnProcessFunction, NULL);
                }
                else {
                    orderedInsertion (pQueue, *(processList[j]));
                    free (processList[j]);
                }
            }
            else {
                isExe = 1;
                exePr = *(processList[j]);
                free (processList[j]);
                pthread_create (&exeTh, NULL, srtnProcessFunction, NULL);
            }
            j++;
        }
        else {
            if (isExe) {
                pthread_join (exeTh, NULL);
                t = simElapsedTime ();
                if (extraInfo)
                    fprintf (stderr, "Instante %fs: Processo \"%s\" finalizou, "
                             "escrevendo a linha %d no arquivo de saída.\n",
                             (double) t / 1000000, exePr.name, i);
                             fprintf (output, "%d\n", t <= exePr.deadline);
                i++;
            }
            if (!isEmpty (pQueue)) {
                exePr = dequeue (pQueue);
                pthread_create (&exeTh, NULL, srtnProcessFunction, NULL);
            }
            else isExe = 0;
        }
    }
}

/******************************************************************************/
/*                        Funções do mutiplas filas                           */
/******************************************************************************/


/* Esta função verifica se o tempo atual de simulação já é maior ou igual ao
tempo de chegada (t0) de algun(s) processo(s) da lista de processos, e, caso
seja, coloca o(s) processo(s) na fila de processos do escalonador, para o
escalonador multiplas filas. */
void *multQueueGate (void *a) {
    unsigned long int t;

    for (int j = 0; j < quantProcess; j++) {
        do {
            t = simElapsedTime ();
        } while (processList[j]->t0 > t);
        if (extraInfo) {
            fprintf (stderr, "Instante %fs: o processo \"%s\" chegou no sistema"
                     ".\n", ((double)t/1000000), processList[j]->name);
        }
        pthread_mutex_lock (&multQueueMutex[0]);
        enqueue (multQueue[0], (*processList[j]));
        pthread_mutex_unlock (&multQueueMutex[0]);

        free (processList[j]);
    }

    return NULL;
}

/* Esta função é a função que será executada por cada processo na simulação do
    escalonador multiplas filas. */
void *multQueueProcessFunction (void *a) {
    unsigned long int t0 = simElapsedTime ();
    unsigned long int t;
    int exitType = 0;
    int i = *((int *) a);

    unsigned long x = 92321, y = 12329;
    if (extraInfo) {
        int s = sched_getcpu ();
        if (s == -1) error ("Couldn't get CPU number. Using -1 instead.");
        t = simElapsedTime ();
        fprintf (stderr, "Instante %fs: Uso de Cpu. Processo \"%s\" começou "
             "a usar a CPU %d.\n", (double) t / 1000000, exePr.name, s);
    }

    while (1) {
        t = simElapsedTime ();
        if (t - t0 >= exePr.rt) {
            exePr.rt = 0;
            exitType = 0;
            break;
        }

        if (t - t0 >= quantum[i]) {
            exePr.rt = exePr.rt - (t - t0);
            exitType = 1;
            break;
        }
        /* Operações arbitrárias para gastar CPU, simulando um processo real. */
        x = ((x % 9112) + (y % 192)) % 1883;
        y = ((x % 9112) + (y % 192)) % 1821;
    }
    if (extraInfo && exitType == 1) {
        int s = sched_getcpu ();
        if (s == -1) error ("Couldn't get CPU number. Using -1 instead.");
        fprintf (stderr, "Instante %fs: Liberação de Cpu. Processo \"%s\" está "
                 "saindo da CPU %d.\n", (double) t / 1000000, exePr.name, s);
    }

    return NULL;
}


/* Esta função executa a simulação do escalonador de procesos seguindo o
   método multiplas filas e escreve no arquivo output alguns resultados. */
void multQueueScheduler (FILE *output) {
    int finishedProcesses = 0;
    int isEmp;
    unsigned long int t;
    pthread_t exeTh;

    while (finishedProcesses < quantProcess) {
        for (int i = 0; i < 5; i++) {
            pthread_mutex_lock (&multQueueMutex[i]);
            isEmp = isEmpty (multQueue[i]);
            pthread_mutex_unlock (&multQueueMutex[i]);
            if (!isEmp) {
                pthread_mutex_lock (&multQueueMutex[i]);
                exePr = dequeue (multQueue[i]);
                pthread_mutex_unlock (&multQueueMutex[i]);
                pthread_create (&exeTh, NULL, multQueueProcessFunction, &i);
                pthread_join (exeTh, NULL);

                if (exePr.rt > 0) {
                    contextChanges++;
                    if (i < 4) {
                        pthread_mutex_lock (&multQueueMutex[i + 1]);
                        enqueue (multQueue[i + 1], exePr);
                        pthread_mutex_unlock (&multQueueMutex[i + 1]);
                    }
                    else {
                        pthread_mutex_lock (&multQueueMutex[4]);
                        enqueue (multQueue[4], exePr);
                        pthread_mutex_unlock (&multQueueMutex[4]);
                    }
                }
                else {
                    t = simElapsedTime ();
                    finishedProcesses++;
                    if (extraInfo)
                        fprintf (stderr, "Instante %fs: Processo \"%s\" "
                                 "finalizou, escrevendo a linha %d no arquivo "
                                 "de saída.\n", (double) t / 1000000,
                                 exePr.name, finishedProcesses);
                    fprintf (output, "%d\n", t <= exePr.deadline);
                }
            }
        }
    }
}




/******************************************************************************/
/*                                  Main                                      */
/******************************************************************************/


int main (int argc, char **argv) {

    extraInfo = 0;
    if (argc < 4)
        fatalError ("Incorrect usage. Use: ep1 stepperType traceFileName"
                    "outputFileName [d]");
    else if (argc >= 5 && strcmp (argv[4], "d") == 0) extraInfo = 1;

    int schedulerType;
    FILE *trace = fopen (argv[2], "r");
    FILE *output = fopen (argv[3], "w");
    if (output == NULL) fatalError ("Couldn't open output file");
    if (trace == NULL) fatalError ("Couldn't open trace file");
    if (sscanf (argv[1], "%d", &schedulerType) == EOF)
        fatalError ("Could't get steppet type");
    pthread_t gateThread;

    contextChanges = 0;

    readTraceFile (trace);
    fclose (trace);
    fprintf (output, "%d\n%d\n", schedulerType, quantProcess);

    /*Inicio do processo de simulação*/

    if (gettimeofday (&simInitTime, NULL) == -1) // salva o tempo inicial da
        fatalError ("Couldn't get actual time");    // simulação em var. global


    switch (schedulerType) {
        case 1:
            pQueue = createQueue ();
            pthread_mutex_init (&pQueueMutex, NULL);
            if (gettimeofday (&simInitTime, NULL) == -1)
                fatalError ("Couldn't get actual time");
            pthread_create (&gateThread, NULL, fcfsGate, NULL);
            fcfsScheduler (output);
            pthread_join (gateThread, NULL);
            destroyQueue (pQueue);
            break;
        case 2:
            pQueue = createQueue ();
            if (gettimeofday (&simInitTime, NULL) == -1)
                fatalError ("Couldn't get actual time");
            srtnScheduler (output);
            destroyQueue (pQueue);
            break;
        case 3:
            for (int i = 0; i < 5; i++) {
                multQueue[i] = createQueue ();
                pthread_mutex_init (&multQueueMutex[i], NULL);
            }
            quantum[0] = 500000;
            quantum[1] = 1000000;
            quantum[2] = 1500000;
            quantum[3] = 2000000;
            quantum[4] = 2500000;
            if (gettimeofday (&simInitTime, NULL) == -1)
            fatalError ("Couldn't get actual time");
            pthread_create (&gateThread, NULL, multQueueGate, NULL);
            multQueueScheduler (output);
            pthread_join (gateThread, NULL);
            for (int i = 0; i < 5; i++) destroyQueue (multQueue[i]);
            break;
        default: fatalError ("Invalid Scheduler type");
    }

    fprintf (output, "%d", contextChanges);
    if (extraInfo)
        fprintf (stderr, "Mudanças de contexto: %d\n", contextChanges);


    free (processList);
    fclose (output);
    exit (EXIT_SUCCESS);
}
