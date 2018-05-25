#include<stdio.h>
#include<stdlib.h>

int main(){
int n, resul=1, count=n;
int aux=0;

	printf("Digite um numero n não negativo:\n\n");
	scanf("%d", &n);
	count=n;

			if (n>0){
			while (n>0){
			resul=n*resul;		
			n=n-1;
			}
		
		printf("%d! = %d\n", count, resul);
}
			
			if (n<0) {
			printf("VOCE NAO DIGITOU UM NUMERO N NAO NEGATIVO!!!\n");
			}
		
}
