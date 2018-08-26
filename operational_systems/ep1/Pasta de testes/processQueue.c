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

#include <stdio.h>
#include <stdlib.h>
#include "processQueue.h"

/*  Função recebe uma string message e imprime na saida de erro
 *  a mensagem da string.
 */
static void fatalError (char *message) {
    fprintf (stderr, "Error: %s\n", message);
    exit (EXIT_FAILURE);
}

processQueue *createQueue () {
    processQueue *q = malloc (sizeof (processQueue));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->length = 100;
    q->p = malloc (q->length * sizeof (process));
    return q;
}

void orderedInsertion (processQueue *q, process s) {
    if (q->rear == q->length) q = resize (q, 2 * q->length);
    int e = q->front;
    int d = q->rear-1;
    int m = (e+d)/2;
    int pos, i;
    while (e < d - 1) {
        m = (e + d) / 2;
        if (q->p[m].rt == s.rt) {e = d = m; break;}
        else if (q->p[m].rt < s.rt) e = m;
        else d = m;
   }
    if (s.rt >= q->p[e].rt && s.rt <= q->p[d].rt) pos = d;
    else if (s.rt > q->p[d].rt) pos = d + 1;
    else pos = e;
    for (i = q->rear-1; i >= pos; i--) q->p[i+1] = q->p[i];
    q->p[i+1] = s;
    q->size++;
    q->rear++;
}

processQueue *resize (processQueue *q, int capacity) {
    process *temp = malloc (capacity * sizeof (process));
    for (int i = 0; i < q->size; i++) {
        temp[i] = q->p[(q->front + i) % q->length];
    }
    q->length = capacity;
    free (q->p);
    q->p = temp;
    q->front = 0;
    q->rear  = q->size;
    return q;
}

int isEmpty (processQueue *q) {
    return q->size == 0;
}

int size (processQueue *q) {
    return q->size;
}

void enqueue (processQueue *q, process s) {
    if (q->size == q->length || q->rear == q->length)
        q = resize (q, 2 * q->length);
    q->p[q->rear++] = s;
    if (q->rear == q->length) q->rear = 0;
    q->size++;
}

process dequeue (processQueue *q) {
    if (isEmpty (q)) fatalError ("Queue underflow");
    process aux = q->p[q->front];
    q->front++;
    q->size--;
    if (q->front == q->length) q->front = 0;
    if (q->size > 0 && q->size == q->length/4) q = resize (q, q->length/2);
    return aux;
}

process peek (processQueue *q) {
    if (isEmpty (q)) fatalError("Queue underflow");
    return q->p[q->front];
}

void destroyQueue (processQueue *q) {
    free (q->p);
    free (q);
}
