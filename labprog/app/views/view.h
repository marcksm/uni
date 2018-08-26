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

#ifndef __VIEW_H__
#define __VIEW_H__

/*** Bibliotecas inclusas ***/
#include <GL/glut.h>

/*** Variáveis globais criadas ***/
GLfloat ratio;
GLuint texturas[3];
GLuint texturasFim[3];
GLuint texturasBarra[2][11];
GLuint texturasNave[2][5];
GLuint texturasHud[2][11];

/*** Protótipos das funções ***/
/*
 * Função recebe os mesmos argumentos da main, e realiza
 * o gerenciamento das principais funções de inicialização
 * da parte gráfica.
 */
void inicializaParteGrafica(int argc, char *argv[]);

/*
 * Função responsável por desenhar os componentes da tela a cada iteração.
 */
void desenha();

#endif
