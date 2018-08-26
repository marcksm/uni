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

#ifndef __FISICA_H__
#define __FISICA_H__

/*** Bibliotecas inclusas ***/
#include "model_vetor.h"

/*** Macros definidas ***/
#define PI 3.141592653589793

/*** Estruturas de dados criadas ***/
typedef Vetor Forca;

/*** Protótipos das funções ***/

/*
 * Recebe os floats m1 e m2 e as estruturas do tipo Vetor
 * p1 e p2, onde m1 e m2 são as massas dos corpos e p1 e p2
 * contêm as posições dos corpos. A função devolve a força
 * resultante dessa interação.
 */
Forca calculaForca(float m1, Vetor p1, float m2, Vetor p2);

/*
 * Recebe um vetor forca e um float massa. A função devolve um
 * vetor aceleração respectivo dessas componentes.
 */
Vetor calculaAceleracao(Vetor forca, float massa);

/*
 * Recebe um vetor aceleração. A função devolve um
 * vetor velocidade respectivo a essa componente.
 */
Vetor calculaVelocidade(Vetor aceleracao);

/*
 * Recebe um vetor velocidade. A função devolve um
 * vetor posição respectivo a essa componente.
 */
Vetor calculaPosicao(Vetor velocidade);

/*
 * Calcula se houve colisão entre dois corpos, com base em seus raios e posições
 * no espaço.
 */
Boolean calculaColisao(float raio1, Vetor p1, float raio2, Vetor p2);

/*
 * Calcula o seno de um ângulo, em graus.
 */
float seno(float angulo);

/*
 * Calcula o cosseno de um ângulo, em graus.
 */
float cosseno(float angulo);

#endif
