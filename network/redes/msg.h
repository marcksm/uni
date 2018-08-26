#ifndef _MSG_H_INCLUDED   /* Include guard */
#define _MSG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções que devolvem as mensagens transmitidas pelo servidor

char *MSGstart ();

char *MSGend ();

char *MSGnamespace ();

char *MSGid ();

char *MSGnoop (double first, double second);

char *MSGidle (int w);

char *MSGlist (char *lista);

#endif
