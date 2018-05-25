#include<stdio.h>

int main(){
int hip=1,cat1=1,cat2=1,n,aux1,aux2,aux3;


printf("Digite N numeros ,para imprimir as n primeiras hipotenusas inteiras\n");
scanf("%d",&n);

	while(hip<=n){
	if((hip*hip)==(cat1*cat1)+(cat2*cat2)){
	printf("%d\n",hip);
	
	}
		while(cat2<=n){
		if((hip*hip)==(cat1*cat1)+(cat2*cat2) && (aux1==1)){
		printf("%d\n",hip);
		aux1=0;
		}
			while(cat1<=n){
			if((hip*hip)==(cat1*cat1)+(cat2*cat2) && (aux1==1)){
			printf("%d\n",hip);
			aux1=0;
			}
			cat1++;
			}
		cat2++;
		cat1=1;
		}
	hip++;	
	cat2=1;
	aux1=1;
	}
}
