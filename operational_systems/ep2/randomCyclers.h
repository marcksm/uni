/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

#ifndef _RANDOMCYCLERS_H
#define _RANDOMCYCLERS_H

/* Inicializa o módulo randomCyclers, criando uma matriz cyclers
 * 3 linhas por (2 * n) + 1  colunas.
 * A posição cyclers[equipe][0] contem informação de quantos ciclistas
 * ainda estão na simulação.
 * A linha cyclers[0][1] a cyclers[0][cyclers[0][0]], mostra os ciclistas das duas equipes
 * A linha cyclers[1][1] a cyclers[1][cyclers[1][0]] mostra os ciclistas da equipe 1
 * A linha cyclers[2][1] a cyclers[2][cyclers[2][0]] mostra os ciclistas da equipe 2
 */
void initRandomCyclers (int n);


/* Retorna o identificador de um ciclista que ainda está na competição,
 * escolhido pseudo-aleatóriamente. O inteiro mode passado como
 * parametro pode ser 0, 1 ou 2  e define se o ciclista aleatóriamente
 * escolhido será, respectivamente, de qualquer equipe, da equipe 1, ou da 2.
 */
int getRandomCycler (int mode);

/* Recebe um inteiro mode, e devolve o numero de ciclistas disponiveis na fila
 */
int getNumberCyclers (int mode);

/* Recebe um inteiro mode e devolve um vetor cyclers de inteiros com o
 * identificador dos ciclistas disponiveis nesta fila. Onde 1<=i<=cyclers[0]
 * tal que cyclers[i] é um ciclista na competição.
 */
int *avaliableCyclers (int mode);

/* Recebe um inteiro mode e retorna 1 se a fila de ciclistas desse mode é 0.
 * e retorna 0 caso contrário.
 */
int isCyclerEmpty (int mode);

/* Recebe um inteiro cycler e remove um ciclista da competição
*/
void removeCycler (int cycler);

/* Libera a memória da matriz de ciclistas.
 */
void destroyRandomCyclers ();

/* Recebe um inteiro n, e reseta a matriz de cyclers
 */
void resetRandomCyclers (int n);


#endif
