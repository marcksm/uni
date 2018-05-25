#include<stdio.h>

int encaixa(int a, int b){
    int resp=1, da, db;
    while(resp==1 && b>0){
        da=a%10;
        db=b%10;
        a=a/10;
        b=b/10;
        if(da!=db){
        resp=0;
        }
        }
    return resp;
}

int main() {
    int a,b,menor,maior,resp=2,stop=1;
    printf("Insira dois numeros inteiros positivos\n");
    scanf("%d %d",&a,&b);
    if (a>b){
    maior=a;
    menor=b;
    }
    else{
    maior=b;
    menor=a;
    }   
        while(maior>0 && stop==1){ 
            if (maior%10 == menor%10){
                resp=encaixa(maior,menor);
                    if(resp==0){
                    printf("NAO é sub\n");
                    stop=0;
                    }
                    if (resp==1){
                    printf("EH SUB\n");
                    stop=0;
                    }
                
            }
        maior=maior/10;
        }
    return 0;
}
