#include<stdio.h>
#include<stdlib.h>

int main(){
int n, aux, par=0, num;
	printf("Digite um numero de digitos para a sequencia n:\n");
	scanf("%d", &n);
	printf("Insira a sequencia de numeros inteiros\n");
		while (n>0){
		n=n-1;
		scanf("%d", &num);
			if (num%2==0){
			par=num+par;
			}
}
	printf("A soma dos inteiros pares da sequencia introduzida é:\n %d\n\n",par); 
}
