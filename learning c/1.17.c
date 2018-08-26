#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int main(){
int dec=0, bin=0, result=0, aux=0,aux2=0, v[1000], i=0, res=0;

	printf("Digite um numero com base decimal\n");
	scanf("%d", &dec);
	bin=dec;
	for (i=0;i<1000;i++){
	v[i]=0;
	}
	i=0;
	while (dec>0){
	
		aux=dec%2;	

		if (aux == 1){
		v[i]=1;
		
		}
		if (aux == 0){
		v[i]=0;
		
		}
		dec=dec/2;
		i++;
		aux2++;
		}
printf("\n");
	for (i=i-1;i>=0;i--){
	printf("%d",v[i]);
	}
printf("\n");
}

