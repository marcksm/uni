#include<stdio.h>

int main(){
int n=1000, result,aux3,aux=1, aux2=1;

while(n<9999){
aux=n%100;
aux3=n/100;
aux2=aux3%100;
	if ((aux+aux2)*(aux+aux2)==n){
	printf("%d\n",n);
	}
n++;
}
}
