#include<stdio.h>

int main(){
int a,n,i,dividendo,divisor,resto,mdc;
printf("...\n");
scanf("%d",&n);
scanf("%d",&mdc);
for(i=1;i<n;i++){
	scanf("%d",&a);
	if(a>=mdc){
	dividendo=a;
	divisor=mdc;
	}
	else{
	dividendo=mdc;
	divisor=a;
	}
	while((dividendo%divisor)!=0){
	resto=dividendo%divisor;
	dividendo=divisor;
	divisor=resto;
	}
	mdc=divisor;
}
printf("MDC=%d\n",mdc);
}
