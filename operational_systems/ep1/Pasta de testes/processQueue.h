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


#ifndef _QUEUE_H
#define _QUEUE_H

#include "process.h"

/* Estrutura da fila de processos:
 * *p ponteiro do vetor de processos do tipo process
 *
 * front, rear são os flags do inicio e fim da fila.
 *
 * size corresponde ao numero de processos atual na fila
 *
 * length corresponde ao tamanho do vetor de processos do tipo process
 */
typedef struct processQueue {
    process *p;
    int front, rear;
    int size;
    int length;
} processQueue;

/* Função devolve uma fila do tipo processQueue.
 */
processQueue *createQueue ();

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e um inteiro capacity. A função privada redimensiona o vetor
 * de processos da fila *q de acordo com o inteiro capacity e a
 * devolve.
 */
processQueue *resize (processQueue *q, int capacity);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e um process s e faz a inserção ordenada do process s confome
 * seu remaining time, o parametro s.rt.
 */
void orderedInsertion (processQueue *q, process s);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e retorna 1 se a fila esta vazia.
 */
int isEmpty (processQueue *q);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e retorna um inteiro do tamanho da fila.
 */
int size (processQueue *q);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e um process s e o coloca na fila.
 */
void enqueue (processQueue *q, process s);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * remove e devolve um process da fila.
 */
process dequeue (processQueue *q);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * sem alterar a fila devolve um process.
 */
process peek (processQueue *q);

/* Função recebe um ponteiro *q para uma fila do tipo processQueue
 * e libera a memória alocada.
 */
void destroyQueue (processQueue *q);

#endif
