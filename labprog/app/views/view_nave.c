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
#include <AL/alut.h>
#include <GL/glut.h>
#include "view.h"
#include "view_nave.h"
#include "../models/model_nave.h"
#include "../batalha-espacial.h"
#include "../models/model_universo.h"

/*** Definição de macros ***/
#define PAUSA_ENTRE_ATUALIZACAO 50.0
#define NAVE_ATINGIDA 4

/*** Declaração de variáveis globais ***/
int contadorTexturas[2] = {0, 0};
float tempoAnimacao = 0.0;

/*
 * Faz a imagem da nave ficar animada quando esta estiver com a propulsão ligada.
 */
static void animaNaves(int i) {
	if (glutGet(GLUT_ELAPSED_TIME) - tempoAnimacao >= PAUSA_ENTRE_ATUALIZACAO) {
		tempoAnimacao = glutGet(GLUT_ELAPSED_TIME);
		contadorTexturas[i] = (contadorTexturas[i] + 1) % 4;
	}
}

void piscaNave(int i) {
	if (naves[i].energia > 0)
		contadorTexturas[i] = NAVE_ATINGIDA;
}

void desenhaNaves() {
	int i, j;
	Vetor pos;

	for (i = 0; i < NUM_NAVES; i++) {
		j = contadorTexturas[i];
		if (naves[i].propulsaoAtivada || j == NAVE_ATINGIDA) {
			animaNaves(i);
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texturasNave[i][j]);

		glPushMatrix();
		glLoadIdentity();

		pos = posicaoRelativaNave(i);
		glTranslatef(pos.x, pos.y, 0.0);
		glRotatef(naves[i].angulo, 0.0, 0.0, -1.0);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-ESCALA_NAVE, ESCALA_NAVE);
		glTexCoord2f(1.0, 0.0); glVertex2f(ESCALA_NAVE, ESCALA_NAVE);
		glTexCoord2f(1.0, 1.0); glVertex2f(ESCALA_NAVE, -ESCALA_NAVE);
		glTexCoord2f(0.0, 1.0); glVertex2f(-ESCALA_NAVE, -ESCALA_NAVE);
		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	}
}

void somExplosao() {
	ALuint buffer, source;

	buffer = alutCreateBufferFromFile("app/views/audio/explosao.wav");
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
}
