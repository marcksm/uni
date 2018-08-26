#ifndef _USER_H_INCLUDED   /* Include guard */
#define _USER_H_INCLUDED

#include "mail.h"

/* Função que devolve todos os emails do usuario logado
 é um vetor int v[][] */
int *getUSERmails ();

/* Função devolve o nome do usuario logado,
* devolve NULL caso não esteja logado */
char *getUSERname (int us_id);

/* Função cria as pastas e subpastas do Maildir para o usuario logado
* caso ele não possua */
void USERinit ();

/* Função desloga o usuario */
void USERlogout ();

/* Função loga o usuario */
int USERlogin(char *username, char *password);

/* Função recebe um inteiro id e seta o user_id para o do
* usuario especificado no id */
void setUSERcurrent (int id);

/* Função devolve o id do usuario logado, -1 se não estive */
int getUSERcurrent ();

/*Função devolve o caminho da pasta do usuario logado
* exemplo:   ./marcos     */
char *getUSERpath ();

#endif
