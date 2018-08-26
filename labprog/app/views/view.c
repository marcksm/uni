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
#include <SOIL/SOIL.h>
#include "../batalha-espacial.h"
#include "../controllers/controller.h"
#include "../models/model_nave.h"
#include "../models/model_universo.h"
#include "view_nave.h"
#include "view_planeta.h"
#include "view_projetil.h"
#include "view_universo.h"
#include "view.h"

/*** Macros definidas ***/
#define IMAGEM_NULL "app/views/texturas/naves/null.png"
#define IMAGEM_FUNDO "app/views/texturas/universo/fundo.jpg"
#define IMAGEM_NAVE1_1 "app/views/texturas/naves/nave1_1.png"
#define IMAGEM_NAVE1_2 "app/views/texturas/naves/nave1_2.png"
#define IMAGEM_NAVE1_3 "app/views/texturas/naves/nave1_3.png"
#define IMAGEM_NAVE1_4 "app/views/texturas/naves/nave1_4.png"
#define IMAGEM_NAVE2_1 "app/views/texturas/naves/nave2_1.png"
#define IMAGEM_NAVE2_2 "app/views/texturas/naves/nave2_2.png"
#define IMAGEM_NAVE2_3 "app/views/texturas/naves/nave2_3.png"
#define IMAGEM_NAVE2_4 "app/views/texturas/naves/nave2_4.png"
#define IMAGEM_PLANETA "app/views/texturas/planeta/planeta.png"
#define IMAGEM_PROJETIL "app/views/texturas/projetil/projetil.png"
#define IMAGEM_BARRA_0L "app/views/texturas/hud/0l.png"
#define IMAGEM_BARRA_10L "app/views/texturas/hud/10l.png"
#define IMAGEM_BARRA_20L "app/views/texturas/hud/20l.png"
#define IMAGEM_BARRA_30L "app/views/texturas/hud/30l.png"
#define IMAGEM_BARRA_40L "app/views/texturas/hud/40l.png"
#define IMAGEM_BARRA_50L "app/views/texturas/hud/50l.png"
#define IMAGEM_BARRA_60L "app/views/texturas/hud/60l.png"
#define IMAGEM_BARRA_70L "app/views/texturas/hud/70l.png"
#define IMAGEM_BARRA_80L "app/views/texturas/hud/80l.png"
#define IMAGEM_BARRA_90L "app/views/texturas/hud/90l.png"
#define IMAGEM_BARRA_100L "app/views/texturas/hud/100l.png"
#define IMAGEM_BARRA_0R "app/views/texturas/hud/0r.png"
#define IMAGEM_BARRA_10R "app/views/texturas/hud/10r.png"
#define IMAGEM_BARRA_20R "app/views/texturas/hud/20r.png"
#define IMAGEM_BARRA_30R "app/views/texturas/hud/30r.png"
#define IMAGEM_BARRA_40R "app/views/texturas/hud/40r.png"
#define IMAGEM_BARRA_50R "app/views/texturas/hud/50r.png"
#define IMAGEM_BARRA_60R "app/views/texturas/hud/60r.png"
#define IMAGEM_BARRA_70R "app/views/texturas/hud/70r.png"
#define IMAGEM_BARRA_80R "app/views/texturas/hud/80r.png"
#define IMAGEM_BARRA_90R "app/views/texturas/hud/90r.png"
#define IMAGEM_BARRA_100R "app/views/texturas/hud/100r.png"
#define FIM_EMPATE "app/views/texturas/win/empate.png"
#define FIM_NAVE1 "app/views/texturas/win/Nave1W.png"
#define FIM_NAVE2 "app/views/texturas/win/Nave2W.png"

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
    carregaTextura(&texturas[0], IMAGEM_FUNDO);
    carregaTextura(&texturas[1], IMAGEM_PLANETA);
    carregaTextura(&texturas[2], IMAGEM_PROJETIL);

	carregaTextura(&texturasNave[0][0], IMAGEM_NAVE1_1);
	carregaTextura(&texturasNave[0][1], IMAGEM_NAVE1_2);
	carregaTextura(&texturasNave[0][2], IMAGEM_NAVE1_3);
	carregaTextura(&texturasNave[0][3], IMAGEM_NAVE1_4);
	carregaTextura(&texturasNave[0][4], IMAGEM_NULL);

    carregaTextura(&texturasNave[1][0], IMAGEM_NAVE2_1);
    carregaTextura(&texturasNave[1][1], IMAGEM_NAVE2_2);
    carregaTextura(&texturasNave[1][2], IMAGEM_NAVE2_3);
    carregaTextura(&texturasNave[1][3], IMAGEM_NAVE2_4);
    carregaTextura(&texturasNave[1][4], IMAGEM_NULL);

    carregaTextura(&texturasBarra[0][0], IMAGEM_BARRA_0L);
    carregaTextura(&texturasBarra[0][1], IMAGEM_BARRA_10L);
    carregaTextura(&texturasBarra[0][2], IMAGEM_BARRA_20L);
    carregaTextura(&texturasBarra[0][3], IMAGEM_BARRA_30L);
    carregaTextura(&texturasBarra[0][4], IMAGEM_BARRA_40L);
    carregaTextura(&texturasBarra[0][5], IMAGEM_BARRA_50L);
    carregaTextura(&texturasBarra[0][6], IMAGEM_BARRA_60L);
    carregaTextura(&texturasBarra[0][7], IMAGEM_BARRA_70L);
    carregaTextura(&texturasBarra[0][8], IMAGEM_BARRA_80L);
    carregaTextura(&texturasBarra[0][9], IMAGEM_BARRA_90L);
    carregaTextura(&texturasBarra[0][10], IMAGEM_BARRA_100L);

	carregaTextura(&texturasBarra[1][0], IMAGEM_BARRA_0R);
    carregaTextura(&texturasBarra[1][1], IMAGEM_BARRA_10R);
    carregaTextura(&texturasBarra[1][2], IMAGEM_BARRA_20R);
    carregaTextura(&texturasBarra[1][3], IMAGEM_BARRA_30R);
    carregaTextura(&texturasBarra[1][4], IMAGEM_BARRA_40R);
    carregaTextura(&texturasBarra[1][5], IMAGEM_BARRA_50R);
    carregaTextura(&texturasBarra[1][6], IMAGEM_BARRA_60R);
    carregaTextura(&texturasBarra[1][7], IMAGEM_BARRA_70R);
    carregaTextura(&texturasBarra[1][8], IMAGEM_BARRA_80R);
    carregaTextura(&texturasBarra[1][9], IMAGEM_BARRA_90R);
    carregaTextura(&texturasBarra[1][10], IMAGEM_BARRA_100R);

	carregaTextura(&texturasFim[0], FIM_EMPATE);
	carregaTextura(&texturasFim[1], FIM_NAVE1);
	carregaTextura(&texturasFim[2], FIM_NAVE2);
}

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

void desenha() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	desenhaFundo();
	desenhaPlaneta();

	desenhaNaves();

	desenhaProjeteis();
	desenhaBarra1();
	desenhaBarra2();

	if (naves[0].energia == 0 || naves[1].energia == 0) desenhaFim();

	glutSwapBuffers();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glutPostRedisplay();
}
