#include<stdio.h>
#include<stdlib.h>

int main(){
int x, n, aux=1, n2;


printf("Digite um numerador inteiro X e um expoente n não negativo \n");
scanf("%d %d", &x, &n);
n2=n;
		while (x!=0 and n>0){
		n=n-1;
		aux=x*aux;
		}
		printf("%d ^ %d é igual a %d\n",x, n2, aux);
 
		
}
		
	
