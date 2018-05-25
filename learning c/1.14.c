#include<stdio.h>
#include<stdlib.h>

int main(){
float n, aux=0, result=1, num1=0, sum=0;
	printf("Digite um numero, para calcular a soma dos algarismos em sequencia fibonacci\n");
	scanf("%f",&n);
	n=n/2;
	while (n>aux){
	result=result+num1;
	
	num1=num1+result;
	sum=num1+result+sum;
	printf("%f,%f,",result, num1);
	
	aux++;

	}
	printf("\nA soma é %f\n", sum);

}
	

