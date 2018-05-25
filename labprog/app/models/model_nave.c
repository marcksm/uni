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
#include <math.h>
#include "model_auxiliar.h"
#include "model_fisica.h"
#include "model_nave.h"
#include "model_planeta.h"
#include "model_projetil.h"
#include "model_universo.h"
#include "../views/view_nave.h"

#define FORCA_PROPULSAO 1.0e7
#define ESCALA_RAIO_NAVE 0.4 * tamanhoUniverso * ESCALA_NAVE


/*** Declaração das funções ***/
void leituraNaves(FILE *entrada) {
    int i;

    naves = mallocSafe(NUM_NAVES * sizeof(Nave));
    for (i = 0; i < NUM_NAVES; i++) {
        fscanf(entrada, "%s", naves[i].nome);
        fscanf(entrada, "%f", &naves[i].massa);
        fscanf(entrada, "%f %f", &naves[i].posicao.x, &naves[i].posicao.y);
        fscanf(entrada, "%f %f", &naves[i].velocidade.x, &naves[i].velocidade.y);
        inicializaVetor(&naves[i].aceleracao);
        inicializaVetor(&naves[i].forca);
        naves[i].propulsaoAtivada = FALSE;
        naves[i].energia = 100.0;
    }
}

void defineRaioNave() {
	int i;
	for (i = 0; i <  NUM_NAVES; i++){
        	naves[i].raio = ESCALA_RAIO_NAVE;
    	}
}

/*
*  Calcula a força resultante entre a nave e os demais corpos do universo.
*/
static void atualizaForcaResultanteNave(int i) {
    int j;
    Vetor temp;

    inicializaVetor(&temp);
    inicializaVetor(&naves[i].forca);

    for (j = 0; j < NUM_NAVES; j++) {
        if(i != j)  {
            temp = calculaForca(naves[i].massa, naves[i].posicao, naves[j].massa, naves[j].posicao);
            naves[i].forca.x += temp.x;
            naves[i].forca.y += temp.y;
        }
    }

    temp = calculaForca(naves[i].massa, naves[i].posicao, planeta->massa, planeta->posicao);
    naves[i].forca.x += temp.x;
    naves[i].forca.y += temp.y;

    for (j = 0; j < nProjeteis; j++) {
        if (projeteis[j].projetilAtivo == TRUE) {
            temp = calculaForca(naves[i].massa, naves[i].posicao, projeteis[j].massa, projeteis[j].posicao);
            naves[i].forca.x += temp.x;
            naves[i].forca.y += temp.y;
        }
    }

    if (naves[i].propulsaoAtivada == TRUE) {
        naves[i].forca.x += FORCA_PROPULSAO * seno(naves[i].angulo);
        naves[i].forca.y += FORCA_PROPULSAO * cosseno(naves[i].angulo);
    }
}

static void colisaoNaves(int i) {
    int j;
    for (j = 0; j < NUM_NAVES; j++) {
        if (i != j)  {
            if (calculaColisao(naves[i].raio, naves[i].posicao, naves[j].raio, naves[j].posicao)) colisao = TRUE;
        }
    }

    if (calculaColisao(naves[i].raio, naves[i].posicao, planeta->raio, planeta->posicao)) colisao = TRUE;

    for (j = 0; j < NUM_PROJETEIS; j++) {
        if (projeteis[j].projetilAtivo == TRUE) {
            if (calculaColisao(naves[i].raio, naves[i].posicao, projeteis[j].raio, projeteis[j].posicao)) {
            	naves[i].energia -= 10;
                projeteis[j].projetilAtivo = FALSE;
            }
            if (naves[i].energia <= 0) colisao = TRUE;
        }
    }
}

/*
*  Atualiza a aceleração da nave com base na força resultante sendo aplicada nesta.
*/
static void atualizaAceleracaoNave(Nave *nave) {
    nave->aceleracao = calculaAceleracao(nave->forca, nave->massa);
}

/*
*  Atualiza a velocidade da nave com base na aceleraçao desta.
*/
static void atualizaVelocidadeNave(Nave *nave) {
    Vetor deltaV;

    deltaV = calculaVelocidade(nave->aceleracao);

    nave->velocidade.x += deltaV.x;
    nave->velocidade.y += deltaV.y;
}

/*
*  Atualiza a posição da nave com base na velocidade desta.
*/
static void atualizaPosicaoNave(Nave *nave) {
    Vetor deltaS;

    deltaS = calculaPosicao(nave->velocidade);

    nave->posicao.x += deltaS.x;
    nave->posicao.y += deltaS.y;

    normalizaPosicao(&nave->posicao);
}

void atualizaNave(int i) {
    colisaoNaves(i);
    atualizaForcaResultanteNave(i);
    atualizaAceleracaoNave(&naves[i]);
    atualizaVelocidadeNave(&naves[i]);
    atualizaPosicaoNave(&naves[i]);
}

Vetor posicaoRelativaNave(int i) {
    float x, y;
    Vetor novaPosicao;

    x = naves[i].posicao.x;
    y = naves[i].posicao.y;

    novaPosicao.x = (float) x / tamanhoUniverso;
    novaPosicao.y = (float) y / tamanhoUniverso;

    return novaPosicao;
}
