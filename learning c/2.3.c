#include<stdio.h>

int main(){

int m,n,x=0,y=0,aux,aux2,xx,yy,result;

printf("Digite m e n como valores maximos para x e y na funcao x*y-x*x+y\n");
scanf("%d %d",&m,&n);

while(x<m){
	x++;
	if (aux>aux2){
		result=aux;
		xx=x;
		yy=y;
		}
		else{
		result=aux2;
		xx=x;
		yy=y;
		}
	aux2=(x*y)-(x*x)+y;
	
	
		
	while(y<n){
	y++;
	aux=(x*y)-(x*x)+y;
		if (aux>aux2){
		result=aux;
			xx=x;
		yy=y;
		}
		else{
		result=aux2;
		xx=x;
		yy=y;
		}
	
	}

}
printf("%d\n",result);
printf("%d %d",xx,yy);
}
