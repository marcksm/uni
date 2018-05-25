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

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

void teclaPressionada(unsigned char tecla, int x, int y);
void teclaLiberada(unsigned char tecla, int x, int y);
void operacoesTecla();
void teclaEspecial(int tecla, int x, int y);
void teclaEspecialPressionada(int tecla, int x, int y);
void operacoesTeclaEspecial();

#endif
