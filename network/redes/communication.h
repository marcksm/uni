#ifndef _COMMUNICATION_H_INCLUDED   /* Include guard */
#define _COMMUNICATION_H_INCLUDED

#define LISTENQ 1
#define MAXDATASIZE 100
#define MAXLINE 4096

#include "msg.h"
#include <string.h>
#include "user.h"

int connfd;

#define MAXSIZE 5000000

char sendbuffer[MAXSIZE];

/*Função reseta o buffer de mensagens sendbuffer*/
void SENDreset ();

/*Função adiciona uma linha ao buffer de mensagens*/
void SENDinsertline (char *s);

/*Função recebe um commando do cliente e faz a autenticação*/
void CLIENTauthenticate (char sm[][MAXLINE + 1]);

/*Função recebe um commando do cliente e faz o login*/
void CLIENTlogin (char sm[][MAXLINE + 1]);

/*Função recebe um commando do cliente e faz o logout*/
void CLIENTlogout (char sm[][MAXLINE + 1]);

/*Função devolve o id do usuario logado*/
int CLIENTcurrent ();

/*Função recebe um commando do cliente e lista INBOX*/
void CLIENTlist (char sm[][MAXLINE + 1]);

/*Função recebe um commando do cliente e responde em idle*/
void CLIENTidle (char sm[][MAXLINE + 1]);

/*Função recebe um commando do cliente e responde conforme*/
void CLIENTnamespace (char sm[] [MAXLINE+1]);

/*Função recebe um commando do cliente e responde conforme*/
void CLIENTid (char sm[] [MAXLINE+1]);

/*Função recebe um commando do cliente e responde conforme*/
void CLIENTnoop (char sm[] [MAXLINE+1]);

/*Função recebe um commando do cliente e responde conforme*/
void CLIENTdone (char sm[] [MAXLINE+1]);

/*Função recebe um commando do cliente e responde conforme*/
void CLIENTEselect (char sm[][MAXLINE + 1]);

/*Função recebe um commando e o interpreta*/
void CLIENTrequest (char sm[][MAXLINE + 1]);

/*Função le do socket e devolve quantidade de chars lidos*/
int CLIENTread (char sm [][MAXLINE+1]);

/*Função escreve no */
void CLIENTwrite ();

/*Função private*/
void split (char s[], char ss[][MAXLINE + 1]);

#endif
