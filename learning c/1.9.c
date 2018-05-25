#include<stdio.h>
#include<stdlib.h>

int main(){
int n, j, i, aux, aux2, i2=1, j2=1;
	printf("Insira n para numero de saidas, e dois numeros para encontrar seus multiplos\n\n");
	scanf("%d %d %d", &n, &i, &j);
	
		while (n>0){	
			i2=i2+1;
			j2=j2+1;
		
			if (i2%i==0 or (j2%j==0)){
			printf("%d, %d,",i2,j2);
		
			n=n-1;
				}
				

			}
				
}
		
