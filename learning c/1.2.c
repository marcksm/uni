#include<stdio.h>
#include<stdlib.h>

int main(){

int num, aux=0;
	printf("Digite um numero n, inteiro positivo\n\n");
	scanf("%d",&num);
	
		while(num>0){
			aux=num+aux;
			num=num-1;
			}

	printf("A soma de dos n primeiros numeros inteiros positivos eh: %d\n\n",aux);
}

