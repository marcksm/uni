#include <stdio.h>
#define MAX 1000
#define PILHA 40000

void printar_maze(int a,int b,int maze[MAX][MAX]){
/*Função que imprime o labirinto conforme a matriz maze.*/
int z,x;
for(z=1;z<=a+1;z++){
    for(x=1;x<=b+1;x++){
        if (maze[z][x]==9999){
        printf(" T");
        }
        else if (maze[z][x]==8888){
        printf(" S");
        }
        else if(maze[z][x]==-1 || maze[z][x]==0){
        printf(" #",maze[z][x]);
        }
        else if(maze[z][x]!=0){
        printf(" %d",maze[z][x]);
        }
        printf(" "); 
    }
printf("\n\n");
}
printf("\n\n");
}
void moldura(int maze2[MAX][MAX],int a, int b, int z, int x){
/*Função que coloca moldura na matriz, para evitar problemas
de contagem de posições vazias não permitidas.
É colocado -1 em volta do labirinto.
*/
for(z=0,x=1;x<=b+1;x++){
    maze2[z][x]=-1;
}
for(z=1,x=0;z<=a+1;z++){
    maze2[z][x]=-1;
}
for(z=a+2,x=1;x<=b+1;x++){
    maze2[z][x]=-1;
}
for(z=1,x=b+2;z<=a+1;z++){
    maze2[z][x]=-1;
}

}
void procurar_caminhos_mais_curtos(int maze2[MAX][MAX],int cont,int a,int b,int z,int x,int aux){
/*Função que procura caminhos mais curtos, através de um método de incremento.
Vai adicionando numeros em casas vazias adjacentes a posição atual.
Ex: #=Paredes
    T=Tomas
    S=Saida

 0  0  #  0  0  # 

 #  0  0  0  #  # 

 0  0  #  0  0  0 

 S  #  0  0  0  T 


 8  7  #  5  6  # 

 #  6  5  4  #  # 

 8  7  #  3  2  1 

 S  #  3  2  1  T 


*/
while(cont<(MAX*MAX)){
/*aux tem a posição de Tomas, então a função procura por esse ponto para começar.
Depois coloca cont em todas as casas adjacentes livres dessa posiçao(aux).
Aux recebe cont, e cont++. Assim a função procurará o novo aux, e colocará cont 
em todas as casas adjacentes livres novamente. Fazendo isso até atingir o cont MAX.
Assim que o maze ficar completo, o cont ficara aumentando até o MAX sem interferir
nos pontos ja posicionados.*/
for(z=1;z<=a+1;z++){
    for(x=1;x<=b+1;x++){
     
       if (maze2[z][x]==aux){
            if (maze2[z-1][x]==0){
            maze2[z-1][x]=cont;
            }
            if (maze2[z][x+1]==0){
            maze2[z][x+1]=cont;
            }
            if (maze2[z+1][x]==0){
            maze2[z+1][x]=cont;
            }
            if (maze2[z][x-1]==0){
            maze2[z][x-1]=cont;
            }
        }
        
    
    }
}

        aux=cont;
        cont++;
}
}
void printar_caminho(int caminho[MAX], int num_caminhos,int maze[MAX][MAX],int a, int b){
int k=0,c=0,sair=0,yl=0,xl=0,pl=0;
/*Função que imprime um caminho e o labirinto com o caminho*/
    printf(" (%d,%d)SAIDA",caminho[0]-1,caminho[1]-1);
    for(k=3;sair==0;k=k+3){
        if (caminho[k+3]==0 && caminho[k+4]==0 && caminho[k+5]==0){
        sair=1; 
        }
        if(sair==0){
        printf(" (%d,%d)%d,",caminho[k]-1,caminho[k+1]-1,caminho[k+2]);
        }
        else{
        printf(" (%d,%d)TOMAS\n",caminho[k]-1,caminho[k+1]-1);
        }
    }
    sair=0;
    printf("CAMINHO NUMERO:%d\n\n",num_caminhos);
/*As operaçoes abaixo servem para imprimir o labirinto com o caminho.*/
    for(c=0;sair==0;c=c+3){
    xl=caminho[c];
    yl=caminho[c+1];
    pl=caminho[c+2];
    maze[xl][yl]=pl;        
        if(maze[xl][yl]==9999){
        sair=1;        
        }
        
    }
    sair=0;
   /* printar_maze(a,b,maze);*/
        for(c=0;sair==0;c=c+3){
        xl=caminho[c];
        yl=caminho[c+1];
        pl=caminho[c+2];
           if(maze[xl][yl]==9999){
           sair=1;        
           }
           maze[xl][yl]=0;        
        }
        sair=0;
}
int verificar_menor_numero_ao_redor(int menor_num[MAX],int maze2[MAX][MAX], int cont, int z, int x){
int l=0;          
/*Função que verifica o menor numero ao redor da posição.
Ex:

-1 -1  3 -1  0 -1
 T  1  2  3  4  5
 1  2  3  4  5  S
 2  3  4  5  6  7

Em volta do 5, temos:
  4
4 5 S
  6
O menor numero possivel é 4, então cont receberá 4, para
ser usado na próxima função.
Obs: S é a saida e tem seu numero representado por 8888
um numero muito grande para garantir que não exista posições 
adjacentes a ele com numero maior que a saida.
*/
    if(maze2[z-1][x]!=-1){
    menor_num[0]=maze2[z-1][x];
    }
    if(maze2[z][x+1]!=-1){
    menor_num[1]=maze2[z][x+1];
    }
    if(maze2[z+1][x]!=-1){
    menor_num[2]=maze2[z+1][x];
    }
    if (maze2[z][x-1]!=-1){
    menor_num[3]=maze2[z][x-1];
    }
    for(l=0;l<4;l++){
        if(menor_num[l]>0 && (menor_num[l]<cont)){
        cont=menor_num[l];   
        }
        /*Caso ao redor do numero é encontrado Tomas(9999), cont recebe
        9999 para indicar o fim de um caminho.*/
        if (menor_num[l]==9999){
        cont=9999;
        l=4;
        }
    }
    return cont;
}
int main(){
FILE * entrada;
int i=0,leitura=0,entry[MAX],maze[MAX][MAX],maze2[MAX][MAX],numero,tomas_pos[MAX],saida[MAX],menor_num[MAX];
int a=0,b=0,x=0,z=0,cont=1,aux=9999,j=0;
char u='a';
int posicao=0,pilha[PILHA],caminho[MAX],fim=1,p=0,tmp=0,num_caminhos=1,sair=0,sinalizar=1;
/*Leitura do arquivo e armazenamento de seus dados no vetor entry*/
entrada = fopen("labirinto", "r");
while(leitura != EOF){
leitura = fscanf(entrada, "%d", &numero);
entry[i]=numero;
i++;
}
/*Posicionamento de toma,saida e do tamanho do maze
Obs: É acrescido +1 na tomas_pos e na saida e 
-1 no a e b, para adequar o deslocamento do labirinto
para criar a MOLDURA.*/
tomas_pos[0]=entry[0]+1;
tomas_pos[1]=entry[1]+1;
saida[0]=entry[2]+1;
saida[1]=entry[3]+1;
a=entry[4]-1;
b=entry[5]-1;
/*Coloca o labirinto na matriz maze, onde z é linha
e x é coluna. */
for(z=1,i=6;z<=a+1;z++){
    for(x=1;x<=b+1;x++){
    maze[z][x]=entry[i];
    i++;
    }
}
/*Marcação da posição do Tomas e da Saida
Obs: eles recebem numeros grandes(9999 e 8888) para se diferenciar de todas
as outras posições na matriz. 
*/
maze[tomas_pos[0]][tomas_pos[1]]=9999;
maze[saida[0]][saida[1]]=8888;
for(z=0;z<=a+1;z++){
/*Uma cópia da matriz do labirinto é feita para utilizar em outras funções
sem perder os resultados obtidos até agora*/
    for(x=0;x<=b+1;x++){
    maze2[z][x]=maze[z][x];
    }
}
moldura(maze2,a,b,z,x);
cont=1;
/*Cont deve ser 1 antes de começar a procurar os caminhos*/
procurar_caminhos_mais_curtos(maze2,cont,a,b,z,x,aux); 
/*printar_maze(a,b,maze2);*/
posicao=8888;
/*A variavél posicao indica a posição atual no caminho,ela tem inicio na
saida. Pois a verificação do caminho é feita da saida para o tomas.
*/

caminho[0]=saida[0];
caminho[1]=saida[1];
caminho[2]=8888;
i=0;
z=caminho[0];
x=caminho[1];
cont=MAX*MAX;/*Cont deve ser o maximo possivel*/
j=3;
/*Inicio da busca de caminhos:
A forma utilizada é baseada no backtracking. Começo pela posição da saida
e analiso as casas adjacentes a posição atual.
Ex:
 8  7  -1  5  6  -1 
                                             1
-1  6   5  4  -1 -1                        1 P 1 (Casas adjacentes ao ponto P)
                                             1
 8  7  -1  3  2   1 

 S -1   3  2  1   T 
Na saida(S ou 8888) as casas adjacentes são 8 e -1, -1 é descartado por ser
parede. Então a posição do (2,0)8, onde (2,0) é a posição na matriz e 8 é um
indice da posição no caminho para facilitar as futuras
manipulações com esse ponto.Esse ponto é armazenado no vetor pilha.

Como não temos mais nenhum ponto que possa ser armazenado,o vetor caminho
recebe o ultimo ponto da pilha(2,0)8 e esse ponto é apagado da pilha.A variavel
posicao recebe agora 8 e z e x recebem suas cordenadas (2,0). Assim a posição
de observação agora é (2,0)8. Novamente analisamos suas casas adjacentes e 
procuramos pela menor casa e != de -1, que nesse caso resulta no (2,1)7.
É realizado o mesmo procedimento: coloca o ponto na pilha passa pro caminho e 
retira da pilha.
No ponto (2,3)3 acontece algo importante para esse método:
Pois ao analisar os pontos adjacentes temos dois pontos: (3,3)2 e (2,4)2,
armazenaremos os dois na pilha(tanto faz a ordem), e passaremos o ultimo ponto
para o vetor caminho, dessa forma sobra um ponto na pilha e ela não fica vazia!
Ao chegar no Tomas(9999), temos um caminho completo!, agora falta os outros.
Quando finalizamos o caminho, verificamos se a pilha tem algum ponto, se tiver,
este ponto é trocado com o ponto que tem o mesmo indice no vetor caminho.
Ex:ao final de 1 caminho
 pilha (2,4)2
caminho (3,0)8888 (2,0)8, (2,1)7, (1,1)6, (1,2)5, (1,3)4, (2,3)3, (3,3)2,
(3,4)1, (3,5)9999

Verifica então que o indice do ultimo ponto da pilha (2,4)2 é 2, que sera 
substituido pelo ponto de indice 2 do caminho ( (3,3)2 ), e a posicao
receberá 2 e z e x recebem suas cordenadas (2,4) e o ponto da pilha é removido.
Agora o caminho terá inicio neste ponto (2,4)2, e parte anterior a este caminho
é mantida. Acontecerá o procedimento de observar as casas adjacentes e procurar
o menor numero. Porém neste caso também teremos 2 casas adjacentes com mesmo
numero menor: (2,5)1 e (3,4)1.
Logo os dois são colocados no vetor pilha, e o ultimo é retirado e passado 
para o vetor caminho,desse modo teremos:
pilha: (2,5)1
caminho: (3,0)8888 (2,0)8, (2,1)7, (1,1)6, (1,2)5, (1,3)4, (2,3)3, (2,4)2,
(3,4)1, (3,5)9999

Agora basta permutar o ponto da pilha (2,5)1 com o de indice 1 no caminho:
pilha (0,0,0)<-Vazia
caminho:  (3,0)8888 (2,0)8, (2,1)7, (1,1)6, (1,2)5, (1,3)4, (2,3)3, (2,4)2,
(2,5)1, (3,5)9999

Totalizando 3 caminhos diferentes.
A condição de parada é quando o vetor pilha estiver vazio.

Obs: Quando não há caminhos possíveis significa que a saida esta bloqueada,
Ex: Se bloquearmos (1,1) teremos um labirinto assim:
 #  #  #  5  6  # 

 #  #  5  4  #  # 

 8889  8890  #  3  2  1 

 S  #  3  2  1  T 

Pois durante a enumeração a função tentará enumerar todas as casas
adjacentes a um numero anterior, porém ao encontrar as casas bloqueadas
não consiguirá enumerar as casas do outro lado do bloqueio até que o valor
do cont(variavel que inicia de 1 e vai até MAX*MAX) atinja o valor 8888,
que é o valor da saida, quando isso ocorre, ele enumera as casas adjacentes
com 8889 e 8890... e assim por diante até terminar todas as casas.
Caso a posição 8889 seja casa adjacente a SAIDA, então o programa entende
que não há caminhos possíveis.             -1
Caso a SAIDA esteja totalmente bloqueada -1 S-1 existe uma condição 
                                           -1
existe uma condição especifica para o termino do programa.

*/
while(fim!=0){
    if(maze2[z][x]==posicao){
            if(posicao==8888 && maze2[z-1][x]==-1 && maze2[z][x+1]==-1 
            && maze2[z][x-1]==-1 && maze2[z+1][x]==-1){
            fim=0;
            }
            for(tmp=0;tmp<4;tmp++){
            menor_num[tmp]=0;                
            }
            for(tmp=j;sair==0;tmp++){
            caminho[tmp]=0;
                if(caminho[tmp]==0 && caminho[tmp+1]==0 && caminho[tmp+2]==0){
                sair=1;            
                }
            }
    sair=0;
    cont=verificar_menor_numero_ao_redor(menor_num,maze2,cont,z,x);
            if (maze2[z-1][x]==cont && maze2[z-1][x]!=-1){
            pilha[i]=z-1; 
            pilha[i+1]=x;
            pilha[i+2]=cont;
            i=i+3;
            }
            if (maze2[z][x+1]==cont && maze2[z][x+1]!=-1){
            pilha[i]=z;
            pilha[i+1]=x+1;
            pilha[i+2]=cont;
            i=i+3;
            }
            if (maze2[z+1][x]==cont && maze2[z+1][x]!=-1){
            pilha[i]=z+1;
            pilha[i+1]=x;
            pilha[i+2]=cont;
            i=i+3;
            }
            if (maze2[z][x-1]==cont && maze2[z][x-1]!=-1){
            pilha[i]=z;
            pilha[i+1]=x-1;
            pilha[i+2]=cont;
            i=i+3;
            }
    }
    caminho[j]=pilha[i-3];
    caminho[j+1]=pilha[i-2];
    caminho[j+2]=pilha[i-1];/*cont*/
    if (pilha[i-1]==9999){
    pilha[i-3]=0;
    pilha[i-2]=0;
    pilha[i-1]=0;
    }
    i=i-3;
    j=j+3;
    z=caminho[j-3];
    x=caminho[j-2];
    posicao=cont;
    
    if(cont==9999){
    printar_caminho(caminho,num_caminhos,maze,a,b);
        if((pilha[0]!=0 || pilha[1]!=0 || pilha[2]!=0)){
        num_caminhos++;
            for(p=2;sair==0;p=p+3){
                if((caminho[p]==0 && caminho[p+1]==0 && caminho[p+2]==0)){
                sair=1;
                }
                if (caminho[p]==pilha[i-1]){
                caminho[p]=pilha[i-1];
                caminho[p-2]=pilha[i-3];
                caminho[p-1]=pilha[i-2];
                z=caminho[p-2];
                x=caminho[p-1];
                posicao=caminho[p];
                j=p+1;
                sair=1;
                i=i-3;
                cont=posicao;            
                }
            }
        sair=0;
       /* printf("Pressione a tecla enter para continuar...\n");
        scanf("%c",&u);*/
        }
        sair=0;
        if((pilha[0]==0 && pilha[1]==0 && pilha[2]==0)){
        fim=0;
        printf("Total %d de caminhos possiveis\n",num_caminhos);
        sair=0;
        }
    }
    else{
        if(cont==8889||cont==8890||fim==0){
        fim=0;
        printf("Não ha caminhos\n");        
        }    
    }
}

fclose(entrada);
return 0;
}
