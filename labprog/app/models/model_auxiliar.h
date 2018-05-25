/* ********************************************** */
/*                                                */
/*    MAC0211 - Laboratório de Programação I      */
/*          Exercício-programa - Fase 3           */
/*                                                */
/*    Bárbara de Castro Fernandes - 7577351       */
/*    Duílio Henrique Haroldo Elias - 6799722     */
/*    Marcos Vinicius do Carmo Sousa - 9298274	  */
/*                                                */
/* ********************************************** */

#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

/*** Bibliotecas inclusas ***/
#include <stdio.h>

/*** Protótipos das funções ***/

/*
 * Recebe uma string mensagem e a imprime
 */
void imprimeErro(char *mensagem);

/*
 * Recebe o tamanho nBytes de um objeto e realiza o alocamento de memória
 * de maneira segura.
 */
void *mallocSafe(size_t nBytes);

#endif
