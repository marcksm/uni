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

#ifndef __UNIVERSO_H__
#define __UNIVERSO_H__

/*** Bibliotecas inclusas ***/
#include "model_vetor.h"

/*** Macros definidas ***/

/*** Variáveis globais criadas ***/
float intervaloIteracao;
float tempoTotal;
float tamanhoUniverso;

/*** Protótipos das funções ***/

/*
 * A função calcula e atribui o tamanho do universo na
 * variavel global tamanhoUniverso.
 */
void tamUniverso();

/*
 * A função recebe um vetor posicao e faz a normalização,
 * o modo toroidal, desse vetor conforme o tamanhoUniverso
 */
void normalizaPosicao(Vetor *posicao);

/*
 * Função que desenha a textura dos objetos do universo
 * na janela.
 */
void desenhaUniverso();

#endif
