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
#include "view_universo.h"
#include "view_planeta.h"
#include "../models/model_nave.h"
#include <math.h>

/* Declaração de macros */
#define PI 3.1415926535898
#define ESCALA_BARRA 0.1
#define ESCALA_MSG 0.7

/*** Declaração das funções ***/
void desenhaBarra1() {
	int i = naves[0].energia / 10;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturasBarra[0][i]);

	glPushMatrix();
	glLoadIdentity();

	glTranslatef(-1, -0.8, 0.0);
	glRotatef(0, 0.0, 0.0, -1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-ESCALA_BARRA, 2 * ESCALA_BARRA);
	glTexCoord2f(1.0, 0.0); glVertex2f(ESCALA_BARRA, 2 * ESCALA_BARRA);
	glTexCoord2f(1.0, 1.0); glVertex2f(ESCALA_BARRA, -2 * ESCALA_BARRA);
	glTexCoord2f(0.0, 1.0); glVertex2f(-ESCALA_BARRA, -2 * ESCALA_BARRA);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void desenhaBarra2() {
	int i = naves[1].energia / 10;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturasBarra[0][i]);

	glPushMatrix();
	glLoadIdentity();

	glTranslatef(1, -0.8, 0.0);
	glRotatef(0, 0.0, 0.0, -1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-ESCALA_BARRA, 2 * ESCALA_BARRA);
	glTexCoord2f(1.0, 0.0); glVertex2f(ESCALA_BARRA, 2 * ESCALA_BARRA);
	glTexCoord2f(1.0, 1.0); glVertex2f(ESCALA_BARRA, -2 * ESCALA_BARRA);
	glTexCoord2f(0.0, 1.0); glVertex2f(-ESCALA_BARRA, -2 * ESCALA_BARRA);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void desenhaFundo() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[0]);

	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-(ratio + 1/ratio), 1.0);
	glTexCoord2f(1.0, 0.0); glVertex2f(ratio + 1/ratio, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex2f(ratio + 1/ratio, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex2f(-(ratio + 1/ratio), -1.0);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void desenhaFim() {
	int i;

	if (naves[0].energia == 0 && naves[1].energia == 0) i = 0;
	else if (naves[1].energia == 0) i = 1;
	else i = 2;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturasFim[i]);

	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(-2.5 * ESCALA_MSG, ESCALA_MSG);
	glTexCoord2f(1.0, 1.0); glVertex2f(2.5 * ESCALA_MSG, ESCALA_MSG);
	glTexCoord2f(1.0, 0.0); glVertex2f(2.5 * ESCALA_MSG, -ESCALA_MSG);
	glTexCoord2f(0.0, 0.0); glVertex2f(-2.5 * ESCALA_MSG, -ESCALA_MSG);
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void inicializaAudio(int argc, char *argv[]) {
	ALuint buffer, source;

	alutInit(&argc, argv);
	buffer = alutCreateBufferFromFile("app/views/audio/soundtrack.wav");
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
}
