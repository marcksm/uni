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

#ifndef __NAVE_H__
#define __NAVE_H__

/*** Bibliotecas inclusas ***/
#include <stdio.h>
#include "model_vetor.h"

/*** Declaração de macros ***/
#define NUM_NAVES 2
#define TAM_MAX_NOME 30
#define ESCALA_NAVE 0.08

/*** Estruturas de dados criadas ***/
typedef struct nave {
	char nome[TAM_MAX_NOME];
	float massa;
	float raio;
	float energia;
	float angulo;
	Vetor posicao;
	Vetor velocidade;
	Vetor aceleracao;
	Vetor forca;
	Boolean propulsaoAtivada;
	Boolean freioAtivado;
} Nave;

/*** Variáveis globais criadas ***/
Nave *naves;
Vetor posicao;
Boolean colisao;

/*** Protótipos das funções ***/
float seno(float angle);
float cosseno(float angle);

/*
 * Recebe um arquivo de entrada. A função cria um objeto do tipo naves
 * e o inicializa com as informações passadas pelo
 * arquivo de entrada.
 */
void leituraNaves(FILE *entrada);

/*
 * Recebe um inteiro i. A função atualiza a posição da nave i com
 * base nas forças sendo aplicadas neste.
 */
void atualizaNave(int i);

/*
 * Recebe um inteiro i. A função calcula a posição da nave i
 * relativa às coordenadas da janela.
 */
Vetor posicaoRelativaNave(int i);

/*
 * Define o raio das naves, com base no tamanho do universo.
 */
void defineRaioNave();

#endif
