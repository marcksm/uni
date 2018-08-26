#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef char *string;
char *leitura () {
   int n, ch, size;
   string line, nline;
   n = 0;
   size = 120;
   line = malloc (size + 1);
   while ((ch = getc (stdin)) != '\n'/* && ch != EOF*/) {
      if (n == size) {
         size = size * 2;
         nline = malloc (size + 1);
         strncpy (nline, line, n);
         free (line);
         line = nline;
      }
/*CRIAR  VETOR DE CARACT*/      if (ch==',') line[n++]=' ';
      if (ch >= 65 && ch <= 90) ch = tolower (ch);
      if ((ch > 64) || (ch >= 48 && ch <= 57) || ch == 0 || ch == 32 || ch == 10) line[n++] = ch;
   }
   if (n==0  /*&& ch == EOF*/) {
    free (line);
    return NULL;
    }
   line[n] = '\0';
   nline = malloc (n + 1);
   strcpy (nline, line);
   free (line);
return nline;
}
char *detec_extrac (char *nline) {
   int i, k, a;
   char *palavra;
   i = 0;
   a = 0;
   palavra = malloc (sizeof (nline));
   if (nline[0] == '\n') printf ("SIZE");
   while (nline[a] == ' ') a++;
   for (i = a, k = 0;(nline[i] != ' ' && nline[i] != '\0' && nline[i] != '\n'); k++, i++) palavra[k] = nline[i];
   i++;
   palavra[k]='\0';
   for (k = 0;nline[i] !='\0';k++){
      nline[k] = nline[i];
      i++;
   }
   nline[k++] = '\n';
   nline[k] = '\0';
return palavra;
}
int insercao (char **dicionario, char *palavra, int i) {
int j=0, k=0;
for(j=0;j<i;j++){
   if (strcmp(palavra,dicionario[j])==0){
      k=1;
   }

}
if(k==0){ dicionario[i]=palavra;}
if (k==1) i--;
return i;
}
void BubbleSort(char **dicionario, int tamanho){
  int i=0, j=0; 
  char *aux;
  aux = malloc(1000);
 for(j=tamanho-1;j>=1;j--){
      for(i=0; i<j; i++){
      if(strcmp(dicionario[i],dicionario[i+1])==0){
      }

         if(strcmp(dicionario[i],dicionario[i+1])>0){
            aux=dicionario[i]; 
            dicionario[i]=dicionario[i+1]; 
            dicionario[i+1]=aux; 
         } 
      }  
   } 
}
int main () {
   int i=0,k=0;
   char *nline, *palavra, **dicionario;
   dicionario = malloc (10000);
   nline = leitura ();
  if (nline==NULL) return 0;
    palavra = detec_extrac (nline);
     dicionario[i]=palavra;
      i++; 

   while (nline[0] != '\n'){
      palavra = detec_extrac (nline);
      i= insercao(dicionario,palavra,i);
     i++; 
   }
BubbleSort(dicionario,i);
   for(k=0;dicionario[k]!='\0';k++){
   printf ("-%s\n", dicionario[k]);
   }
return 0;
}
































