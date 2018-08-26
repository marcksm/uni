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
#include "batalha-espacial.h"
#include "models/model_auxiliar.h"
#include "models/model_nave.h"
#include "models/model_planeta.h"
#include "models/model_projetil.h"
#include "models/model_universo.h"
#include "views/view.h"
#include "views/view_nave.h"
#include "views/view_planeta.h"
#include "views/view_projetil.h"
#include "views/view_universo.h"
#include "controllers/controller.h"
#include <math.h>

/*** Protótipos das funções ***/

/*
 * Função da biblioteca glut, ao ser chamada força o fim
 * do Loop gráfico.
 */
void glutLeaveMainLoop();

/*** Declaração das funções ***/

/*
 * Define os raios do planeta, projéteis e nave com base no tamanho do universo.
 */
static void defineRaios() {
	defineRaioPlaneta();
	defineRaioProjetil();
	defineRaioNave();
}

/*
 *  Lê os parâmetros contidos no arquivo de entrada e com eles inicializa as naves,
 *  planetas, projéteis e variáveis relacionadas ao tempo.
 */
static void leEntrada(FILE *entrada) {
	/* Lê os atributos do planeta */
	leituraPlaneta(entrada);

	/* Lê o tempo de duração da simulação */
	fscanf(entrada, "%f", &tempoTotal);

	/* Lê os atributos das naves */
	leituraNaves(entrada);

	/* Lê a quantidade de projéteis e o seu tempo de vida */
	fscanf(entrada, "%d", &nProjeteis);
	fscanf(entrada, "%d", &tProjeteis);

	/* Em milissegundos */
	tempoTotal = 1000 * tempoTotal;
	leituraProjeteis(entrada);
	tamUniverso();
	defineRaios();
	tProjeteis = 1000 * tProjeteis;
}

int main(int argc, char *argv[]) {
	FILE *entrada;
	/* Verifica se a quantidade de parâmetros é a correta */
	if (argc != 3) {
		imprimeErro("Número inválido de parâmetros!\nUtilização:\
        ./batalha-espacial [arquivo de entrada] [intervalo de atualização]\n");
	}
	entrada = fopen(argv[1], "r");

	/* Verifica se o arquivo conseguiu ser aberto */
	if (entrada == NULL) {
		imprimeErro("Erro ao ler arquivo de entrada!\n");
	}

	/* Guarda o intervalo entre as iterações em milissegundos */
	intervaloIteracao = 1000 * atof(argv[2]);

	leEntrada(entrada);

	inicializaAudio(argc, argv);
	inicializaParteGrafica(argc, argv);

	fclose(entrada);

	free(naves);
	free(planeta);
	free(projeteis);

	return EXIT_SUCCESS;
}

void batalha(int t) {
	int i;

	glutKeyboardFunc(teclaPressionada);
	glutKeyboardUpFunc(teclaLiberada);
	glutSpecialFunc(teclaEspecial);
	glutSpecialUpFunc(teclaEspecialPressionada);

	if (glutGet(GLUT_ELAPSED_TIME) >= tempoTotal) {
		glutLeaveMainLoop();
		alutExit();
	}

	for (i = 0; i < NUM_NAVES; i++) {
		atualizaNave(i);
	}

	for (i = 0; i < NUM_PROJETEIS; i++) {
		if (projeteis[i].projetilAtivo == TRUE) atualizaProjetil(i);
	}

	operacoesTecla();
	operacoesTeclaEspecial();

	desenha();

	if (!colisao) glutTimerFunc(intervaloIteracao, batalha, 0);
}
