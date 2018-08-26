#include <stdio.h> //sscanf, fprintf, printf
#include <stdlib.h> //malloc, free
#include <pthread.h> //pthread_create, pthread_join, pthread_exit,
                     //pthread_mutex_init, pthread_mutex_destroy,
                     //pthread_mutex_lock, pthread_mutex_unlock
#include <semaphore.h> //sem_init, sem_post, sem_wait, sem_destroy
#include <string.h> //strcmp
#include <math.h> //pow, ceil, floor
#include <unistd.h> //usleep
#include "randomCyclers.h"
#include "rankCyclers.h"
#include "erro.h"

void printDebug ();
void cycleBreaking ();
void whoFinishedCompetition ();
void cyclerOutOfCompetition (int thNum);
void newSpeed ();
void printInLog ();
void simulationCoordination ();
void threadsFunnel (int thNum);
void barrier (int thNum, int useDone);
void updatePosition (int thNum, int curPos, int nextPos);
void *cycler (void *id);
void initialization (int argc, char **argv);
void finalization ();
void printFinalResults ();
int firstCycler ();



typedef struct cyclerInfo {
    int broked; /* Vale 1 se ciclista quebrou, 0 caso contrário. */
    int isOut; /* Vale 0 se o ciclista está na competição, 1 caso contrário.*/
    int initPos; /* Posição inicial do ciclista na pista. (em metros)*/
    int curPos; /* Posição atual do ciclista na pista (em metros). */
    int curSide; /* Lado atual do ciclísta na pista.  (dentro ou fora) */
    int completeLaps; /* Voltas inteiras já completadas pelo ciclista. */
    double speed; /* Velocidade do ciclista em m/60ms. */
    int endLine; /* Linha de chegada do ciclista. */
    double ds; /* Distancia total percorrida pelo ciclísta, em metros. */
    double lastUpdateTime; /* Tempo da última atualização da posição do
                              ciclista. */
}cyclerInfo_t;


/* Vetor que contêm informações de todos os ciclistas. */
static cyclerInfo_t *cyclers;

/* Mutex para acessar as posições da pista. */
static pthread_mutex_t *pistaMutex;

/* pista é o vetor que representa a pista e d é o tamanho total da pista*/
static int **pista;
static int d;

/* n é a quantidade inicial de ciclistas por equipe e nt a quantidade inicial
 * total de ciclistas */
static int n, nt;

/* mode representa o modo de simulação: 1 para velocidades uniformes e 0 para
 * velocidade variadas como descrito no enunciado do ep. debug é uma flag
 * que, caso tenha valor 1, habilita a impressão de mesagens de debug.*/
static int mode, debug;

/* barrierMutex é uma matrix de semáforos usados na barreira de sincronização
 * das threads ciclístas. Está matrix contem um semáforo para cada thread
 * ciclísta em cada estágio da barreira. Note que, apesar dos ciclistas serem
 * indexados a partide de 1, a matrix barrierMutex é indexada a partir de 0.
 * Por isso, e pelo fato de que a quantidade de ciclistas pode diminuir ao
 * longo da competição, é necessário uma tabela que associe cada thread
 * ciclista, em um dado momento do programa, à um mutex. Essa tabela é o
 * mtt (mutex translation table), que guarda na pocição i, o identificador do
 * mutex associado à thread i naquele momento, se i é uma thread ativa.
 * (i > 0 e i <= nt)*/
static sem_t **barrierMutex;
static int *mtt;

/* barrierStages é a quantidade de estágios da barreira atualmente, que
 * varia conforme a quantidade de threads ciclístas. initialBarrierStages é a
 * quantidadede estágios da barreira no início. */
static int barrierStages;
static int initialBarrierStages;

 /* done é um contador que indica quantas threads já finalizaram suas passagens
  * pela barreira.. De tempos em tempos ela é zerada.
  * doneMutex é um mutex para proteger a variável done. */
static int done;
static pthread_mutex_t doneMutex;

 /* Este mutex é utilizado na função threadsFunnel para designar à primeira
  * thread que conseguir executá-lo, tarefas especiais que devem ser realizadas
  * por uma única thread por iteração. Por exemplo: atualizar o tempo total da
  * simulação e checar se um ciclista "quebrou". Tambêm é utilizado para
  * permitir que apenas uma thread execute as operações da threadsFunnel por
  * vez. */
static pthread_mutex_t funnelMutex;

 /* O tempo todal de simulação, em segundos. */
static double tempoSimu = 0;

 /* Guarda o identificador da thread que, na próxima iteração, devera tentar
  * "segurar" os mutex necessários de forma inversa ao convencional às demais
  * threads. Isto serve para resolver o "problema dos filósofos famintos" que
  * pode aparecer. */
static int different = 1;

 /* doneFunnel guarda a quantidade de threads que já passaram chegaram até a
  * parte final da função threadsFunnel. doneFunnelCond é uma variável de
  * condição utilizada para indicar quando todas as threads já chegaram nesta
  * parte final. doneFunnelMutex é um mutex que protege estas duas variáveis
  * acima.
 */
static int doneFunnel;
static pthread_cond_t doneFunnelCond;
static pthread_mutex_t doneFunnelMutex;


 /* file de saída do relatório da simulação. */
static FILE *output;






 /* Imprime, em formato de tabela, todas as posições da pista, com os
  * respectivos ciclistas que estão nela, ou a string "Nenhum" caso não haja
  * nenhum ciclista naquela posição. */
void printDebug () {
    int initialVazio = -1;
    int i;
    printf ("   DEBUG >> disposição da pista (%fs):\n   ", tempoSimu);
    printf (" Pista:  Ciclistas:\n");
    for (i = 0; i < d; i++) {
        if (pista[i][0] != 0) {
            if (initialVazio != -1) {
                printf ("%5d - %d    Vazio\n", initialVazio, (i - 1) % d);
                initialVazio = -1;
            }
            if (pista[i][1] != 0)
                printf ("%8d       %d e %d\n", i, pista[i][0], pista[i][1]);
            else
                printf ("%8d       %d\n", i, pista[i][0]);
        }
        else if (pista[i][1] != 0) {
            if (initialVazio != -1) {
                printf ("%5d - %d    Vazio\n", initialVazio, (i - 1) % d);
                initialVazio = -1;
            }
            printf ("%8d       %d\n", i, pista[i][1]);
        }
        else if (initialVazio == -1) {
            initialVazio = i;
        }
    }
    if (initialVazio != -1)
        printf ("%5d - %d    Vazio\n", initialVazio, d - 1);
}

/* Esta função, com 10% de probabilidade,  escolhe um ciclista aleatório para
 * quebrar e com 90% de chance, escolhe que ninguem quebrou. Caso seja escolhido
 * que alguem quebrou, altera os identificadores broked e isOut na struct do
 * respectivo ciclista no vetor cyclers e o remove do módulo randomCyclers.
 * (Caso hajam menos de 4 ciclistas em uma equipe, a probabilidade de escolher
 * um ciclísta daquela equipe para quebrar passa a ser 0%).  */
void cycleBreaking () {
    static int whoCanBreak;

    if (getNumberCyclers (1) < 4) {
        if (getNumberCyclers(2) < 4) whoCanBreak = -1;
        else whoCanBreak = 2;
    }
    else if (getNumberCyclers (2) < 4) whoCanBreak = 1;
    else whoCanBreak = 0;
    if (whoCanBreak > -1 && (double) random () < (double) RAND_MAX / 10) {
        int c = getRandomCycler (whoCanBreak);
        cyclers[c].broked = 1;
        cyclers[c].isOut = 1;
    }
}

 /* Esta função verifica quem, na iteração atual, está fora da competição
  * por já ter completado a prova, faz os procedimentos necessários nas
  * variaveis globais para indicar a saída do(s) ciclista(s) e retira o ciclista
  * do modulo randomCyclers. */
void whoFinishedCompetition () {
    for (int i = 1; i < nt + 1; i++) {
        if (cyclers[i].isOut == 0 && cyclers[i].completeLaps == 16) {
            removeCycler (i);
            cyclers[i].isOut = 1;
        }
    }
}


 /* Retira o cilista da pista e ajusta as variáveis globais relativas a barreira
  * para que esta funcione com este ciclísta a menos. */
void cyclerOutOfCompetition (int thNum) {
    pista[cyclers[thNum].curPos][cyclers[thNum].curSide] = 0;
    //barrierStages = (int) ceil (log2 ((double) getNumberCyclers (0)));
    //for (int i = thNum + 1; i < nt + 1; i++) {
    //    mtt[i] = mtt[i] - 1;
    //}
}

 /* Decide e estabelece a velocidade de cada ciclista ainda na competição, da
  * seguinte forma, para o modo de simulação onde a velocidade é variada. */
void newSpeed () {
    static int slow1 = 0, slow2 = 0;
    double *rank1 = queue_i_rank (1);
    double *rank2 = queue_i_rank (2);
    int th;

    for (int i = 1; i < n + 1; i++) {
        th = (int) rank1[i];
        if (cyclers[th].isOut == 1) continue;
        if (slow1 != 0 && rankTeam (th) > rankTeam (slow1)) {
            cyclers[th].speed = 0.5;
            continue;
        }
        if (random () < RAND_MAX / 2) {
            if (th == slow1) slow1 = 0;
            else slow1 = th;
            cyclers[th].speed = 0.5;
            continue;
        }
        cyclers[th].speed = 1.0;
    }

    for (int i = 1; i < n + 1; i++) {
        th = (int) rank2[i];
        if (cyclers[th].isOut == 1) continue;
        if (slow2 != 0 && rankTeam (th) > rankTeam (slow2)) {
            cyclers[th].speed = 0.5;
            continue;
        }
        if (random () < RAND_MAX / 2) {
            if (th == slow2) slow2 = 0;
            else slow2 = th;
            cyclers[th].speed = 0.5;
            continue;
        }
        cyclers[th].speed = 1.0;
    }


        int *cycs = avaliableCyclers (0);
        for (int i = 1; i < cycs[0]; i++) printf ("Speed %d = %f\n", cycs[i], cyclers[cycs[i]].speed);

}


 /* Caso um 3º ciclísta de uma equipe tenha completado uma nova volta desde a,
  * última vez que a função foi chamada, esta função imprime no relatório de
  * saída, o numero da volta que ele completou, o tempo atual da simulação e os
  * identificadores dos 3 primeiros ciclistas da equipe. Caso ambas os terceiros
  * ciclistas das duas equipes tenham completado uma nova volta, são impressas
  * as informações de ambas. */
void printInLog () {
    static int lastLapUsed1 = 0, lastLapUsed2 = 0;
    int k = 0;
    int t1[3], t2[3];
    for (int i = 1; i < n + 1 && k < 3; i++) {
        t1[k] = rankCycler(i, 1);
        if (cyclers[t1[k]].broked == 0) k++;
    }
    k = 0;
    for (int i = 1; i < n + 1 && k < 3; i++) {
        t2[k] = rankCycler(i, 2);
        if (cyclers[t2[k]].broked == 0) k++;
    }

    if (cyclers[t1[2]].completeLaps > lastLapUsed1) {
        lastLapUsed1 = cyclers[t1[2]].completeLaps;
        fprintf (output, "[3º colocado da equipe 1 completou uma nova volta]:\n"
        " Volta %d, tempo %fs, primeiros ciclistas: %d, %d e %d\n\n",
        lastLapUsed1, tempoSimu, t1[0], t1[1], t1[2]);
    }
    if (cyclers[t2[2]].completeLaps > lastLapUsed2) {
        lastLapUsed2 = cyclers[t2[2]].completeLaps;
        fprintf (output, "[3º colocado da equipe 2 completou uma nova volta]:\n"
        " Volta %d, tempo %fs, primeiros ciclistas: %d, %d e %d\n\n",
        lastLapUsed2, tempoSimu, t2[0], t2[1], t2[2]);
    }
}

/* Esta função deve ser chamada por uma única thread a cada iteração e é
* responsável pela realização de operações e checagens de coordenação da
* simulação como um todo. Por exemplo, ela é responsável pela verificação de
* ciclistas quebrados e ciclistas que já completaram a prova, em cada iteração.
*/
static int lastLapUsedForSpeedChange = 0;
static int lastLapUsedForBreak = 0;
void simulationCoordination () {


    tempoSimu += 0.00006;
    if (debug == 1) printDebug ();
    printInLog ();

    whoFinishedCompetition ();

    if (cyclers[firstCycler (cyclers)].completeLaps % 4 == 0 &&
       cyclers[firstCycler (cyclers)].completeLaps != lastLapUsedForBreak) {
       lastLapUsedForBreak = cyclers[firstCycler (cyclers)].completeLaps;
       cycleBreaking ();
    }


    if (mode == 0 && cyclers[firstCycler (cyclers)].completeLaps >
    lastLapUsedForSpeedChange) {

        newSpeed ();
        lastLapUsedForSpeedChange = cyclers[firstCycler (cyclers)].completeLaps;
    }
}

/* Esta função deve ser chamada por todas as threads ciclistas ativas ao fim
 * de cada iteração. Ela sincroniza todas as threads, "escolhe" uma para
 * realizar algumas funções de coordenação relativas à simulação como um todo
 * enquanto as outras aguardam e depois permite que uma a uma cada thread
 * execute algumas operações excenciais à simulação relativas à si própria
 * (como verificar se o respectivo ciclista da thread quebrou, já finalizou a
 * prova e etc.). Por fim, a função sincroniza todas as thread novamente e
 * retorna. (Como parâmetro, a função deve receber o identificador da thread
 * que a chamou). */
void threadsFunnel (int thNum) {
    static int arrived = 0;
    static int first = 0;

    //printf ("(%d) Tentando passar pela barreira\n", thNum);
    //barrier (thNum, 1);
    //printf ("(%d) consegui\n", thNum);

    pthread_mutex_lock (&doneMutex);
    done++;
    pthread_mutex_unlock (&doneMutex);

    pthread_mutex_lock (&funnelMutex);
    if (first == 0) {
        first = 1;
        while (done < getNumberCyclers (0)) {
            usleep (10000);
            //printf ("%d e %d\n", done, getNumberCyclers (0));
        }
        done = 0;
        simulationCoordination ();

        if (cyclers[thNum].isOut == 1) {

            different = -1;
            if (cyclers[thNum].broked == 1) {
                int x = rankCycler (thNum, (thNum > n) + 1), j = 0;
                double *rank = queue_i_rank ((thNum > n) + 1);
                for (int i = 1; i < x; i++)
                    if (cyclers[(int)rank[i]].completeLaps ==
                        cyclers[thNum].completeLaps) j++;
                printf ("Ciclista %d quebrou na volta %d e ele era o %dº da sua"
                        " equipe na volta\n", thNum,
                        cyclers[thNum].completeLaps, j + 1);
            }
            else updateCycler (thNum, ceil (cyclers[thNum].ds),
                                cyclers[thNum].initPos);
            cyclerOutOfCompetition (thNum);
            pthread_mutex_unlock (&funnelMutex);
            pthread_exit (NULL);
        }
        else {

            updateCycler (thNum, cyclers[thNum].ds, cyclers[thNum].initPos);

            arrived++;
            different = thNum;
        }
    }
    else {
        if (arrived == getNumberCyclers (0)) {
            arrived = 0;
            first = 0;
        }
        if (cyclers[thNum].isOut == 1) {
            if (cyclers[thNum].broked == 1) {
                int x = rankCycler (thNum, (thNum > n) + 1), j = 0;
                double *rank = queue_i_rank ((thNum > n) + 1);
                for (int i = 1; i < x; i++)
                    if (cyclers[(int)rank[i]].completeLaps ==
                        cyclers[thNum].completeLaps) j++;
                printf ("Ciclista %d quebrou na volta %d e ele era o %dº da sua"
                        " equipe na volta\n", thNum,
                        cyclers[thNum].completeLaps, j + 1);
            }
            else updateCycler (thNum, ceil (cyclers[thNum].ds),
                               cyclers[thNum].initPos);
            cyclerOutOfCompetition (thNum);
            pthread_mutex_unlock (&funnelMutex);
            pthread_exit (NULL);
        }

        arrived++;

        if (arrived == getNumberCyclers (0)) {
            arrived = 0;
            first = 0;
        }

        updateCycler (thNum, cyclers[thNum].ds, cyclers[thNum].initPos);

        if (different == -1) different = thNum;
    }
    pthread_mutex_unlock (&funnelMutex);

    pthread_mutex_lock (&doneFunnelMutex);
    doneFunnel++;
    //printf ("%d e %d\n", doneFunnel, getNumberCyclers (0));
    if (doneFunnel == getNumberCyclers (0)) {
        doneFunnel = 0;
        pthread_cond_broadcast (&doneFunnelCond);
    }
    else pthread_cond_wait (&doneFunnelCond, &doneFunnelMutex);
    pthread_mutex_unlock (&doneFunnelMutex);
}


/* Função que implementa a barreira de sincronização de threads ciclistas,
 * que sincroniza-as no ponto em que for chamada. thNum é o identificador da
 * thread que a esta chamando. useDone, quando valer 1, fará com que a função
 * incremente a variável global done, para cada thread que finzalizar sua
 * passagem pela barreira. */
void barrier (int thNum, int useDone) {
    int myAsMu = mtt[thNum];
    int di = 1;
    for (int i = 0; i < barrierStages; i++) {
        int pairMu = (myAsMu + di) % getNumberCyclers (0);
        //printf ("(%d): estágio %d, %d - %d\n", thNum, i, myAsMu, pairMu);
        sem_post (&barrierMutex[i][myAsMu]);
        sem_wait (&barrierMutex[i][pairMu]);
        di = di * 2;
    }
    if (useDone == 1) {
        pthread_mutex_lock (&doneMutex);
        done++;
        pthread_mutex_unlock (&doneMutex);
    }
}


 /* Tenta atualizar a posição do ciclista thNum na pista, que está na posição
  * curPos, para a próxima possição que é a nextPos. Caso não seja possível (
  * devido à presença de outro ciclísta à frente), mantêm o ciclista em
  * curPos. Tambêm atualiza o curPos, curSide e ds da struct do ciclista em
  * cyclers. Caso, tenha havido movimentação e nesta movimentação o cliclista
  * tenha completado mais uma volta, atualiza a quantidade de voltas completas
  * na struct do ciclista no vetor global cyclers. */
void updatePosition (int thNum, int curPos, int nextPos) {
    double speed = cyclers[thNum].speed;

    if (thNum == different) {
        pthread_mutex_lock (&pistaMutex[(curPos + 1) % d]);
        pthread_mutex_lock (&pistaMutex[curPos]);
    }
    else {
        pthread_mutex_lock (&pistaMutex[curPos]);
        pthread_mutex_lock (&pistaMutex[(curPos + 1) % d]);
    }
    if (pista[nextPos][0] == thNum) cyclers[thNum].ds += speed;
    else if (pista[nextPos][1] == thNum) cyclers[thNum].ds += speed;
    curPos = (int) (cyclers[thNum].ds + cyclers[thNum].initPos) % d;
    nextPos = (int) (cyclers[thNum].ds + cyclers[thNum].initPos +
    cyclers[thNum].speed) % d;
    if (pista[nextPos][0] == 0) {

        if (curPos != nextPos) cyclers[thNum].lastUpdateTime = tempoSimu;
        pista[curPos][cyclers[thNum].curSide] = 0;
        pista[nextPos][0] = thNum;
        cyclers[thNum].curPos = nextPos;
        cyclers[thNum].curSide = 0;
        cyclers[thNum].ds += speed;
    }
    else if (pista[nextPos][1] == 0) {

        if (curPos != nextPos) cyclers[thNum].lastUpdateTime = tempoSimu;
        pista[curPos][cyclers[thNum].curSide] = 0;
        pista[nextPos][1] = thNum;
        cyclers[thNum].curPos = nextPos;
        cyclers[thNum].curSide = 1;
        cyclers[thNum].ds += speed;
    }

    if (thNum == different) {
        pthread_mutex_unlock (&pistaMutex[(curPos + 1) % d]);
        pthread_mutex_unlock (&pistaMutex[curPos]);
    }
    else {
        pthread_mutex_unlock (&pistaMutex[curPos]);
        pthread_mutex_unlock (&pistaMutex[(curPos + 1) % d]);
    }
    if (cyclers[thNum].curPos > cyclers[thNum].endLine) {
        cyclers[thNum].completeLaps = (cyclers[thNum].ds -
        (cyclers[thNum].endLine - cyclers[thNum].initPos)) / d;
    }

}

/* Função a ser executada por uma thread ciclista. Recebe como parametro, um
 * um endereço onde se encontra o inteiro identificador de um ciclista e executa
 * a simulação do movimento do respectivo ciclista na pista. */
void *cycler (void *id) {

    int thNum = *((int *) id);
    int curPos, nextPos;

    while (1) {
        curPos = (int) (cyclers[thNum].ds + cyclers[thNum].initPos) % d;
        nextPos = (int) (cyclers[thNum].ds + cyclers[thNum].initPos +
        cyclers[thNum].speed) % d;
        printf ("thNum=%d, curPos=%d, nextPos=%d, speed=%f, ds=%f\n", thNum,curPos, nextPos, cyclers[thNum].speed,cyclers[thNum].ds);
        updatePosition (thNum, curPos, nextPos);
        threadsFunnel (thNum);
    }
    return NULL;
}

/* Essa função recebe os argumentos passados para o programa no vetor argv, a
 * quantidade de argumentos em argc e faz toda a preparação e inicialização
 * necessária para o início da simulação. */
void initialization (int argc, char **argv) {

    if (argc < 4) fatalError ("Insuficient arguments.");
    if (argc == 5 && strcmp (argv[4], "-d") == 0) debug = 1;
    else debug = 0;

    if (sscanf (argv[1], "%d", &d) <= 0) fatalError("Invalid arguments.");
    if (sscanf (argv[2], "%d", &n) <= 0) fatalError("Invalid arguments.");
    if (argv[3][0] == 'v') mode = 0;
    else if (argv[3][0] == 'u') mode = 1;
    else fatalError ("Invalid arguments.");
    nt = n * 2;

    mtt = malloc ((nt + 1) * sizeof (int));
    for (int i = 1; i < nt + 1; i++) mtt[i] = i - 1;
    barrierStages = (int) ceil (log2 ((double) nt));
    initialBarrierStages = barrierStages;
    barrierMutex = malloc (barrierStages * sizeof (sem_t *));
    for (int i = 0; i < barrierStages; i++) {
        barrierMutex[i] = malloc (nt * sizeof (sem_t));
        for (int j = 0; j < nt; j++)
            if (sem_init (&barrierMutex[i][j], 0, 0) == -1)
                fatalError ("Error initializating semaphores.");
    }

    pista = malloc (d * sizeof (int *));
    pistaMutex = malloc (d * sizeof (pthread_mutex_t));
    for (int i = 0; i < d; i++) {
        pista[i] = malloc (2 * sizeof (int));
        pthread_mutex_init (&pistaMutex[i], NULL);
    }

    pthread_mutex_init (&funnelMutex, NULL);
    pthread_mutex_init (&doneMutex, NULL);
    done = 0;

    doneFunnel = 0;
    pthread_mutex_init (&doneFunnelMutex, NULL);
    pthread_cond_init (&doneFunnelCond, NULL);

    if ((output = fopen ("Relatório_Simulação.txt", "w")) == NULL)
    fatalError ("Couldn't open output file.");

    cyclers = malloc ((nt + 1) * sizeof (cyclerInfo_t));
    different = 1;

    initRandomCyclers (n);
    initRankCyclers (n);
    int c1, c2;

    for (int i = 0; i < n; i++) {
        c1 = getRandomCycler (1);
        c2 = getRandomCycler (2);

        pista[i][0] = c1;
        pista[i][1] = 0;
        cyclers[c1].broked = 0;
        setCycler (c1, (double) n - i);
        cyclers[c1].ds = 0.0;
        cyclers[c1].completeLaps = 0;
        cyclers[c1].lastUpdateTime = 0.0;
        cyclers[c1].initPos = i;
        cyclers[c1].curPos = i;
        cyclers[c1].curSide = 0;
        cyclers[c1].endLine = n - 1;
        cyclers[c1].isOut = 0;
        if (mode == 1) cyclers[c1].speed = 1.0;
        else cyclers[c1].speed = 0.5;

        pista[i + d/2][0] = c2;
        pista[i + d/2][1] = 0;
        cyclers[c2].broked = 0;
        setCycler (c2, (double) n - i);
        cyclers[c2].ds = 0.0;
        cyclers[c2].completeLaps = 0;
        cyclers[c2].lastUpdateTime = 0.0;
        cyclers[c2].initPos = i + d/2;
        cyclers[c2].curPos = i + d/2;
        cyclers[c2].curSide = 0;
        cyclers[c2].endLine = (d / 2) + n - 1;
        cyclers[c2].isOut = 0;
        if (mode == 1) cyclers[c2].speed = 1.0;
        else cyclers[c2].speed = 0.5;
    }

    resetRandomCyclers (n);


    for (int i = n; i < d/2; i++) {
        pista[i][0] = 0;
        pista[i][1] = 0;
    }

    for (int i = d/2 + n; i < d; i++) {
        pista[i][0] = 0;
        pista[i][1] = 0;
    }
}

int firstCycler () {
    int c, c2;
    for (int i = 1; i < n + 1; i++) {
        c = rankCycler (i, 1);
        c2 = rankCycler (i, 2);
        if (cyclers[c].broked == 0 && cyclers[c2].broked == 0) break;
    }
    if (cyclers[c].ds > cyclers[c2].ds) return c;
    return c2;
}

/* Finaliza a simulação, desalocando os espaços de memória alocados na
 * simulação. */
void finalization () {
    for (int i = 0; i < initialBarrierStages; i++) {
        for (int j = 0; j < nt; j++)
            sem_destroy (&barrierMutex[i][j]);
        free (barrierMutex[i]);
    }
    free (barrierMutex);
    free (mtt);
    pthread_mutex_destroy (&funnelMutex);
    for (int i = 0; i < d; i++) {
        free (pista[i]);
        pthread_mutex_destroy (&pistaMutex[i]);
    }
    free (pista);
    free (pistaMutex);
    free (cyclers);
    destroyRandomCyclers ();
    destroyRankCyclers ();
    fclose (output);
}

 /* Imprime os resultados finais da simulação. */
void printFinalResults () {
    int k = 0, j = n - 1;
    int *t1, *t2;
    t1 = malloc (n * sizeof (int));
    t2 = malloc (n * sizeof (int));

    for (int i = 0; i < n; i++) {
        t1[k] = rankCycler(i + 1, 1);
        if (cyclers[t1[k]].broked == 0) k++;
        else {
            t1[j] = t1[k];
            j--;
        }
    }
    k = 0;
    j = n - 1;
    for (int i = 0; i < n; i++) {
        t2[k] = rankCycler(i + 1, 2);
        if (cyclers[t2[k]].broked == 0) k++;
        else {
            t2[j] = t2[k];
            j--;
        }
    }
    if (cyclers[t1[2]].lastUpdateTime < cyclers[t2[2]].lastUpdateTime)
        fprintf (output, "1º lugar: equipe 1. 2º lugar: equipe 2.\n");
    else if (cyclers[t1[2]].lastUpdateTime > cyclers[t2[2]].lastUpdateTime)
        fprintf (output, "1º lugar: equipe 2. 2º lugar: equipe 1.\n");
    else
        fprintf (output, "Ocorreu empate.\n");

    fprintf (output, "Ranking final da equipe 1\n(com os tempos de chegada):"
            "\n");
    int i;
    for (i = 0; i < n; i++) {
        if (cyclers[t1[i]].broked == 1) break;
        if ((i % 5 == 0) && (i != 0)) printf ("\n");
        else fprintf (output, "%d (%f)   ", t1[i],
             cyclers[t1[i]].lastUpdateTime);
    }
    if (i < n) {
        fprintf (output, "\nCiclistas que quebraram da equipe 1:\n");
        for (; i < n; i++)
            fprintf (output, "%d, na volta %d\n", t1[i],
            cyclers[t1[i]].completeLaps);
    }
    else fprintf (output, "\nNenhum ciclista da equipe 1 quebrou.\n");

    fprintf (output, "\nRanking final da equipe 2\n(com os tempos de chegada):"
            "\n");
    for (i = 0; i < n; i++) {
        if ((i % 5 == 0) && (i != 0)) printf ("\n");
        if (cyclers[t2[i]].broked == 1) break;
        else fprintf (output, "%d (%f)   ", t2[i],
             cyclers[t2[i]].lastUpdateTime);
    }
    if (i < n) {
        fprintf (output, "\nCiclistas que quebraram da equipe 2:\n");
        for (; i < n; i++)
            fprintf (output, "%d, na volta %d\n", t2[i],
            cyclers[t2[i]].completeLaps);
    }
    else fprintf (output, "\nNenhum ciclista da equipe 2 quebrou.\n");

    free (t1);
    free (t2);
}


int main (int argc, char **argv) {

    initialization (argc, argv);

    int *id = malloc (nt * sizeof (int));
    pthread_t *cyclerThreads;
    cyclerThreads = malloc (nt * sizeof (pthread_t));
    for (int i = 0; i < nt; i++) {
        id[i] = i + 1;
        pthread_create (&cyclerThreads[i], NULL, cycler, (void *) &id[i]);
    }

    for (int i = 0; i < nt; i++) pthread_join (cyclerThreads[i], NULL);
    free (cyclerThreads);
    free (id);

    printFinalResults ();

    finalization ();

    return 0;
}
