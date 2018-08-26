#include<stdio.h>
#include<stdlib.h>

int main(){

int n, triang, result, aux=1;

	printf("Digite um numero para verificar se ele é triangular:\n");
	scanf("%d",&n);
	
		while (n/aux != 1){
		aux=aux+1;
			if (n%aux == 0 and n%(aux+1) == 0 and n%(aux+2) == 0){
				printf("O numero %d é triangular!\n\n",n);
				n=1;
				aux=1;
				}
	
			
		}
		if (n!=1){
			printf("Não é triangular!\n\n");
			}
		
	}
