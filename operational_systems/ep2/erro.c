/*******************************************************************************

    Marcos Vinicius do Carmo Sousa  nº USP: 9298274
    Matheus Tavares Bernardino      nº USP: 9292987


*******************************************************************************/

#include "erro.h"
#include <stdio.h>
#include <stdlib.h>

void fatalError (char *message) {
    fprintf (stderr, "Error: %s\n", message);
    exit (EXIT_FAILURE);
}

void Error (char *message) {
    fprintf (stderr, "Error: %s\n", message);
}
