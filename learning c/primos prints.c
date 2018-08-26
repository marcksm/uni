#include<stdio.h>
#include<stdlib.h>

int main(){
int p, n=1, aux;

	printf("Digite um numero para verificar se é primo\n\n");
	scanf("%d",&p);
		
		while(p>n){
		n=n+1;
			if (p%n == 0 and p != n){
			printf("O numero NAO é primo!\n\n");
			p=(n-10);
			}
			if (p%n == 0 and p/n == 1){
			
			printf("O numero é primo!\n\n");
			}
			
}
}
