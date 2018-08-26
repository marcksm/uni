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

#ifndef __VIEW_UNIVERSO_H__
#define __VIEW_UNIVERSO_H__

/*** Protótipos das funções ***/

/*
 * Função que desenha a textura do fundo na janela.
 */
void desenhaFundo();

/*
 * Desenha o texto na tela designando o ganhador do jogo.
 */
void desenhaFim();

/*
 * Desenha a barra de energia do jogador 1.
 */
void desenhaBarra1();

/*
 * Desenha a barra de energia do jogador 2.
 */
void desenhaBarra2();

void inicializaAudio(int argc, char *argv[]);

#endif
