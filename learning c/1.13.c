#include<stdio.h>
#include<stdlib.h>

int main(){
int n=0, aux=1, result;

printf("Digite um numero inteiro positivo:\n");
scanf("%d", &n);
	while (n>aux){
	if ((aux+(aux+1)+(aux+2) == n)){
	printf("O numero é perfeito!\n");
	result=1;	
	}
	
	if (aux+1>=n and result!=1){
	printf("Não é perfeito\n");
	}
	aux++;
}
}
	
