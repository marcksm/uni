#ifndef _MAIL_H_INCLUDED   /* Include guard */
#define _MAIL_H_INCLUDED

#define LISTENQ 1
#define MAXDATASIZE 100
#define MAXLINE 4096

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "communication.h"


/*Função devolve a quantidade de emails do usuario logado*/
int getMAILqtd ();

/*Recebe um inteiro UID referente a um email e devolve o tamanho de arquivo
do email */
int getMAILsize(int uid);

/*Recebe um inteiro UID referente a um email e devolve a quantidade de linhas
do arquivo de email */
int getMAILlines(int uid);

/*Função recebe duas string e devolve uma que é a concateção
* das duas */
//char *STRINGconcatenate (char *str1, char *str2);

/*Função recebe um inteiro UID referente a um email e
* devolve uma string contendo o UID
* Ex: MAILuniqname(143);
    devolve uma string: 143 */
char *MAILuniqname(int uid);

/*Função recebe um inteiro UID referente a um email e
* devolve uma string contendo o UID e os parametros SEEN DELETE e LISTA
* Ex: MAILgetname(143);
*    devolve uma string: 143_1_0_0  */
char *MAILgetname (int uid);

/*Função recebe um inteiro UID referente a um email e
* devolve uma string contendo o caminho até o email do usuario
*Ex: getMAILpath (143);
*     devolve string: ./marcos/Maildir/cur/143_1_0_0   */
char *getMAILpath (int uid);

/* Função recebe um inteiro UID referente a um email,
* Um inteiro seen para o parametro SEEN do email
* Um inteiro delete para o parametro DELETE do email
* Um inteiro l para o parametro LISTA do email
* e atualiza o email com os parametros novos.
* Ex: MAILupdate (143, 1, 1, 1)
*  -> 143_1_1_1                  */
void MAILupdate (int uid_i, int seen, int delete, int l);

/* Função adiciona novos emails que estão na pasta @user/Maildir/new
  Criando uma UID e adicionando na uidlist e movendo o email para
  @user/Maildir/cur com os parametros corretos.
*/
void MAILnew (void);

/* Função recebe uma UID referente a um email e devolve um  vetor v[0,1,2]
* com o status referente a SEENv[0], DELETEv[1] e LIST v[2]*/
int *MAILstatus (int uid);

/* Função recebe um inteiro UID e muda o email para SEEN = 1
*/
void toMAILseen (int uid);

/* Função recebe um inteiro UID e muda o email para SEEN = 0
*/
void toMAILunseen (int uid);

/* Função recebe um inteiro UID e muda o email para DELETE = 1
*/
void toMAILdelete (int uid);

/* Função recebe um inteiro UID e muda o email para DELETE = 0
*/
void toMAILundelete (int uid);

/* Função recebe um inteiro UID e devolve 1 se email marcado como SEEN
 0 caso contrario */
int isMAILseen (int uid);

/* Função recebe um inteiro UID e devolve 1 se email marcado como UNSEEN
 0 caso contrario */
int isMAILunseen (int uid);

/* Função recebe um inteiro UID e devolve 1 se email marcado como DELETE
 0 caso contrario */
int isMAILdelete (int uid);



#endif
