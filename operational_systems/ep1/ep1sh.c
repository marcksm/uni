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


#include <stdio.h> // fprintf
#include <stdlib.h> // exit, malloc, free, realloc, strtol
#include <unistd.h> //execve, fork
#include <sys/wait.h> //waitpid
#include <sys/stat.h> // chmod
#include <sys/types.h> // geteuid
#include <readline/readline.h> // readline
#include <readline/history.h> // add_history
#include <string.h> // strlen, strcpy
#include "StringSeparation.h" // wordsIn


char *command;
char **parameters;

/* Imprime na saida padrão de erro uma mensagem de erro. */
void error (char *message) {
    fprintf (stderr, "Error: %s\n", message);
}


/* Imprime na saida padrão de erro uma mensagem de erro e finaliza o programa
com status de saída igual a EXIT_FAILURE. */
void fatalError (char *message) {
    fprintf (stderr, "Error: %s\n", message);
    exit (EXIT_FAILURE);
}
/* Executa o comando chmod */
void chh (void) {
    long int pl;
    pl = strtol (parameters[1], 0, 8);
    chmod (parameters[2], pl);
}

/* Executa o comando id -u */
void idu (void) {
    uid_t id;
    id = geteuid();
    printf ("%d\n", id);

}

/*Imprime o texto promptText na saída padrão e lê um comando da entrada padrão,
com seus possíveis parametros, salvando-os respectivamente, nas variaveis
globais command e parameters. */
void read_command (char *promptText) {

    char *line_read = readline (promptText);
    if (line_read != NULL) {
        parameters = wordsIn (line_read);
        if (parameters != NULL) {
            add_history (line_read);
            command = malloc ((strlen (parameters[0]) + 1) * sizeof (char));
            if (command == NULL) fatalError ("Out of memory.");
            command = strcpy (command, parameters[0]);
        }
        free (line_read);
    }
    else {
        command = NULL;
        parameters = NULL;
    }
}


/* Libera a memoria alocada para as variaveis globais command e parameters. */
void freeGlobalVariables () {
    if (command != NULL) {
        free (command);
        command = NULL;
    }
    if (parameters != NULL) {
        for (int i = 0; parameters[i] != NULL; i++) free (parameters[i]);
        free (parameters);
        parameters = NULL;
    }
}


/* Retorna o uma string contendo o texto a ser usado no prompt. O texto é da
   forma "(dir/): ", onde dir é o diretorio de onde o programa foi lançado.*/
char *getPromptText () {
    char *dir = getcwd (NULL, 0);
    if (dir == NULL) fatalError ("Could't get current directory.");

    char *promptText = malloc ((strlen (dir) + 6) * sizeof (char));
    if (promptText == NULL) fatalError ("Out of memory.");
    promptText[0] = '(';
    int i = 1;
    while (dir[i-1] != '\0') {
        promptText[i] = dir[i-1];
        i++;
    }
    promptText[i] = '/';
    promptText[i+1] = ')';
    promptText[i+2] = ':';
    promptText[i+3] = ' ';
    promptText[i+4] = '\0';

    free (dir);

    return promptText;
}


/* A main inicializa o programa e permanece em um looping (até que o programa
seja morto), onde espera por um comando do usuário, o executa e, ao termino da
execução, aguarda um novo comando.*/
int main () {

    pid_t pid;
    char *promptText = getPromptText ();

    while (1) {

        read_command (promptText);

        if (command != NULL) {
            if (strcmp (command, "exit") == 0) break;
            else if (strcmp (command, "chmod") == 0) chh ();
            else if (strcmp (command, "id") == 0 && parameters[1] != NULL &&
                     strcmp (parameters[1], "-u") == 0) idu ();
            else {
                pid = fork ();

                if (pid == -1) {
                    error ("Failed at creating a child process.");
                }
                else if (pid == 0) {
                    execve (command, parameters, 0);
                    fatalError ("Failed at executing given command.");
                }
                else {
                    int status;
                    waitpid (pid, &status, 0);
                }
            }
            freeGlobalVariables ();
        }
    }


    clear_history ();
    freeGlobalVariables ();
    free (promptText);
    exit (EXIT_SUCCESS);
}
