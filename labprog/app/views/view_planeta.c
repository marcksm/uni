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

/*** Bibliotecas inclusas ***/
#include <GL/glut.h>
#include "view.h"
#include "view_planeta.h"
#include "../models/model_planeta.h"

/*** Macros definidas ***/

void desenhaPlaneta() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[3]);

    glPushMatrix();
    glLoadIdentity();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex2f(-ESCALA_PLANETA, ESCALA_PLANETA);
    glTexCoord2f(1.0, 0.0); glVertex2f(ESCALA_PLANETA, ESCALA_PLANETA);
    glTexCoord2f(1.0, 1.0); glVertex2f(ESCALA_PLANETA, -ESCALA_PLANETA);
    glTexCoord2f(0.0, 1.0); glVertex2f(-ESCALA_PLANETA, -ESCALA_PLANETA);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
