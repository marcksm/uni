#include <stdio.h>
int main(){

int n, soma, i=1;

printf("Digite n sequencias de numeros inteiros\n");
scanf("%d",&n);

	while(n>0){
	printf("Digite a sequencia, e termine com 0\n");
		while(i!=0){
		scanf("%d",&i);
		if (i%2==0){
		soma=i+soma;
		}
		}
		printf("A soma dos pares dessa seq eh %d\n",soma);
		soma=0;
		i=1;
		n--;
	}	
	return 0;
}
	





