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
#include "view_projetil.h"
#include "../models/model_projetil.h"

/*** Macros definidas ***/


/*** Declaração das funções ***/
void desenhaProjeteis() {
    Vetor pos;
    int i;

    for (i = 0; i < NUM_PROJETEIS; i++) {
        if (projeteis[i].projetilAtivo == TRUE) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturas[4]);
            pos = posicaoRelativaProjetil(i);

            glPushMatrix();
            glLoadIdentity();

            glTranslatef(pos.x, pos.y, 0.0);
            glRotatef(projeteis[i].angulo, 0.0, 0.0, -1.0);

            glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex2f(-ESCALA_PROJETIL, ESCALA_PROJETIL);
            glTexCoord2f(1.0, 0.0); glVertex2f(ESCALA_PROJETIL, ESCALA_PROJETIL);
            glTexCoord2f(1.0, 1.0); glVertex2f(ESCALA_PROJETIL, -ESCALA_PROJETIL);
            glTexCoord2f(0.0, 1.0); glVertex2f(-ESCALA_PROJETIL, -ESCALA_PROJETIL);
            glEnd();

            glPopMatrix();
            glDisable(GL_TEXTURE_2D);
        }
    }
}
