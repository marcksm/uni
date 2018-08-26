/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/


#include <stdio.h> //sscanf, fprintf, printf
#include <stdlib.h> //malloc, free
#include <pthread.h> //pthread_create, pthread_join, pthread_exit,
                     //pthread_mutex_init, pthread_mutex_destroy,
                     //pthread_mutex_lock, pthread_mutex_unlock,
                     //pthread_cond_init, pthread_cond_destroy,
                     //pthread_cond_wait, pthread_cond_broadcast
#include <string.h> //strcmp
#include <math.h> //ceil
#include <unistd.h>
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

/* pista é a matriz que representa a pista. A matriz tem linhas de 0 à d - 1,
 * que representam as posições da pista, e 2 colunas, que representam o lado de
 * dentro e o lado de fora da pista.
 */
static int **pista;
static int d;

/* n é a quantidade inicial de ciclistas por equipe e nt a quantidade inicial
 * total de ciclistas */
static int n, nt;

/* mode representa o modo de simulação: 1 para velocidades uniformes e 0 para
 * velocidade variadas como descrito no enunciado do ep. debug é uma flag
 * que, caso tenha valor 1, habilita a impressão de mesagens de debug.*/
static int mode, debug;

 /* Este mutex é utilizado na função threadsFunnel para designar à primeira
  * thread que conseguir executá-lo, tarefas especiais que devem ser realizadas
  * por uma única thread por iteração. Por exemplo: atualizar o tempo total da
  * simulação e checar se um ciclista "quebrou". Tambêm é utilizado para
  * permitir que apenas uma thread execute as operações da threadsFunnel por
  * vez. */
static pthread_mutex_t funnelMutex;

 /* O tempo total de simulação, em segundos. (Não é o tempo real de execução do
  * programa, e sim o tempo na simulação). */
static double tempoSimu = 0;

 /* O programa possui 2 barreiras de sincronização de threads: uma no início e
  * uma no final da função threadsFunnel. A variável arrived guarda quantas
  * threads já chegaram na barreira. barrierCond é uma variável de condição
  * utilizada para indicar quando todas as threads já chegaram na barreira e,
  * portanto, podem seguir adiante. barrierMutex é um mutex que protege estas
  * duas variáveis acima.
 */
static int arrived;
static pthread_cond_t barrierCond;
static pthread_mutex_t barrierMutex;





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
                if (initialVazio == i)
                    fprintf (stderr, "%8d       Vazio\n", initialVazio);
                else
                    fprintf (stderr, "%5d - %d    Vazio\n",  initialVazio,
                             (i - 1) % d);
                initialVazio = -1;
            }
            if (pista[i][1] != 0)
                fprintf (stderr, "%8d       %d e %d\n", i, pista[i][0],
                        pista[i][1]);
            else
                fprintf (stderr, "%8d       %d\n", i, pista[i][0]);
        }
        else if (pista[i][1] != 0) {
            if (initialVazio != -1) {
                fprintf (stderr, "%5d - %d    Vazio\n", initialVazio,
                         (i - 1) % d);
                initialVazio = -1;
            }
            fprintf (stderr, "%8d       %d\n", i, pista[i][1]);
        }
        else if (initialVazio == -1) {
            initialVazio = i;
        }
    }
    if (initialVazio != -1)
        fprintf (stderr, "%5d - %d    Vazio\n", initialVazio, d - 1);
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
        cyclerOutOfCompetition (c);
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
            cyclerOutOfCompetition (i);
            cyclers[i].isOut = 1;
        }
    }
}


 /* Retira o cilista da pista. */
void cyclerOutOfCompetition (int thNum) {
    pista[cyclers[thNum].curPos][cyclers[thNum].curSide] = 0;
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
        if (cyclers[th].isOut == 1) {
            if (slow1 == th) slow1 = 0;
            continue;
        }
        if (slow1 != 0 && rankTeam (th) > rankTeam (slow1) &&
            cyclers[th].curPos != cyclers[slow1].curPos) {
            cyclers[th].speed = 0.5;
            continue;
        }
        if (random () < RAND_MAX / 2) {
            if (th == slow1) slow1 = 0;
            else slow1 = th;
            cyclers[th].speed = 0.5;
            continue;
        }
        if (slow1 == th) slow1 = 0;
        cyclers[th].speed = 1.0;
    }

    for (int i = 1; i < n + 1; i++) {
        th = (int) rank2[i];
        if (cyclers[th].isOut == 1) {
            if (slow2 == th) slow2 = 0;
            continue;
        }
        if (slow2 != 0 && rankTeam (th) > rankTeam (slow2) &&
            cyclers[th].curPos != cyclers[slow2].curPos) {
            cyclers[th].speed = 0.5;
            continue;
        }
        if (random () < RAND_MAX / 2) {
            if (th == slow2) slow2 = 0;
            else slow2 = th;
            cyclers[th].speed = 0.5;
            continue;
        }
        if (th == slow2) slow2 = 0;
        cyclers[th].speed = 1.0;
    }

}


 /* Caso um 3º ciclísta de uma equipe tenha completado uma nova volta desde a,
  * última vez que a função foi chamada, esta função imprime no relatório de
  * saída (saida padrão), o numero da volta que ele completou, o tempo atual da
  * simulação e os identificadores dos 3 primeiros ciclistas da equipe. Caso
  * ambas os terceiros ciclistas das duas equipes tenham completado uma nova
  * volta, são impressas as informações de ambas. */
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
        printf ("[3º colocado da equipe 1 completou uma nova volta]:\n"
        " Volta %d, tempo %fs, primeiros ciclistas: %d, %d e %d\n\n",
        lastLapUsed1, tempoSimu, t1[0], t1[1], t1[2]);
    }
    if (cyclers[t2[2]].completeLaps > lastLapUsed2) {
        lastLapUsed2 = cyclers[t2[2]].completeLaps;
        printf ("[3º colocado da equipe 2 completou uma nova volta]:\n"
        " Volta %d, tempo %fs, primeiros ciclistas: %d, %d e %d\n\n",
        lastLapUsed2, tempoSimu, t2[0], t2[1], t2[2]);
    }
}

/* Esta função deve ser chamada por uma única thread a cada iteração e é
* responsável pela realização de operações e checagens de coordenação da
* simulação como um todo. Por exemplo, ela é responsável pela verificação de
* ciclistas quebrados e ciclistas que já completaram a prova, em cada iteração.
*/
void simulationCoordination () {
    static int lastLapUsedForSpeedChange = 0;
    static int lastLapUsedForBreak = 0;

    int fc;
    double lastTime = tempoSimu;
    tempoSimu += 0.00006;
    if (debug == 1) printDebug ();
    printInLog ();

    whoFinishedCompetition ();

    for (int i = 1; i < nt + 1; i++)
    if (cyclers[i].broked == 0) {
        if (cyclers[i].isOut == 0) updateCycler (i, cyclers[i].ds,
            cyclers[i].initPos);
        else if (cyclers[i].lastUpdateTime == lastTime) updateCycler (i,
            ceil (cyclers[i].ds), cyclers[i].initPos);
    }

    fc  = firstCycler ();

    if (cyclers[fc].completeLaps % 4 == 0 &&
       cyclers[fc].completeLaps != lastLapUsedForBreak) {
       lastLapUsedForBreak = cyclers[fc].completeLaps;
       cycleBreaking ();
    }

    if (mode == 0 && cyclers[fc].completeLaps >
    lastLapUsedForSpeedChange) {

        newSpeed ();
        lastLapUsedForSpeedChange = cyclers[fc].completeLaps;
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
    static int first = 0;

    if (pthread_mutex_lock (&barrierMutex) != 0)
      fatalError ("Error mutex barrierMutex\n");
    arrived++;
    if (pthread_mutex_unlock (&barrierMutex) != 0)
      fatalError ("Error mutex barrierMutex\n");


    if (pthread_mutex_lock (&funnelMutex) != 0)
      fatalError ("Error mutex funnelMutex\n");
    if (first == 0) {
        first = 1;
        while (arrived != getNumberCyclers (0));
        arrived = 0;
        simulationCoordination ();
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

        if (pthread_mutex_unlock (&funnelMutex) != 0)
          fatalError ("Error unlock mutex funnelMutex\n");
        pthread_exit (NULL);
    }
    if (pthread_mutex_unlock (&funnelMutex) != 0)
      fatalError ("Error unlock mutex funnelMutex\n");

    if (pthread_mutex_lock (&barrierMutex) != 0)
      fatalError ("Error lock mutex barrierMutex\n");
    arrived++;

    if (arrived == getNumberCyclers (0)) {
        arrived = 0;
        first = 0;
        if (pthread_cond_broadcast (&barrierCond) != 0)
          fatalError ("Error broadcast barrierCond\n");
    }
    else if (pthread_cond_wait (&barrierCond, &barrierMutex)  != 0)
      fatalError ("Error cond wait barrierCond\n");
    if (pthread_mutex_unlock (&barrierMutex) != 0)
      fatalError ("Error mutex lock barrierMutex\n");
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

    if (pthread_mutex_lock (&pistaMutex[curPos]) != 0)
        fatalError ("Error lock mutex pistaMutex\n");
    if (pthread_mutex_lock (&pistaMutex[(curPos + 1) % d]) != 0)
        fatalError ("Error lock mutex pistaMutex\n");

    if (pista[nextPos][0] == thNum) cyclers[thNum].ds += speed;
    else if (pista[nextPos][1] == thNum) cyclers[thNum].ds += speed;
    else if (pista[nextPos][0] == 0) {

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

    if (pthread_mutex_unlock (&pistaMutex[curPos]) != 0)
        fatalError ("Error unlock mutex pistaMutex \n");
    if (pthread_mutex_unlock (&pistaMutex[(curPos + 1) % d]) != 0)
        fatalError ("Error unlock mutex pistaMutex \n");

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

    pista = malloc (d * sizeof (int *));
    pistaMutex = malloc (d * sizeof (pthread_mutex_t));
    if (pista == NULL || pistaMutex == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    for (int i = 0; i < d; i++) {
        pista[i] = malloc (2 * sizeof (int));
        if (pista[i] == NULL)
            fatalError ("Couldn't allocate sufficient memory");
        if (pthread_mutex_init (&pistaMutex[i], NULL) != 0)
            fatalError ("Error init mutex pistaMutex\n");
    }

    if (pthread_mutex_init (&funnelMutex, NULL) != 0)
        fatalError ("Error init mutex pistaMutex\n");

    arrived = 0;
    if (pthread_mutex_init (&barrierMutex, NULL) != 0)
        fatalError ("Error init mutex barrierMutex\n");
    if (pthread_cond_init (&barrierCond, NULL) != 0)
        fatalError ("Error init cond mutex barrierCond\n");

    cyclers = malloc ((nt + 1) * sizeof (cyclerInfo_t));
    if (cyclers == NULL) fatalError ("Couldn't allocate sufficient memory");

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
    if (pthread_mutex_destroy (&funnelMutex) != 0)
        Error ("Error mutex destroy funnelMutex\n");
    if (pthread_mutex_destroy (&barrierMutex) != 0)
        Error ("Error mutex destroy barrierMutex\n");
    if (pthread_cond_destroy (&barrierCond) != 0)
        Error ("Error cond destroy  barrierCond\n");
    for (int i = 0; i < d; i++) {
        free (pista[i]);
        if (pthread_mutex_destroy (&pistaMutex[i]) != 0)
            Error ("Error mutex destroy pistaMutex\n");
    }
    free (pista);
    free (pistaMutex);
    free (cyclers);
    destroyRandomCyclers ();
    destroyRankCyclers ();
}

 /* Imprime os resultados finais da simulação. */
void printFinalResults () {
    int k = 0, j = n - 1;
    int *t1, *t2;
    t1 = malloc (n * sizeof (int));
    t2 = malloc (n * sizeof (int));
    if (t1 == NULL || t2 == NULL)
        fatalError ("Couldn't allocate sufficient memory");

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
        printf ("1º lugar: equipe 1. 2º lugar: equipe 2.\n");
    else if (cyclers[t1[2]].lastUpdateTime > cyclers[t2[2]].lastUpdateTime)
        printf ("1º lugar: equipe 2. 2º lugar: equipe 1.\n");
    else
        printf ("Ocorreu empate.\n");

    printf ("Ranking final da equipe 1\n(com os tempos de chegada):"
            "\n");
    int i;
    for (i = 0; i < n; i++) {
        if (cyclers[t1[i]].broked == 1) break;
        if ((i % 5 == 0) && (i != 0)) printf ("\n");
        else printf ("%d (%f)   ", t1[i],
             cyclers[t1[i]].lastUpdateTime);
    }
    if (i < n) {
        printf ("\nCiclistas que quebraram da equipe 1:\n");
        for (; i < n; i++)
            printf ("%d, na volta %d\n", t1[i],
            cyclers[t1[i]].completeLaps);
    }
    else printf ("\nNenhum ciclista da equipe 1 quebrou.\n");

    printf ("\nRanking final da equipe 2\n(com os tempos de chegada):"
            "\n");
    for (i = 0; i < n; i++) {
        if ((i % 5 == 0) && (i != 0)) printf ("\n");
        if (cyclers[t2[i]].broked == 1) break;
        else printf ("%d (%f)   ", t2[i],
             cyclers[t2[i]].lastUpdateTime);
    }
    if (i < n) {
        printf ("\nCiclistas que quebraram da equipe 2:\n");
        for (; i < n; i++)
            printf ("%d, na volta %d\n", t2[i],
            cyclers[t2[i]].completeLaps);
    }
    else printf ("\nNenhum ciclista da equipe 2 quebrou.\n");

    free (t1);
    free (t2);
}


int main (int argc, char **argv) {

    initialization (argc, argv);

    int *id = malloc (nt * sizeof (int));
    pthread_t *cyclerThreads = malloc (nt * sizeof (pthread_t));
    if (cyclerThreads == NULL || id == NULL)
        fatalError ("Couldn't allocate sufficient memory");
    for (int i = 0; i < nt; i++) {
        id[i] = i + 1;
        if (pthread_create (&cyclerThreads[i], NULL, cycler, (void *) &id[i])
            != 0) fatalError ("Error create cyclerThreads\n");
    }

    for (int i = 0; i < nt; i++)
      if (pthread_join (cyclerThreads[i], NULL) != 0)
        fatalError ("Error join cyclerThreads\n");
    free (cyclerThreads);
    free (id);

    printFinalResults ();

    finalization ();

    return 0;
}
