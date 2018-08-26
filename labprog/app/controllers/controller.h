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

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

/*** Protótipos das funções ***/

/*
 * Recebe uma tecla e a pressiona.
 */
void teclaPressionada(unsigned char tecla, int x, int y);

/*
 * Recebe uma tecla pressionada, e a libera.
 */
void teclaLiberada(unsigned char tecla, int x, int y);

/*
 * Controla o funcionamento das teclas não-especiais quando estas são pressionadas.
 */
void operacoesTecla();

/* 
 * Recebe uma tecla especial e a pressiona.
 */
void teclaEspecial(int tecla, int x, int y);

/*
 * Recebe uma tecla pressionada, e a libera.
 */
void teclaEspecialPressionada(int tecla, int x, int y);

/*
 * Controla o funcionamento das teclas especiais quando estas são pressionadas.
 */
void operacoesTeclaEspecial();

#endif
