#include<stdio.h>
#include<stdlib.h>

int main(){

int diaf, dia=1, vendf, vend, dia2=1, vend2;
	printf("Para encerrar o programa digite o dia = 0\n");
	printf("Digite o dia e a quantidade de discos vendidos:\n\n");
	
		scanf("%d %d", &dia, &vend);
		while (dia2!=0 or dia!=0){
		scanf("%d %d", &dia2, &vend2);
		if (vend2>vend){
		vendf=vend2;
		diaf=dia2;
		dia=dia2;
		vend=vend2;
		}
		else {
		vendf=vend;
		diaf=dia;
		}
		}
	printf("No dia %d de março foi vendido a maior quantidade de discos, totalizando %d discos\n\n",diaf, vendf);
		
}
