#include<stdio.h>
#define MAX 1000
int main(){

int k1=1,k2=0,k=0,altern,n,num=0,i=0,v[1000],aux;
printf("Digite n, e uma sequencia com n inteiros\npara verificar seu k-alternante\n");
scanf("%d",&n);
aux=n;
	while(n>0){
		scanf("%d",&num);
		if (num%2==0){
		v[i]=1;
		}
		if (num%2!=0){
		v[i]=0;
		}
		i++;
		n--;
	}
	for(i=0;i<aux;){
		if(v[i]==v[i+1]){
		k1++;
		if (k1!=k2 && v[i]==v[i+1] && v[i]==v[i-1]){
		k=0;}
		}
		else{
		k2=k1;
		k1=1;
		}
		i++;
		if (k1==k2 && v[i]!=v[i+1]){
			k=k2;
			}
	
	}		
	k2=0;	

	k1=0;
	for(i=0;i<aux;i++){
	if (v[i]==1){
	k1++;}
	
	if (v[i]==0){
	k2++;}}


	if (k1==aux || k2==aux){	
	k=aux;}

	printf("A seq eh alternante %d\n",k);
}





