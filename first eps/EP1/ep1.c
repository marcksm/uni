#include <stdio.h>
int main() {
int m=0, n=0, pec=0, pecpc=1, aux=1, aux2=0;
/*
Variável n == Numero de peças inicial

Variável m == Numero maximo de peças que 
	é permitido retirar em cada jogada

Variável pec == Numero de peças removidas
	pelo jogador

Variável pecpc == Numero de peças retiradas
	pelo Super Computador

Variável aux == Auxiliador das funções logicas

Variavel aux2 == Utilizada como parametro para
	verificar se a jogada é ilícita(pec>m)
	
*/

/* Instruções para o usuario sobre o jogo */	
printf("Bem vindo ao jogo do NIM!\n\n\n");
printf("Você enfrentará o Super computador em uma acirrada batalha");
printf(" de puro intelecto!\n");
printf("Inicie inserindo o número de peças para o jogo e o número\n");
printf("máximo de peças permitido retirar em cada jogada\n");
scanf("%d %d", &n, &m);
printf("Neste jogo cada jogador joga alternadamente,retirando\npelo");
printf(" menos 1 e no máximo %d peças por turno\n", m);
printf("Vence quem tirar as últimas peças possíveis!\n\n");

	if ((n%(m+1)) == 0){
	/*Esta condição implica na decisão do computador iniciar ou não o jogo,
	caso ela for verdadeira o computador deixa o jogador iniciar o jogo, 
	para que sua estrategia vencedora sempre aconteça.*/
	printf("O Super Computador gentilmente concedeu-lhe"); 
	printf(" a honra de iniciar o jogo!\n\n");
		while (n>0 && aux2==0){
		/*
		Esta condição de loop, continuará até que todas as 
		peças sejam removidas e que o jogador não trapaceie
		*/
		printf("%d peças restantes, remova de 1 a %d peças\n",n,m);
		scanf("%d",&pec);
		n=n-pec;
		/*
		Expressão que remove peças do jogador do total de peças
		*/
			if (pec == 1){
			/*
			Condição que exprime a quantidade de peças removidas
			pelo jogador. Ela também mantém a ortografia correta
			no jogo, garantindo a concordância nas frases.
			Ex: 1 peça
			Ex: 2 peças
			*/
			printf("Você removeu %d peça!\n",pec);
			}
			else{
			printf("Você removeu %d peças!\n",pec);
			}
			if (pec > m || pec==0){
			/*
			Verifica se o jogador é um trapaceiro, pois se remover
			mais peças que o permitido ou nenhuma, a variavel aux2
			assumirá 1 e denunciará o jogador.
			*/
			aux2=1;
			}
		pecpc=1;
		aux=1;
		/*
		Reseta as variaveis de comparação
		*/			
			while (pecpc<=m && aux == 1 && aux2==0){
			/*
			Esse  loop coordena a estratégia vencedora
			do Super Computador, tentando deixar um
			numero multiplo de m+1. Caso isso não seja
			possível, deverá tirar o maior numero de peças
			*/
				if ((n-pecpc)%(m+1)==0){
				aux=0;
				pecpc--;
				}
								
			pecpc++;
			}
			if(aux==0){
			/*
			Caso o jogador trapaceie, as expressões abaixo não 
			serão mostradas
			*/									
				if (pecpc == 1){
				/*
				Condição que exprime a quantidade de peças removidas
				pelo Super Computador. Ela também mantém a ortografia
				correta	no jogo, garantindo a concordância nas frases.
				Ex: 1 peça
				Ex: 2 peças
				*/		
				printf("O Super Computador removeu");
				printf(" %d peça!\n",pecpc);
				}
				else{
				printf("O Super Computador removeu");
				printf(" %d peças!\n",pecpc);
				}
			}
		n=n-pecpc;
		/*
		Expressão que remove peças do Super Computador
		do total de peças
		*/
		
		}
	}
	else
	{
	/*
	Esta condição acontece caso a primeira falhe, para
	que o Super Computador garanta a estrategia vencedora.
	*/
	printf("O Super Computador iniciou o jogo!\n");
		while (n>0 && aux2==0){
		/*
		Esta condição de loop, continuará até que todas as 
		peças sejam removidas e que o jogador não trapaceie
		*/
		pecpc=1;
		aux=1;
		/*
		Reseta as variaveis de comparação
		*/
			while (pecpc<=m && aux == 1){
			/*
			Esse  loop coordena a estratégia vencedora
			do Super Computador, tentando deixar um
			numero multiplo de m+1. Caso isso não seja
			possível, deverá tirar o maior numero de peças
			*/			
				if ((n-pecpc)%(m+1)==0){
				aux=0;
				pecpc--;
				}
							
			pecpc++;
			}
			if (pecpc == 1){
			/*
			Condição que exprime a quantidade de peças removidas
			pelo Super Computador. Ela também mantém a ortografia
			correta	no jogo, garantindo a concordância nas frases.
			Ex: 1 peça
			Ex: 2 peças
			*/		
			printf("O Super Computador removeu %d peça!\n",pecpc);
			}
			else{
			printf("O Super Computador removeu %d peças!\n",pecpc);
			}									
		n=n-pecpc;
		/*
		Expressão que remove peças do Super Computador
		do total de peças
		*/
			if (n>0 && aux2==0){
			/*
			Caso o jogador trapaceie, as expressões abaixo não 
			serão mostradas
			*/													
			printf("%d peças restantes, remova de 1 a",n);
			printf(" %d peças\n",m);
			scanf("%d",&pec);
				if (pec == 1){
				/*
				Condição que exprime a quantidade de peças
				removidas pelo jogador. Ela também mantém a
				ortografia correta no jogo, garantindo a 
				concordância nas frases.
				Ex: 1 peça
				Ex: 2 peças
				*/		
				printf("Você removeu %d peça!\n",pec);
				}
				else{
				printf("Você removeu %d peças!\n",pec);
				}
				if (pec > m || pec==0){
				/*
				Verifica se o jogador é um trapaceiro, pois se
				remover mais peças que o permitido ou nenhuma,
				a variavel aux2 assumirá 1 e denunciará o 
				jogador.
				*/
				aux2=1;
				}
			}
		n=n-pec;
		/*
		Expressão que remove peças do jogador do total de peças
		*/
		}
			
		
	}
/*
Exprime o resultado do jogo
*/
	if(aux2==0){
	printf("O Super Computador venceu!\n");
	}
	else{
	printf("Você trapaciou, TEJE PRESO!\n");
	}	
return 0;
}



