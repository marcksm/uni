/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

#ifndef _RANKCYCLERS_H
#define _RANKCYCLERS_H

/* Recebe um inteiro n, e inicializa a estrutura de ranking com
* n ciclistas em cada equipe, onde i, j inteiros, 1<=i<=n é a primeira
* equipe e n+1<=j<=2*n é  a segunda equipe.
*/
void initRankCyclers (int n);

/* Funcao que recebe o ciclista e devolve o ranking dele
 * na equipe. Onde cycler 1<=cycler<=n ou n+1<=cycler<=2*n
*/
int rankTeam (int cycler);

/* Função que recebe o ranking e a equipe, e devolve o ciclista
 * correspondente ao ranking na equipe. rk e team são inteiros onde
 * 1<=rk<=n e 1<=team<=2.
*/
int rankCycler (int rk, int team);

/* Recebe um ciclista cycler e uma distancia dist e atualiza o ranking
* do ciclista na competição.
*/
void updateCycler (int cycler, double dist, int initPos);

/* Função que recebe a equipe e devolve um vetor double rank[i]
* onde o indice do vetor é o ranking e o rank[i] é o ciclista neste
* rank. 1<=i<=n.
*/
double *queue_i_rank (int mode);

/* Função que recebe a equipe e devolve um vetor double cyclers[i]
* onde o indice do vetor são os ciclistas e o cyclers[i] é o rank deste
* ciclista. 1<=i<=n.
*/
double *queue_i_cycler (int mode);

/* Desaloca vetores inicializados
*/
void destroyRankCyclers ();

/* Função que recebe o ranking e devolve o ciclista 1<=ciclista<=2*n respectivo.
 * rk é o ranking onde, 1 <=rk<= 2*n. Se devolver 0, não há ciclistas
 * ocupando essa posição no ranking.
*/
int rankCyclerOverall (int rk);

/* Inicializa ciclista cycler no ranking rk
*/
void setCycler (int cycler, double rk);

#endif
