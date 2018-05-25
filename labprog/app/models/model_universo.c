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
#include <stdio.h>
#include <math.h>
#include "model_nave.h"
#include "model_planeta.h"
#include "model_projetil.h"
#include "model_universo.h"

/*** Declaração das funções ***/
void tamUniverso() {
   int i;
   float max = 0, temp_x, temp_y;

   for (i = 0; i < NUM_NAVES; i++) {
      temp_x = sqrt(naves[i].posicao.x * naves[i].posicao.x);
      temp_y = sqrt(naves[i].posicao.y * naves[i].posicao.y);
      if (temp_x > max) max = temp_x;
      if (temp_y > max) max = temp_y;
   }

   for (i = 0; i < NUM_PROJETEIS; i++) {
      temp_x = sqrt(projeteis[i].posicao.x * projeteis[i].posicao.x);
      temp_y = sqrt(projeteis[i].posicao.y * projeteis[i].posicao.y);
      if (temp_x > max) max = temp_x;
      if (temp_y > max) max = temp_y;
   }

   tamanhoUniverso = max;
}

void normalizaPosicao(Vetor *posicao) {
    if (posicao->x > tamanhoUniverso) posicao->x = -tamanhoUniverso;
    if (posicao->x < -tamanhoUniverso) posicao->x = tamanhoUniverso;
    if (posicao->y > tamanhoUniverso) posicao->y = -tamanhoUniverso;
    if (posicao->y < -tamanhoUniverso) posicao->y = tamanhoUniverso;
}
