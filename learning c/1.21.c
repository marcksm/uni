#include<stdio.h>

int main(){
int n, aux, cont, seq, seq1;

printf("Digite n e uma sequencia de n numeros\n");
scanf("%d",&n);
printf("A sequencia ");
while(n>0){

scanf("%d",&seq);
printf("%d ",seq);
if (seq1==seq || seq==seq1){
	cont--;
	}
scanf("%d",&seq1);
printf("%d ",seq1);
if (seq1==seq || seq==seq1){
	cont--;
	}

cont=cont+2;

n=n-2;
}
printf("é formada por %d segmentos\n",cont);
}
