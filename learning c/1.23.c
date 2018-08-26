#include<stdio.h>
#define MAX 1000
int main(){

int n, i=0, v[1000], aux,aux2,aux3, result=1;
printf("Digite um numero com n>= 10 algarismos, para verificar se \né palindromo\n");
for (i=0;i<1000;i++){
	v[i]=0;
	}
scanf("%d",&n);
aux=n;
i=0;
while(n>1){
v[i]=n%10;
n=n/10;
i++;
}
aux3=i;
aux2=i-1;
for (i=0;i<aux3;){
	printf("%d %d\n",v[i],v[aux2]);
	if(v[i]!=v[aux2]){
	result=0;
	}
	i++;
	aux2--;
}
if (result==1){
printf("É PALINDORMO\n");
}
else{
printf("NAO É PALINDORMO\n");
}
}
