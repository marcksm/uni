/*  **************************************************************************  */
/*  Nome:  MARCOS VINICIUS DO CARMO SOUSA                                       */
/*  Numero  USP:  9298274		                                        */
/*  Exercício-­‐programa 1 						        */
/*  *************************************************************************** */
/*  gcc -Wall -ansi -pedantic -O2 -oep1 ep1.c  
for (pecpc=1; pecpc<m || (n-pecpc)%(m+1)!=0 ; pecpc++){
					n=n-pecpc;
					}
printf("%d peças em jogo, o computador retirará de 1 a %d peças\n",n,m);
*/
#include <stdio.h>
int main() {
int m=0, n=0, pec=0, pecpc=1, aux=1;
	
	printf("Bem vindo ao jogo do NIM!@2\n");
	printf("Insira um numero de peças para o jogo e o numero\n maximo de peças permitido para retirar em cada jogada\n");
	scanf("%d %d", &n, &m);
	printf("Neste jogo cada jogador jogam alternadamente,\nretirando  pelo  menos  1  e  no  máximo %d cada um\n", m);
	printf("Vence quem tirar as ultimas peças possiveis\n");
		if ((n%(m+1)) == 0){
			while (n>0){
				printf("%d peças restantes, remova de 1 a %d peças\n",n,m);
				scanf("%d",&pec);
				n=n-pec;
				pecpc=1;
				aux=1;
				
					while (pecpc<=m && aux == 1){
						if ((n-pecpc)%(m+1)==0){
						aux=0;
						pecpc--;
						}
									
					pecpc++;
					}
														
				printf("O computador removeu %d peças\n", pecpc);
				n=n-pecpc;
				}
		}
		else{
			while (n>0){
				pecpc=1;
				aux=1;
				while (pecpc<=m && aux == 1){
						if ((n-pecpc)%(m+1)==0){
						aux=0;
						pecpc--;
						}
								
					pecpc++;
					}
														
				printf("O computador removeu %d peças\n", pecpc);
				n=n-pecpc;
				
				printf("%d peças restantes, remova de 1 a %d peças\n",n,m);
				scanf("%d",&pec);
				n=n-pec;
					}
		
		}
}


