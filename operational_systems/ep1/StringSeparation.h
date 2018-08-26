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

#ifndef _STRINGSEPARATION_H
#define _STRINGSEPARATION_H


/* This function receives a string text and returns a array containing all of
   the words in the string text. A word is a maximun sequence of characters
   other than space. Returns NULL if text is NULL or if text is exclusively a
   sequence of 0 or more spaces followed by '\0'.
*/
char ** wordsIn (char *text);


#endif
