#include<stdio.h>
#include<stdlib.h>

int main(){
int p, n, aux, nota1, nota2, notamaior, notamenor;

printf("Digite numero de alunos:\n");
scanf("%d",&n);
printf("Digite a nota dos alunos na sequencia:\n");
scanf("%d",&nota1);
	while (n>0){
	scanf("%d",&nota2);
	if (nota2>nota1){
	notamaior=nota2;
	notamenor=nota1;
	nota1=nota2;
	}
	else{
	notamaior=nota1;
	notamenor=nota2;
	nota1=nota2;
	}
	printf("Maior nota %d:\n",notamaior);
	printf("Menor nota %d: \n", notamenor);
}
