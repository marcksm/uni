#include<stdio.h>

int main(){

int i,aux,n;
float h, x, y;
	
printf("Type n positive integer, and n real coordinates(x,y)\n");
scanf("%d",&n);
while(n>0){
	scanf("%f %f",&x,&y);
	
	if ((x>=0) && (y>=0) && (((float)x*x)+((float)y*y)<=1)){
	printf("(%f,%f)pertencem\n",x,y);
	}
	else{
	printf("(%f,%f)NAO pertencem\n",x,y);
	}
n--;
}
}
