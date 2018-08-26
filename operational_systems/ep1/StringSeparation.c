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

#include <stdlib.h> // exit, malloc, realloc, free
#include <stdio.h> // fprintf



/* Imprime na saida padrão de erro uma mensagem de erro e finaliza o programa
com status de saída igual a EXIT_FAILURE. */
static void fatalError (char *message) {
    fprintf (stderr, "Fatal error: %s\n", message);
    exit (EXIT_FAILURE);
}



char ** wordsIn (char *text) {

    int i; // atual index of the iteration in text
    int mwl, mwq = 4; // maximun word length and maximun word's quantit
    int cwl, cwq = 0; // current word length and current word's quantit
    char **words = NULL; // the words to be returned by the function

    if (text == NULL || text[0] == '\0') return NULL;
    for (i = 0; text[i] == ' '; i++);
    if (text[i] == '\0') return NULL;

    i = 0;
    words = malloc (mwq * sizeof (char *));
    if (words == NULL) fatalError ("Out of memory.");
    do {
        while (text[i] == ' ') i++;
        if (text[i] == '\0') break;

        cwl = 0;
        mwl = 4;

        if (cwq >= mwq){
            mwq *= 2;
            words = realloc (words, mwq * sizeof (char *));
            if (words == NULL) fatalError ("Out of memory.");
        }
        words[cwq] = malloc (mwl * sizeof (char));
        if (words[cwq] == NULL) fatalError ("Out of memory.");

        while (text[i] != ' ' && text[i] != '\0') {
            if (cwl >= mwl){
                mwl *= 2;
                words[cwq] = realloc (words[cwq], mwl * sizeof (char));
                if (words[cwq] == NULL) fatalError ("Out of memory.");
            }
            words[cwq][cwl] = text[i];
            i++;
            cwl++;
        }
        if (cwl >= mwl){
            mwl *= 2;
            words[cwq] = realloc (words[cwq], mwl * sizeof (char));
            if (words[cwq] == NULL) fatalError ("Out of memory.");
        }
        words[cwq][cwl] = '\0';
        cwl++;
        cwq++;
    } while (text[i] != '\0');

    if (cwq >= mwq){
        mwq += 1;
        words = realloc (words, mwq * sizeof (char *));
        if (words == NULL) fatalError ("Out of memory.");

    }
    words[cwq] = NULL;

    return words;
}
