#include<stdio.h>

int main(){

int n1, n2, n3, maior, meio, menor;

printf("Insira 3 numeros inteiros\n");
scanf("%d %d %d",&n1,&n2,&n3);
 
if (n1>n2 && n1>n3){
	maior=n1;
		if(n2>n3){
		meio=n2;
		menor=n3;
		}
		else{
		meio=n3;
		menor=n2;
		}
}

if (n2>n1 && n2>n3){
	maior=n2;
		if(n1>n3){
		meio=n1;
		menor=n3;
		}
		else{
		meio=n3;
		menor=n1;
		}
}

if (n3>n2 && n3>n1){
	maior=n3;
		if(n2>n1){
		meio=n2;
		menor=n1;
		}
		else{
		meio=n1;
		menor=n2;
		}
}

printf("%d %d %d",menor,meio,maior);
}

