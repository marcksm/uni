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

#include <GL/glut.h>
#include <math.h>
#include "../models/model_projetil.h"
#include "../controllers/controller.h"

Boolean estadosTecla[256];
Boolean estadosTeclaEspecial[256];

void teclaPressionada(unsigned char tecla, int x, int y) {
    estadosTecla[tecla] = TRUE;
}

void teclaLiberada(unsigned char tecla, int x, int y) {
    estadosTecla[tecla] = FALSE;
}

void operacoesTecla() {
    /* Ativa ou desativa a propulsão conforme a tecla 'w' esteja ativada */
    naves[1].propulsaoAtivada = estadosTecla['w'];

    if (estadosTecla['s']) {
         criaProjetil(naves[1]);
    }

    if (estadosTecla['a']) {
         naves[1].angulo = -1.0 + fmod(naves[1].angulo, 360.0);
    }

    if (estadosTecla['d']) {
         naves[1].angulo = 1.0 + fmod(naves[1].angulo, 360.0);
    }
}

void teclaEspecial(int tecla, int x, int y) {
    estadosTeclaEspecial[tecla] = TRUE;
}

void teclaEspecialPressionada(int tecla, int x, int y) {
    estadosTeclaEspecial[tecla] = FALSE;
}

void operacoesTeclaEspecial() {
    /* Ativa ou desativa a propulsão conforme a tecla '↑' esteja ativada */
    naves[0].propulsaoAtivada = estadosTeclaEspecial[GLUT_KEY_UP];

    if (estadosTeclaEspecial[GLUT_KEY_DOWN]) {
         criaProjetil(naves[0]);
    }

    if (estadosTeclaEspecial[GLUT_KEY_LEFT]) {
         naves[0].angulo = -1.0 + fmod(naves[0].angulo, 360.0);
    }

    if (estadosTeclaEspecial[GLUT_KEY_RIGHT]) {
         naves[0].angulo = 1.0 + fmod(naves[0].angulo, 360.0);
    }
}
