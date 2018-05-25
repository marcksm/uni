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

#ifndef __PROJETIL_H__
#define __PROJETIL_H__

/*** Bibliotecas inclusas ***/
#include <stdio.h>
#include "model_vetor.h"
#include "model_nave.h"

#define NUM_PROJETEIS 200
#define ESCALA_PROJETIL 0.01

/*** Estruturas de dados criadas ***/
typedef struct projetil {
        float massa;
        float raio;
        float tempo;
        float angulo;
        Vetor posicao;
        Vetor velocidade;
        Vetor aceleracao;
        Vetor forca;
        Boolean projetilAtivo;
} Projetil;


/*** Variáveis globais criadas ***/
Projetil *projeteis;
int nProjeteis, tProjeteis;
Vetor posicao;
float angulo;

/*** Protótipos das funções ***/

/*
 * Recebe um arquivo de entrada. A função cria um objeto do tipo
 * projétil e o inicializa com as informações passadas pelo
 * arquivo de entrada.
 */
void leituraProjeteis(FILE *entrada);


/*
 * Recebe um inteiro i. A função atualiza a posição do projétil i
 * com base nas forças sendo aplicadas neste.
 */
void atualizaProjetil(int i);

/*
 * Recebe um inteiro i. A função calcula a posição do projétil i
 * relativa às coordenadas da janela.
 */
Vetor posicaoRelativaProjetil(int i);

void atualizaTempoProjeteis();
void criaProjetil(Nave nave);
void defineRaioProjetil();

#endif
