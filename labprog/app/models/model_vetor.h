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

#ifndef __VETOR_H__
#define __VETOR_H__

/*** Estruturas de dados criadas ***/
typedef struct vetor {
	float x;
	float y;
} Vetor;

typedef enum boolean {FALSE, TRUE} Boolean;

/*** Protótipos das funções ***/

/*
 * Recebe uma estrutura do tipo Vetor e inicializa suas váriaveis.
 */
void inicializaVetor(Vetor *vetor);

#endif
