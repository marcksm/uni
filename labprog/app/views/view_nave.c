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
#include "view_nave.h"
#include "../models/model_nave.h"

int countFrame = 0;
/*** Declaração de macros ***/

void desenhaNaves() {
    Vetor pos;
    int i;

    for (i = 0; i < NUM_NAVES; i++) {

        glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturasNave[i][countFrame]);
        printf ("%d\n", countFrame);
	countFrame = (countFrame + 1)%4;	
        pos = posicaoRelativaNave(i);

        glPushMatrix();
        glLoadIdentity();

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

