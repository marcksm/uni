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
#include <SOIL/SOIL.h>
#include "../batalha-espacial.h"
#include "../models/model_universo.h"
#include "view.h"
#include "../controllers/controller.h"

/*** Macros definidas ***/
#define IMAGEM_FUNDO "app/views/texturas/universo/fundo.jpg"
#define IMAGEM_NAVE1 "app/views/texturas/naves/nave1.png"
#define IMAGEM_NAVE2 "app/views/texturas/naves/nave2.png"
#define IMAGEM_PLANETA "app/views/texturas/planeta/planeta.png"
#define IMAGEM_PROJETIL "app/views/texturas/projetil/projetil.png"

/*** Variáveis globais criadas ***/
static GLfloat fovy = 45.0;
static GLfloat near = 0.0;
static GLfloat far = 1000.0;

/*** Protótipos das funções ***/

/*
 *  Ajusta da imagem da simulação quando a janela é redimensionada.
 */
static void redimensionaTela(int largura, int altura) {
    if (altura == 0) altura = 1;
    ratio = (float) largura / (float) altura;
    gluOrtho2D(-ratio, ratio, -1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0.0, 0.0, largura, altura);
    gluPerspective(fovy, ratio, near, far);
    glOrtho(-ratio, ratio, 1.0, -1.0, near, far);
}

/*
 *  Inicializa a janela com 75% da altura e da largura da tela do usuário.
 */
static void janela() {
    float alturaTela, larguraTela;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    larguraTela = glutGet(GLUT_SCREEN_WIDTH);
    alturaTela = glutGet(GLUT_SCREEN_HEIGHT);

    glutInitWindowSize(larguraTela * 0.75, alturaTela * 0.75);
    glutInitWindowPosition(-1.0, -1.0);
    glutCreateWindow("Batalha Espacial");
}

/*
 *  Carrega uma determinada textura.
 */
static void carregaTextura(GLuint *textura, char *nomeTextura) {
    *textura = SOIL_load_OGL_texture
        (
         nomeTextura,
         SOIL_LOAD_AUTO,
         SOIL_CREATE_NEW_ID,
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
}

/*
 *  Carrega a cada iteração as texturas dos objetos contidos no universo.
 */
static void carregaTexturas() {
/*    carregaTextura(&texturas[0], IMAGEM_NAVE1);*/
/*    carregaTextura(&texturas[1], IMAGEM_NAVE2);*/
    carregaTextura(&texturas[2], IMAGEM_FUNDO);
    carregaTextura(&texturas[3], IMAGEM_PLANETA);
    carregaTextura(&texturas[4], IMAGEM_PROJETIL);
    carregaTextura(&texturasNave[1][0], "app/views/texturas/naves/nave2_1.png"); 
    carregaTextura(&texturasNave[1][1], "app/views/texturas/naves/nave2_2.png");
    carregaTextura(&texturasNave[1][2], "app/views/texturas/naves/nave2_3.png");
    carregaTextura(&texturasNave[1][3], "app/views/texturas/naves/nave2_4.png");
    carregaTextura(&texturasNave[0][0], "app/views/texturas/naves/nave1_1.png"); 
    carregaTextura(&texturasNave[0][1], "app/views/texturas/naves/nave1_2.png");
    carregaTextura(&texturasNave[0][2], "app/views/texturas/naves/nave1_3.png");
    carregaTextura(&texturasNave[0][3], "app/views/texturas/naves/nave1_4.png");


}

/*
 *  Responsável pela inicialização da parte gráfica e temporal da simulação. É a
 *  parte responsável por chamar o laço principal do programa.
 */
void inicializaParteGrafica(int argc, char *argv[]) {
    glutInit(&argc, argv);
    janela();
    carregaTexturas();
    glutReshapeFunc(redimensionaTela);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glutTimerFunc(intervaloIteracao, batalha, 0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutMainLoop();
}
