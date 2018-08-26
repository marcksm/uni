#include<stdio.h>
#include<stdlib.h>

int main(){
int n,j,m,i,x=1;

	printf("Insira 3 numeros ");
	scanf("%d %d %d",&n, &m, &j);
	for (x=1; x<n; x++){
	if (x%m == j%m){
	printf("O numero %d é congruente módulo %d a %d\n",x,m,j);
	}
	}
}
