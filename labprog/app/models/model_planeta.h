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

#ifndef __PLANETA_H__
#define __PLANETA_H__

/*** Bibliotecas inclusas ***/
#include <stdio.h>
#include "model_vetor.h"

/*** Declaração de macros ***/
#define ESCALA_PLANETA 0.2

/*** Estruturas de dados criadas ***/
typedef struct planeta {
	float raio;
	float massa;
	Vetor posicao;
} Planeta;

/*** Variáveis globais criadas ***/
Planeta *planeta;

/*** Protótipos das funções ***/

/*
 * Recebe um arquivo de entrada. A função cria um objeto do
 * tipo planeta e o inicializa com as informações passadas pelo
 * arquivo de entrada.
 */
void leituraPlaneta(FILE *entrada);

/*
 * Define o raio do planeta, com base no tamanho do universo.
 */
void defineRaioPlaneta();

#endif
