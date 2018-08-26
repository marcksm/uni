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

#include <GL/glut.h>
#include <math.h>
#include "../models/model_projetil.h"
#include "../controllers/controller.h"

/*** Declaração de macros ***/
#define PAUSA_ENTRE_DISPAROS 300.0

/*** Declaração de variáveis globais ***/
float tempoDisparoNave1 = 0.0, tempoDisparoNave2 = 0.0;
Boolean estadosTecla[256];
Boolean estadosTeclaEspecial[256];

/*** Declaração das funções ***/
void teclaPressionada(unsigned char tecla, int x, int y) {
	estadosTecla[tecla] = TRUE;
}

void teclaLiberada(unsigned char tecla, int x, int y) {
	estadosTecla[tecla] = FALSE;
}

void operacoesTecla() {
	/* Ativa ou desativa a propulsão da nave 2 conforme a tecla 'w' esteja ativada */
	naves[1].propulsaoAtivada = estadosTecla['w'];

	/* Ativa ou desativa o freio da nave 2 conforme a tecla 's' esteja ativada */
	naves[1].freioAtivado = estadosTecla['s'];

	/* Disparo de projéteis pela nave 2 */
	if (estadosTecla['q']) {
		if (glutGet(GLUT_ELAPSED_TIME) - tempoDisparoNave2 >= PAUSA_ENTRE_DISPAROS) {
			tempoDisparoNave2 = glutGet(GLUT_ELAPSED_TIME);
			criaProjetil(naves[1]);
		}
	}

	/* Rotação da nave 2 */
	if (estadosTecla['a']) {
		naves[1].angulo = -1.0 + fmod(naves[1].angulo, 360.0);
	}

	if (estadosTecla['d']) {
		naves[1].angulo = 1.0 + fmod(naves[1].angulo, 360.0);
	}

	/* Disparo de projéteis pela nave 1 */
	if (estadosTecla['/']) {
		if (glutGet(GLUT_ELAPSED_TIME) - tempoDisparoNave1 >= PAUSA_ENTRE_DISPAROS) {
			tempoDisparoNave1 = glutGet(GLUT_ELAPSED_TIME);
			criaProjetil(naves[0]);
		}
	}
}

void teclaEspecial(int tecla, int x, int y) {
	estadosTeclaEspecial[tecla] = TRUE;
}

void teclaEspecialPressionada(int tecla, int x, int y) {
	estadosTeclaEspecial[tecla] = FALSE;
}

void operacoesTeclaEspecial() {
	/* Ativa ou desativa a propulsão da nave 1 conforme a tecla '↑' esteja ativada */
	naves[0].propulsaoAtivada = estadosTeclaEspecial[GLUT_KEY_UP];

	/* Ativa ou desativa o freio da nave 1 conforme a tecla '↓' esteja ativada */
	naves[0].freioAtivado = estadosTeclaEspecial[GLUT_KEY_DOWN];

	/* Rotação da nave 1 */
	if (estadosTeclaEspecial[GLUT_KEY_LEFT]) {
		naves[0].angulo = -1.0 + fmod(naves[0].angulo, 360.0);
	}

	if (estadosTeclaEspecial[GLUT_KEY_RIGHT]) {
		naves[0].angulo = 1.0 + fmod(naves[0].angulo, 360.0);
	}
}
