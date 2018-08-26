/* ********************************************** */
/*                                                */
/*    MAC0211 - Laboratório de Programação I      */
/*          Exercício-programa - Fase 4           */
/*                                                */
/*    Bárbara de Castro Fernandes - 7577351       */
/*    Duílio Henrique Haroldo Elias - 6799722     */
/*    Marcos Vinicius do Carmo Sousa - 9298274	  */
/*                                                */
/* ********************************************** */

#include <stdlib.h>
#include "model_auxiliar.h"

/*** Declaração das funções ***/
void imprimeErro(char *mensagem) {
	fprintf(stderr, "%s", mensagem);
	exit(EXIT_FAILURE);
}

void *mallocSafe(size_t nBytes) {
	void *p;
	p = malloc(nBytes);
	if (p == NULL) {
		imprimeErro("Erro na alocação de memória.\n");
	}
	return p;
}
