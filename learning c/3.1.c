#include<stdio.h>

int main(){
int x, aux, i;
float montante=0, z;

printf("Digite o capital aplicado\n");
scanf("%d",&x);
printf("Digite quantos meses ficou aplicado e a taxa de juros mensais\n");
scanf("%d %f",&i,&z);
montante=x;
aux=i;
	while(i>0){
	montante=montante+(z/100*montante);
	i--;
	}
printf("TOTAL em %d MESES = %f\n",aux,montante);
}	
