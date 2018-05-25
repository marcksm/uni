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
#include <math.h>
#include "model_auxiliar.h"
#include "model_fisica.h"
#include "model_planeta.h"
#include "model_projetil.h"
#include "model_universo.h"
#include "../views/view_nave.h"

#define ESCALA_RAIO_PROJETIL tamanhoUniverso * ESCALA_PROJETIL * 4
#define ESCALA_VELOCIDADE_PROJETIL tamanhoUniverso * 0.1 * ESCALA_NAVE
#define ESCALA_POSICAO_PROJETIL tamanhoUniverso * ESCALA_NAVE

int massa;

/*** Declaração das funções ***/
void leituraProjeteis(FILE *entrada) {
    int i;

    projeteis = mallocSafe(NUM_PROJETEIS * sizeof(Projetil));
    for (i = 0; i < nProjeteis; i++) {
        fscanf(entrada, "%f", &projeteis[i].massa);
        fscanf(entrada, "%f %f", &projeteis[i].posicao.x, &projeteis[i].posicao.y);
        fscanf(entrada, "%f %f", &projeteis[i].velocidade.x, &projeteis[i].velocidade.y);
        inicializaVetor(&projeteis[i].aceleracao);
        inicializaVetor(&projeteis[i].forca);
        projeteis[i].tempo = glutGet(GLUT_ELAPSED_TIME);
        projeteis[i].projetilAtivo = TRUE;
        massa = projeteis[i].massa;
    }
}

void defineRaioProjetil() {
	int i;    

	for (i = 0; i < NUM_PROJETEIS; i++){
        projeteis[i].raio = ESCALA_RAIO_PROJETIL; 
    }
}

void criaProjetil(Nave nave) {
    int i;

    for (i = 0; i < NUM_PROJETEIS; i++) {
        if (projeteis[i].projetilAtivo == FALSE) break;
    }

    if (i == NUM_PROJETEIS) return;

    projeteis[i].projetilAtivo = TRUE;
    projeteis[i].tempo = glutGet(GLUT_ELAPSED_TIME);
    projeteis[i].posicao.x = nave.posicao.x + ESCALA_POSICAO_PROJETIL * seno(nave.angulo);
    projeteis[i].posicao.y = nave.posicao.y + ESCALA_POSICAO_PROJETIL * cosseno(nave.angulo);
    projeteis[i].velocidade.x = nave.velocidade.x + ESCALA_VELOCIDADE_PROJETIL * seno(nave.angulo);
    projeteis[i].velocidade.y = nave.velocidade.y + ESCALA_VELOCIDADE_PROJETIL * cosseno(nave.angulo);
    projeteis[i].angulo = nave.angulo;
}

void atualizaTempoProjeteis() {
    int i;

    for (i = 0; i < NUM_PROJETEIS; i++) {
        if (projeteis[i].projetilAtivo == TRUE &&
            (glutGet(GLUT_ELAPSED_TIME) - projeteis[i].tempo) > tProjeteis) {
                projeteis[i].projetilAtivo = FALSE;
            }
        }
    }

    /*
    *  Calcula a força resultante entre o projétil e os demais corpos do universo.
    */
    static void atualizaForcaResultanteProjetil(int i) {
        int j;
        Vetor temp;

        inicializaVetor(&projeteis[i].forca);

        for (j = 0; j < NUM_NAVES; j++) {
            temp = calculaForca(projeteis[i].massa, projeteis[i].posicao, naves[j].massa, naves[j].posicao);
            projeteis[i].forca.x += temp.x;
            projeteis[i].forca.y += temp.y;
        }

        temp = calculaForca(projeteis[i].massa, projeteis[i].posicao, planeta->massa, planeta->posicao);
        projeteis[i].forca.x += temp.x;
        projeteis[i].forca.y += temp.y;

        for (j = 0; j < nProjeteis; j++) {
            if (i != j && projeteis[j].projetilAtivo == TRUE) {
                temp = calculaForca(projeteis[i].massa, projeteis[i].posicao, projeteis[j].massa, projeteis[j].posicao);
                projeteis[i].forca.x += temp.x;
                projeteis[i].forca.y += temp.y;
            }
        }

    }

    /*
    *  Atualiza a aceleração do projétil com base na força resultante sendo aplicada neste.
    */
    static void atualizaAceleracaoProjetil(Projetil *projetil) {
        projetil->aceleracao = calculaAceleracao(projetil->forca, projetil->massa);
    }

    /*
    *  Atualiza a velocidade do projétil com base na aceleraçao deste.
    */
    static void atualizaVelocidadeProjetil(Projetil *projetil) {
        Vetor deltaV;

        inicializaVetor(&deltaV);
        deltaV = calculaVelocidade(projetil->aceleracao);

        projetil->velocidade.x += deltaV.x;
        projetil->velocidade.y += deltaV.y;
    }

    /*
    *  Atualiza a posição do projétil com base na velocidade deste.
    */
    static void atualizaPosicaoProjetil(Projetil *projetil) {
        Vetor deltaS;

        inicializaVetor(&deltaS);

        deltaS = calculaPosicao(projetil->velocidade);

        projetil->posicao.x += deltaS.x;
        projetil->posicao.y += deltaS.y;

        normalizaPosicao(&projetil->posicao);
    }

    void atualizaProjetil(int i) {
        atualizaTempoProjeteis();
        atualizaForcaResultanteProjetil(i);
        atualizaAceleracaoProjetil(&projeteis[i]);
        atualizaVelocidadeProjetil(&projeteis[i]);
        atualizaPosicaoProjetil(&projeteis[i]);
    }

    Vetor posicaoRelativaProjetil(int i) {
        float x, y;
        Vetor novaPosicao;

        x = projeteis[i].posicao.x;
        y = projeteis[i].posicao.y;

        novaPosicao.x = (float) x / tamanhoUniverso;
        novaPosicao.y = (float) y / tamanhoUniverso;

        return novaPosicao;
    }
