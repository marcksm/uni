#include<stdio.h>
#include<stdlib.h>

int main(){
int dec=1, bin=0, n=0, result=0, aux=0;

	printf("Digite um numero na base binaria:\n");
	scanf("%d",&bin);
	aux=bin;
	while (aux>=1){
	
	if (aux%10 == 2 or aux%10 == 3 or aux%10 == 4 or aux%10 == 5 or aux%10 == 6 or aux%10 == 7 or aux%10 == 8 or aux%10 == 9){
	printf("BINARIO EH 1 OU 0 SEU BURRO\n");
		
	}
	aux=aux/10;

	}
	while (bin>0){
	
	
	if (bin%10 == 1){
	dec=2*dec;
	result=dec+result;
	}
	else{
	dec=dec*2;
	}
	bin=bin/10;
	}
printf("%d\n",result/2);
}
