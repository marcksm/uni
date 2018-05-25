#include <stdio.h>

int contardigito(int n, int d){
    int cont=0, dig;
    while(n>0){
        dig=n%10;
        n=n/10;
        if (dig==d){
        cont++;
        }
    }
    return cont;
}

int main(){
    int a,b,i,contA,contB,diff=0;
    printf("...\n");
    scanf("%d %d",&a,&b);
        for(i=0;i<=9 && diff==0;i++){
            contA=contardigito(a,i);
            contB=contardigito(b,i);
            if (contA!=contB){
                diff=1;
                }
        }
        if(diff==0){
        printf("São permutações\n");
        }
        else{
        printf("NAO SAO PERMUTAÇOES\n");
        }

    return 0;
}
