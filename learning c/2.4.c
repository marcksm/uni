#include<stdio.h>

int main(){
int n=1, m=2, aux=1, i=1, prim=1,soma=0;

printf("Digite n e uma sequencia de n numeros inteiros positivo\n");
scanf("%d",&n);

while (n>0){
scanf("%d",&i);
	for(m=2;m<=i;m++){
	if ((i%m==0) && (i!=m)){
	aux=0;
	}
	if(i%m==0 && i==m && i!=1 && aux==1){
	soma=i+soma;
	}
	}
n--;
aux=1;
}
printf("A soma dos numeros primos desta seq eh %d\n",soma);
}
