#include<stdio.h>
#include<stdlib.h>

int main(){

int num, quad;

printf("Digite uma sequencia de numeros, e para encerrar digite 0\n");
scanf("%d",&num);

	if (num!=0){

		while (num!=0) {
			quad=num*num;
		printf("O quadrado desse numero é: %d\n ",quad);
		printf("Digite uma sequencia de numeros, e para encerrar digite 0\n");
		scanf("%d",&num);	
		}
	}else 
	printf("Fim da sequencia de numeros\n");
	}



