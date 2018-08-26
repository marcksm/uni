#include<stdio.h>

int main(){

int n,k=2,primo,mult=0,aux=0;

printf("Insira um numero inteiro positivo\n");
scanf("%d",&n);

aux=n;
	while(aux>1){
		while (aux%k==0){
		aux=aux/k;
		mult++;
		}
		if(mult!=0){	
		printf("%d, com multiplicidade %d\n",k,mult);
		}
	k++;
	mult=0;
	}
}
