#include<stdio.h>
#include<stdlib.h>

int main(){
	
int num, aux=1, aux2;

	printf("Digite um numero inteiro n:\n");
	scanf("%d",&num);
		printf("Os n primeiros numeros inteiros positivos ímpares são: ");
		while(num>0){
			num=num-1;
			printf("%d,",aux);
			aux=aux+2;
			}
printf("\n\n");			

}
