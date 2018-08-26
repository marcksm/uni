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

/*** Bibliotecas inclusas ***/
#include "model_auxiliar.h"
#include "model_universo.h"
#include "model_planeta.h"

/*** Declaração de macros ***/
#define ESCALA_RAIO_PLANETA 1.05 * tamanhoUniverso * ESCALA_PLANETA

/*** Declaração das funções ***/
void leituraPlaneta(FILE *entrada) {
	planeta = mallocSafe(sizeof(Planeta));
	fscanf(entrada, "%f %f", &planeta->raio, &planeta->massa);
	inicializaVetor(&planeta->posicao);
}

void defineRaioPlaneta() {
	planeta->raio = ESCALA_RAIO_PLANETA;
}
