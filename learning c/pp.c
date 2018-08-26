#include<stdio.h>
#include<stdlib.h>

int main(){
int p, n=1, aux;

	printf("Digite um numero para verificar se é primo\n\n");
	p=2;
		
		while(p>n){
		n=n+1;
			if (p%n == 0 and p != n){
			
			}
			if (p%n == 0 and p/n == 1){
			
			printf("O numero %d é primo!\n\n",p);
			}
			if (p >= 10000){
			p=0;
			}
		p=p+1;
			
}
}
