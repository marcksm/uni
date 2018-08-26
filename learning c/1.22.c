#include<stdio.h>

int main(){

int n, aux=0, seq, seq1, cont=0, maior=0;
seq=seq1=1;
printf("Digite n e uma sequencia de n inteiros\n");
scanf("%d",&n);
printf("Na sequencia ");
scanf("%d",&seq1);
printf("%d ",seq1);
while(n>1){
scanf("%d",&seq);
printf("%d ",seq);
	if (seq>seq1){
	cont++;

	}
	else{
	if (cont>aux){
	aux=cont;}
	cont=0;
	}


scanf("%d",&seq1);
printf("%d ",seq1);
	if (seq1>seq){
	cont++;
	}
	else{
	if (cont>aux){
	aux=cont;}
	cont=0;
	}
	
n=n-2;
}
if (aux>cont){
printf("o comprimento do segmento crescente máximo é %d\n",aux+1);
}
else{
printf("o comprimento do segmento crescente máximo é %d\n",cont+1);
}
}





