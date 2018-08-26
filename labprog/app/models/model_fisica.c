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
#include <math.h>
#include <GL/glut.h>
#include "model_fisica.h"
#include "model_universo.h"

/*** Macros definidas ***/
#define CONSTANTE_GRAVITACAO 6.674287e-11

/*** Declaração das funções ***/
Forca calculaForca(float m1, Vetor p1, float m2, Vetor p2) {
	Forca forca;
	float numerador, denominador;

	inicializaVetor(&forca);

	numerador = (float) CONSTANTE_GRAVITACAO * ((m1 * m2) * (p2.x - p1.x));
	denominador = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
	if (denominador == 0.0) return forca;
	forca.x = numerador / pow(denominador, 3);
	numerador = (float) CONSTANTE_GRAVITACAO * ((m1 * m2) * (p2.y - p1.y));
	forca.y = numerador / pow(denominador, 3);

	return forca;
}

Vetor calculaAceleracao(Vetor forca, float massa) {
	Vetor aceleracao;

	inicializaVetor(&aceleracao);
	if (massa == 0) return aceleracao;
	aceleracao.x = forca.x / massa;
	aceleracao.y = forca.y / massa;

	return aceleracao;
}

Vetor calculaVelocidade(Vetor aceleracao) {
	Vetor velocidade;

	inicializaVetor(&velocidade);

	velocidade.x = aceleracao.x * intervaloIteracao;
	velocidade.y = aceleracao.y * intervaloIteracao;

	return velocidade;
}

Vetor calculaPosicao(Vetor velocidade) {
	Vetor posicao;

	inicializaVetor(&posicao);

	posicao.x = velocidade.x * intervaloIteracao;
	posicao.y = velocidade.y * intervaloIteracao;

	return posicao;
}

Boolean calculaColisao(float raio1, Vetor p1, float raio2, Vetor p2) {
    float altura = glutGet(GLUT_WINDOW_HEIGHT), largura = glutGet(GLUT_WINDOW_WIDTH);
    float ratio = largura/altura;
    float dist = sqrt(pow(ratio * p2.x - ratio * p1.x, 2) + pow(p2.y - p1.y, 2));

    if (dist <= (raio1 + raio2)) return TRUE;
    else return FALSE;
}

/* Calcula o seno em graus */
float seno(float angulo)
{
	float anguloRadianos = angulo * PI / 180;
	return sin(anguloRadianos);
}

/* Calcula o cosseno em graus */
float cosseno(float angulo)
{
	float anguloRadianos = angulo * PI / 180;
	return cos(anguloRadianos);
}
