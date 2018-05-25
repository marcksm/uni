#include<stdio.h>

int main(){

int n, k=1;
float h=0;

printf ("Digite n inteiro positivo\n");
scanf("%d",&n);

	while(n>=k){
	h=h+((float)1/k);
	k++;
}
printf("%f\n",h);
}
