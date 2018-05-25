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
#include "view_universo.h"
#include "view_planeta.h"
#include <math.h>
#define PI 3.1415926535898

GLint circle_points =100;
/*** Declaração das funções ***/
void draw(float r, float cx, float cy)
{
    glClear(GL_COLOR_BUFFER_BIT);
    double angle = 2*PI/circle_points;
    glBegin(GL_LINE_LOOP);
        double angle1=0.0;
        glVertex2d( cos(0.0) , sin(0.0));
        int i;
        for ( i=0 ; i< circle_points ;i++)
        {
            glVertex2d(cos(angle1)*r + cx,sin(angle1)*r + cy);
            angle1 += angle ;
        }
    glEnd();
    glFlush();
}
void desenhaFundo() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[2]);

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

void desenhaUniverso() {
    desenhaFundo();
    /*draw(0.22,0,0);*/
    desenhaPlaneta();

}
