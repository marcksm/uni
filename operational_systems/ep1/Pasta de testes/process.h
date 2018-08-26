/*******************************************************************************
*   ep1 - MAC0422 - Sistemas Operacionais
*       Professor: Daniel Batista
*
*   09/set/2016
*
*   por:
*   Matheus Tavares Bernardino,      nº USP: 9292987
*   Marcos Vinicius do Carmo Sousa,  nº USP: 9298274
*
*******************************************************************************/

#ifndef _PROCESS_H
#define _PROCESS_H

typedef struct process {
    char name[101];
    unsigned long int t0;
    unsigned long int dt;
    unsigned long int deadline;
    unsigned long int rt;
}process;



#endif
