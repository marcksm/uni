#include<stdio.h>
#include<stdlib.h>

int main(){
int n, resto, inteiro, result, num1, num2, aux, aux1;
printf("Digite dois numeros inteiros:\n");
scanf("%d %d",&num1, &num2);
	if (num1>num2){
	
	while (resto!=0){
	resto=num1%num2;	
	inteiro=num1/num2;
	num1=num2;
	num2=resto;
}
}
	if (num2>num1){
	aux=num2;
	aux1=num1;
	num1=aux;
	num2=aux1;
	while (resto!=0){
	resto=num1%num2;	
	inteiro=num1/num2;
	num1=num2;
	num2=resto;
}
}
printf("MDC é %d \n",num1);
}

