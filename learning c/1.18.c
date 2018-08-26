#include<stdio.h>

int main(){
int n1,n2,n3;
printf("Digite 3 numeros inteiros para verificar se eles fazem parte de um triangulo retangulo\n");
scanf("%d %d %d",&n1,&n2,&n3);

if (((n1*n1)==(n2*n2)+(n3*n3)) || ((n2*n2)==(n1*n1)+(n3*n3)) || ((n3*n3)==(n2*n2)+(n1*n1))){
	printf("Formam os lados de um triangulo retangulo\n");
}
else{
printf("Não formam lados de um triangulo retangulo\n");
}
}
