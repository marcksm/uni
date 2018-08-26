#define MAX 100000
#include <stdio.h>
/*Função que retorna a jogada do jogador*/
int jogador(int jogada){
    if(jogada == 1 ){
        printf("Você jogou pedra!\n");
    }
    if(jogada == 2){
        printf("Você jogou papel!\n");
    }
    if (jogada == 3){
        printf("Você jogou tesoura!\n");
    }
return jogada;
}
/*Função que retorna a jogada do Super computador*/
float comput(float cont){
    int comp;        
    if (cont<(0.333333333)){
        printf("O Super computador jogou pedra!\n");
        comp=1;
    }
    if (cont>=(0.333333333) && cont<(0.666666667)){
        printf("O Super computador jogou tesoura!\n");	
        comp=3;
    }
    if (cont>=(0.666666667)){
        printf("O Super computador jogou papel!\n");
        comp=2;
    }
return(comp);
} 

int main(){
/*Declaração de variaveis*/
int modo=10,comp=0,emp=0,vit=0,derr=0,v[MAX],u[MAX],t[MAX], c[MAX];
int x=0,y=0,z=0,papel=0,pedra=0,tesoura=0,jogada=1,jog=0, i=0, k=0;
int jogada3_2=0,jogada3_1=0,jogada3_3=0,jogada2_2=0,jogada2_3=0, fim=0;
int jogada2_1=0,jogada1_1=0,jogada1_3=0,jogada1_2=0,n=0,ni=0;
int ultima=0,aux=1,seq4=0,seq3=0,seq2=0,anterior1=0;
int anterior2=0,anterior3=0,aux2=0,h=0,vitan=0;
unsigned long int a=22695477,x0=3,b=1,m=4294967296,xi=0;
char nome[MAX];
float cont=0,win=0,draw=0,lose=0;

/*Declaração de variaveis*/
printf("******************************************************************\n");
printf("*************************** JAKENPON *****************************\n");
printf("******************************************************************\n");
printf("***  Bem vindo ao Jaken-Pon, o jogo da pedra, papel e tesoura! ***\n");
printf("******************************************************************\n");
printf("***************************  REGRAS: *****************************\n");
printf("******************************************************************\n");
printf("*** No Janken-pon, os jogadores devem simultaneamente escolher ***\n");
printf("*** 3 possíveis jogadas: pedra, papel e tesoura. Vence o jogador *\n");
printf("*** que obtiver maior numero de vitórias em ao menos 100 turnos. *\n");
printf("*** Para checar o ganhador de cada turno compara-se as jogadas ***\n");
printf("*** (pedra,papel,tesoura) jogados por ambos os oponentes.      ***\n");
printf("******************************************************************\n");
printf("**************** PEDRA GANHA DE TESOURA (AMASSANDO-A) ************\n");
printf("**************** TESOURA GANHA DE PAPEL  (CORTANDO-O) ************\n");
printf("**************** PAPEL GANHA DE PEDRA (EMBRULHANDO-A) ************\n");
printf("******************************************************************\n");
printf("**** Nobre jogador, digite seu primeiro nome para iniciarmos: ****\n");
printf("********* Finalize a inserção dele com um ponto '.' ao final *****\n");

/*O operador logico while abaixo, serve para armazenar o nome do jogador
em um vetor, e assim reproduzi-lo a cada interação*/
while(fim==0){
    scanf("%c",&nome[n]);
        if (nome[n]=='.'){
            fim=1;
        }
    n++;
    ni++;
}
/*
Expressão que imprime o nome do jogador
*/
for(n=0;n<ni;n++){
    if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
        printf("%c",nome[n]);
    }
}
printf("? É isso mesmo? Que nome poderoso para um simples humano,\n");
printf("Mas não me intimido com nomes, eu o Super Computador deixarei\n");
printf("que escolha a maneira como vou te vencer\n\n");
printf("Escolha o modo de jogo:\n");
while(modo!=0){
/*Reset das variaveis para trocar de modo*/
emp=0,vit=0,derr=0,jog=0;
papel=0,pedra=0,tesoura=0,i=0,k=0;
    if (modo!=10){
        printf("Escolha o modo de jogo:\n");
    }   
printf("1-Fácil\n");
printf("2-Médio\n");
printf("3-Dificil\n");
printf("0-Sair\n");
scanf("%d",&modo);
    if(modo == 1){
    vit=0, emp=0, derr=0, jog=0, win=0, lose=0, draw=0;
    printf("Você selecionou o modo fácil\n");
    printf("Vou fingir que não sei diferenciar um papel  de uma tesoura\n");
        jogada=1;/*Evita problemas ao trocar de modo*/
        while(jogada!=0){
        printf("1=Pedra, 2=Papel, 3=Tesoura\nDigite 0 para acabar o jogo\n");
        scanf("%d",&jogada);
        jogador(jogada);/*Função que retorna a jogada do jogador*/
                if(jogada!=0){				
                xi=((a*x0)+b)%m;/*Parametro da jogada aleatória*/
                cont=(float)xi/(m-1);/*Parametro da jogada aleatória*/
                comp=comput(cont);/*Função que retorna a jogada do computador*/
                x0=xi;/*Parametro da jogada aleatória*/
                /*Comparador entre a jogada do jogador e do computador*/
                    if((jogada==1 && comp==3) || (jogada==2 && comp==1)
                    || (jogada==3 && comp==2)){
                        for(n=0;n<ni;n++){
                            if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                            printf("%c",nome[n]);
                            }
                        }
                    printf(" ganhou!\n");
                    vit++;
                    }
                    if((jogada==1 && comp==1) || (jogada==2 && comp==2)
                    || (jogada==3 && comp==3)){
                    printf("Empatou!\n");
                    emp++;
                    }
                    if ((jogada==1 && comp==2) || (jogada==2 && comp==3)
                    || (jogada==3 && comp==1)){
                    printf("O Super computador ganhou!\n");
                    derr++;
                    }
                /*Estatistica por turno*/
                win=(float)(vit)/(vit+emp+derr)*100;
                draw=(float)(emp)/(vit+emp+derr)*100;
                lose=(float)(derr)/(vit+emp+derr)*100;
                jog++;
                printf("**********************\n");
                printf("%.1f %% ",win);
                    for(n=0;n<ni;n++){
                        if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                        printf("%c",nome[n]);
                        }
                     }
                printf("\n");
                printf("%.1f %% EMPATES\n",draw);
                printf("%.1f %% COMPUTADOR\nJOGADAS:%d\n",lose,jog);
                printf("**********************\n");
                }/*if jogada*/
        }/*while jogada*/
    }/*if modo*/
    if (modo==2){
    /*Reset de variaveis*/
    vit=0, emp=0, derr=0, jog=0, win=0, lose=0, draw=0;
    i=0,k=0; 
    printf("Você selecionou o modo médio\n");
    /*Expressão que imprime o nome do jogador*/
        for(n=0;n<ni;n++){
            if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
            printf("%c",nome[n]);
            }
        }
    printf(",você adora desafios não? Parece que terei que acabar com\n");
    printf("a sua vontade de vencer hoje. HOJE E SEMPRE HAHAHAHAHA\n");
    jogada=1;    
        while(jogada!=0){
        printf("1=Pedra, 2=Papel, 3=Tesoura\nDigite 0 para acabar o jogo\n");
        scanf("%d",&jogada);
        k++;
        v[i]=jogador(jogada);/*jogadas são armazenadas em um vetor*/
        ultima=v[i-1]; /*Ultima jogada que o jogador realizou*/       
        i++;
            if(k>=8){
/*Algoritimo da probabilidade condicional, a partir de 8 jogadas ele começa
a ser utilizado(antes disso é aleatório). Na qual consiste no seguinte: 
analisa as ultimas 7 jogadas e busca por padrões em pares. Sendo pedra=1,
papel=2,tesoura=3.Exemplo: 12121212122, verifica-se que 1depois2 acontece
com alta freq, assim como 2depois1,essas frequencias são armazenadas em 
variaveis especificas.Então dado a ultima jogada, 2, como nas ultimas 7 
o registro de padrão foi 2depois1 foi superior a qualquer outro 2depois2 
ou 2depois3, logo o computador jogara contrá 2depois1, jogando 2, pois 
a probabilidade do jogador jogar 1 é alta.
Analisar as ultimas 7 foi a que apresentou melhores resultados neste algoritmo
pois o computador tem um bom histórico de jogadas, e ao mesmo tempo não demora
muito para reagir caso o jogador apresente sequencias repetitivas.
*/
                for (i=k-7/*Analisa as 7 ultimas*/;i<k;i++){
                    if (v[i-2]==1){
                        if (v[i-1]==2){
                        jogada1_2++; 
                        } 
                        if (v[i-1]==3){
                        jogada1_3++;
                        }
                        if (v[i-1]==1){
                        jogada1_1++;
                        }
                    }
                    if (v[i-2]==2){
                        if(v[i-1]==1){
                        jogada2_1++;
                        }
                        if (v[i-1]==2){
                        jogada2_2++;
                        }
                        if (v[i-1]==3){
                        jogada2_3++;
                        }
                    }
                    if (v[i-2]==3){
                        if(v[i-1]==1){
                        jogada3_1++;
                        }             
                        if (v[i-1]==2){
                        jogada3_2++;
                        }
                        if (v[i-1]==3){
                        jogada3_3++;
                        }
                    }                                                                        
                }/*for*/
/*Os próximos operadores logicos servem para verificar qual jogada o computador
deve realizar, para isso elas comparam a frequencia de uma jogada dado a 
anterior, e verificam a ultima jogada do oponente, e buscam a maior frequencia
dado ela(ultima) para que o computador jogue contra ela.
Algumas jogadas empatam em numero de frequencia, então o computador busca jogar
pelo empate, que é melhor do que arriscar por uma derrota. */
                if(ultima==1){ 
                    if(jogada1_2 > jogada1_3 && jogada1_2 > jogada1_1){
                    comp=3;
                    }
                    if(jogada1_3 > jogada1_2 && jogada1_3 > jogada1_1){
                    comp=1;
                    }
                    if(jogada1_1 > jogada1_2 && jogada1_1 > jogada1_3){
                    comp=2;
                    }
/*Nestas comparações, caso a frequencia de jogada em 1depois1 e 1depois3 seja
a mesma, o computador opta por lançar 1, pois pode vencer ou empatar e nunca
perder.(obs:o !=0  serve para evitar de utilizar essa estrategia no começo
quando as variaveis estão zeradas)*/
                    if (jogada1_1==jogada1_3 && jogada1_3!=0){
                    comp=1;          
                    }
                    if(jogada1_1==jogada1_2 && jogada1_1!=0){
                    comp=2;
                    }
                    if(jogada1_2==jogada1_3 && jogada1_2!=0){
                    comp=3;
                    }  
                }
                if(ultima==2){
                    if(jogada2_2 > jogada2_3 && jogada2_2 > jogada2_1){
                    comp=3;
                    }
                    if(jogada2_3 > jogada2_2 && jogada2_3 > jogada2_1){
                    comp=1;
                    }
                    if(jogada2_1 > jogada2_2 && jogada2_1 > jogada2_3){
                    comp=2;
                    }
                    if(jogada2_1==jogada2_2 && jogada2_1!=0){
                    comp=2;
                    }
                    if(jogada2_1==jogada2_3 && jogada2_1!=0){
                    comp=1;
                    }
                    if(jogada2_2==jogada2_3 && jogada2_2!=0){
                    comp=3;
                    }
                } 
                if(ultima==3){
                    if(jogada3_2 > jogada3_3 && jogada3_2 > jogada3_1){
                    comp=3;
                    }
                    if(jogada3_3 > jogada3_2 && jogada3_3 > jogada3_1){
                    comp=1;
                    }
                    if(jogada3_1 > jogada3_2 && jogada3_1 > jogada3_3){
                    comp=2;
                    }
                    if(jogada3_1==jogada3_2 && jogada3_1!=0){
                    comp=2;
                    }
                    if(jogada3_2==jogada3_3 && jogada3_2!=0){
                    comp=3;
                    }
                    if(jogada3_1==jogada3_3 && jogada3_1!=0){
                    comp=1;
                    }
                } 
/*Jogada do computador*/
                if(comp==2){                                          
                printf("O computador jogou papel!\n");
                }
                if(comp==3){
                printf("O computador jogou tesoura!\n");
                }
                if(comp==1){
                printf("O computador jogou pedra!\n");
                }
/*Reset das variaveis de cada possibilidade, já que a cada jogada, essas
variaveis são incrementadas de acordo com o histórico de jogadas do vetor
v, o reset evita que elas armazenem jogadas repetidas */
            jogada3_2=0;
            jogada3_1=0;
            jogada3_3=0;
            jogada2_2=0;
            jogada2_3=0;
            jogada2_1=0;
            jogada1_1=0;
            jogada1_3=0;
            jogada1_2=0;
            }/*if k>=8*/
        else{
/*Algoritmo da jogada aleatória que é utilizado antes de atingir 8 jogadas*/
            xi=((a*x0)+b)%m;
            cont=(float)xi/(m-1);
            comp=comput(cont);		
            } 
        x0=xi;
/*Comparador que imprime o vencedor da rodada*/
        if ((jogada==1 && comp==3) || (jogada==2 && comp==1)
        || (jogada==3 && comp==2)){
            for(n=0;n<ni;n++){
                if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                printf("%c",nome[n]);
                }
            }
        printf(" ganhou!\n");
        vit++;
        
        }
        if ((jogada==1 && comp==1) || (jogada==2 && comp==2)
        || (jogada==3 && comp==3)){
        printf("Empatou!\n");
        emp++;
        }
        if ((jogada==1 && comp==2) || (jogada==2 && comp==3)
        || (jogada==3 && comp==1)){
        printf("O Super Computador ganhou!\n");
        derr++;
        }
        /*Estatistica por turno*/
        win=(float)(vit)/(vit+emp+derr)*100;
        draw=(float)(emp)/(vit+emp+derr)*100;
        lose=(float)(derr)/(vit+emp+derr)*100;
        jog++;
        printf("**********************\n");
        printf("%.1f %% ",win);
            for(n=0;n<ni;n++){
                if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                printf("%c",nome[n]);
                }
            }
        printf("\n");
        printf("%.1f %% EMPATES\n",draw);
        printf("%.1f %% COMPUTADOR\nJOGADAS:%d\n",lose,jog);
        printf("**********************\n");
        }/*while*/
    }/*if modo*/
    if (modo==3){
    vit=0, emp=0, derr=0, jog=0, win=0, lose=0, draw=0,vitan=0,h=0;
    /*Reset dos vetores auxiliares do modo dificil*/
        for (i=0;i<10000;i++){
        v[i]=0;
        u[i]=0;
        t[i]=0;
        c[i]=0;
        }
    /*Reset de variaveis*/
    x=0,y=0,z=0,k=0,i=0,h=5;
    printf("Você selecionou o modo dificil\n");
    jogada=1;/*Evita problemas ao mudar de modo*/
        while(jogada!=0){
        printf("1=Pedra, 2=Papel, 3=Tesoura\nDigite 0 para acabar o jogo\n");
        scanf("%d",&jogada);
        k++;
        v[i]=jogador(jogada);
/*A variavel vitan, analisa o desempenho em tempo real do algoritmo, caso a var
fique maior que 8, o modo de analise das jogadas anteriores é resetado, dessa
forma evita-se jogadas repetidas Ex: 1111111111222222222221313131313131,
assim com o reset, computador coloca seu ponto inicial de verificação, 
apartir de k-7, recomeçando a analise de padrões.
Também é feito um reset nos vetores que contabilizam as jogadas dadas
as anteriores*/
        if (vitan>8){
        h=k-7;
        vitan=0;
            for (i=0;i<30000;i++){
            v[i]=0;
            u[i]=0;
            t[i]=0;
            c[i]=0;
            }
        }
        /*As ultimas jogadas são registradas nas seguintes variaveis*/        
        ultima=v[i-1];        
        anterior1=v[i-2];
        anterior2=v[i-3];
        anterior3=v[i-4];
        i++;
        
            if(k>=9){
            /*Condição para inicio do algoritmo, apartir da nona jogada é 
            iniciado,antes é aleatório*/
                for (i=h/*h é modificado conforme vitan*/,z=0,y=0,x=0;i<k;i++){
/*Essa lógica, é baseado no método criado pelo New York Times 
http://www.nytimes.com/interactive/science/rock-paper-scissors.html?_r=0
Que inicialmente busca padroes de 4 repetições, depois 3 e depois 2.
O algoritmo armazena em um vetor especifico para cada interação,
para então verificar qual maior freq jogada dado
as 4 anteriores, ou 3 anteriores ou 2 anteriores, analisando todas
as jogadas apartir de h.*/      
                    if (v[i-1]==ultima && v[i-2]==anterior1 && 
                        v[i-3]==anterior2 && v[i-4]==anterior3){
/*É realizado uma contagem para ver qual tipo de sequencia mais 
se repetiu, e  em cada interação existe um vetor, para armazenar
as jogadas de acordo com a sequencia.Ex:12121212312312312121
o computador procurará por 2121(ultima sequencia possivel)
em todas as jogadas anteriores(apartir da quinta),e armazenará em
um vetor sua proxima jogada dada a sequencia anterior, que neste 
caso é 2 e 2. Depois comparará no vetor, para saber qual mais se
repetiu e jogará contra ela. Neste caso só teve 2, então computador
jogara 3.*/
                    seq4++;
                    u[x]=v[i];
                    /*Este vetor armazena as jogadas dadas as anteriores
                    da sequencia 4*/
                    x++;
                    aux=0;               
                    }
                    if (v[i-1]==ultima && v[i-2]==anterior1 && v[i-3]==anterior2 && aux==1){
                    seq3++;
                    t[y]=v[i];
                    /*Este vetor armazena as jogadas dadas as anteriores
                    da sequencia 3*/
                    y++;
                    aux=0;
                    }
                    if (v[i-1]==ultima && v[i-2]==anterior1 && aux==1){
                    seq2++;
                    c[z]=v[i];
                    /*Este vetor armazena as jogadas dadas as anteriores
                    da sequencia 4*/
                    z++;
                    aux=0;
                    }
/*A váriavel aux serve para evitar a contagem de sequencias simultaneas, uma
vez que a seq4 foi contada, a mesma ordem de jogadas não pode ser adicionada
a seq3 e nem a seq2*/                                   
                    aux=1;
                }/*for*/
/*Verifica qual a seq mais utilizada,(seq4,seq3 ou seq2)e busca analisar a
maior frequencia de ultimas jogadas dado as anteriores e o computador 
joga contra ela(ultima jogada) */     
/*printf("SEQ4=%d\nSQ3=%d\nSQ2=%d\nh=%d\nvitn=%d\n",seq4,seq3,seq2,h,vitan);*/ 
                if((seq4 > seq3 && seq4 > seq2)||(seq2==seq4)||(seq3==seq4)){
                    for (x=0;x<k;x++){
                        if(u[x]==1){
                        pedra++;
                        }
                        if(u[x]==2){
                        papel++;                            
                        }
                        if(u[x]==3){
                        tesoura++;
                        }
                    }
                    if(tesoura==pedra && tesoura!=0){
                    comp=1;
                    }
                    if(tesoura==papel && tesoura!=0){
                    comp=3;
                    }
                    if(papel==pedra && papel!=0){
                    comp=2;
                    }
                    if(pedra>papel && pedra>tesoura){
                    comp=2;
                    }
                    if(papel>pedra && papel>tesoura){
                    comp=3;
                    }
                    if(tesoura>pedra && tesoura>papel){
                    comp=1;
                    }
                                                                         
                }
                if((seq3 > seq2 && seq3 > seq4 )){
                    for (y=0;y<k;y++){
                        if(t[y]==1){
                        pedra++;
                        }
                        if(t[y]==2){
                        papel++;                            
                        }
                        if(t[y]==3){
                        tesoura++;
                        }
                    }
                    if(tesoura==pedra && tesoura!=0){
                    comp=1;
                    }
                    if(tesoura==papel && tesoura!=0){
                    comp=3;
                    }
                    if(papel==pedra && papel!=0){
                    comp=2;
                    }
                    if(pedra>papel && pedra>tesoura){
                    comp=2;
                    }
                    if(papel>pedra && papel>tesoura){
                    comp=3;
                    }
                    if(tesoura>pedra && tesoura>papel){
                    comp=1;
                    }
                    
                }
                if((seq2 > seq3 && seq2 > seq4)){
                    for (z=0;z<k;z++){
                        if(c[z]==1){
                        pedra++;
                        }
                        if(c[z]==2){
                        papel++;                            
                        }
                        if(c[z]==3){
                        tesoura++;
                        }
                    }
                    if(tesoura==pedra && tesoura!=0){
                    comp=1;
                    }
                    if(tesoura==papel && tesoura!=0){
                    comp=3;
                    }
                    if(papel==pedra && papel!=0){
                    comp=2;
                    }
                    if(pedra>papel && pedra>tesoura){
                    comp=2;
                    }
                    if(papel>pedra && papel>tesoura){
                    comp=3;
                    }
                    if(tesoura>pedra && tesoura>papel){
                    comp=1;
                    }
                    
                }
                if(comp==2){                                          
                printf("O Super computador jogou papel!\n");
                }
                if(comp==3){
                printf("O Super computador jogou tesoura!\n");
                }
                if(comp==1){
                printf("O Super computador jogou pedra!\n");
                }
                /*Reset de variaveis*/
            seq4=0;
            seq2=0;
            seq3=0;
            anterior1=0;
            anterior2=0;
            anterior3=0;
            anterior1=0;
            pedra=0;
            papel=0;
            tesoura=0;
            }/*ifk>=9*/
            else{
            /*Algoritmo aleatório*/
            xi=((a*x0)+b)%m;
            cont=(float)xi/(m-1);
            comp=comput(cont);		
            }
        x0=xi;
        /*Comparador para verificar o vencedor do turno*/
        if ((jogada==1 && comp==3) || (jogada==2 && comp==1)
        || (jogada==3 && comp==2)){
        /*Imprime o nome do jogador*/            
            for(n=0;n<ni;n++){
                if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                printf("%c",nome[n]);
                }
            }
            printf(" ganhou!\n");
            vit++;
            vitan=vitan+2;/*vitan é somado duas vezes a cada vit do jogador*/
            
        }
        if ((jogada==1 && comp==1) || (jogada==2 && comp==2)
        || (jogada==3 && comp==3)){
        printf("Empatou!\n");
        emp++;
        }
        if ((jogada==1 && comp==2) || (jogada==2 && comp==3)
        || (jogada==3 && comp==1)){
        printf("O Super Computador ganhou!\n");
        derr++;
        vitan--;/*vitan é subtraido uma vez a cada derrota do jogador*/
        }
        win=(float)(vit)/(vit+emp+derr)*100;
        draw=(float)(emp)/(vit+emp+derr)*100;
        lose=(float)(derr)/(vit+emp+derr)*100;
        jog++;
        /*Estatistica por turno*/
        printf("**********************\n");
        printf("%.1f %% ",win);
            for(n=0;n<ni;n++){
                if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                printf("%c",nome[n]);
                }
            }
        printf("\n");
        printf("%.1f %% EMPATES\n",draw);
        printf("%.1f %% COMPUTADOR\nJOGADAS:%d\n",lose,jog);
        printf("**********************\n");
        }/*while*/                
    }/*if modo3*/
    if (modo == 555){
    /*MODO SECRETO LIZARD SPOCK*/
    /*Utiliza dos conceitos do modo fácil para jogar*/
    printf("*******************CHEATCODE ACTIVATED***********************\n");
    printf("************** Rock Paper Scissors Lizard Spock *************\n");
    printf("**** É uma variação do tradicional Jaken-Pon visto       ****\n");
    printf("**** originalmente na série televisiva The big bang Theory **\n");
    printf("**** nos episódios:'The Lizard-Spock Expansion' e 'The   ****\n");
    printf("**** Euclid Alternative'. As jogadas possíveis são:pedra ****\n");
    printf("**** papel,tesoura,lizard e spock. Neste jogo as regras  ****\n");
    printf("**** são parecidas com o Jaken-Pon, porém com incremento ****\n");
    printf("**** das jogadas: lizard  e spock.                       ****\n");
    printf("*************************************************************\n");
    printf("************************** REGRAS ***************************\n");
    printf("*************************************************************\n");
    printf("**** TESOURA CORTA PAPEL          PAPEL EMBRULHA PEDRA   ****\n");
    printf("**** PEDRA DESTRÓI LIZARD         LIZARD ENVENENA SPOCK  ****\n");
    printf("**** SPOCK AMASSA TESOURA         TESOURA DECAPTA LIZARD ****\n");
    printf("**** LIZARD COME PAPEL            PAPEL DESAPROVA SPOCK  ****\n");
    printf("**** SPOCK VAPORIZA PEDRA         PEDRA AMASSA TESOURA   ****\n");
    printf("*************************************************************\n");
    printf("*************************************************************\n");
    printf("*************************************************************\n");
    /*http://bigbangtheory.wikia.com/wiki/Rock_Paper_Scissors_Lizard_Spock*/
    jogada=1;
        while(jogada!=0){
        printf("Digite 1=PEDRA,2=PAPEL,3=TESOURA,4=LIZARD,5=SPOCK,0=SAIR\n");   
        scanf("%d",&jogada);
            if(jogada!=0){				
            xi=((a*x0)+b)%m;/*Parametro da jogada aleatória*/
            cont=(float)xi/(m-1);/*Parametro da jogada aleatória*/
            /*Regras para jogada aleatória*/        
                if(cont<=0.20){
                comp=1;
                }
                if(cont>0.2 && cont<=0.4){
                comp=2;
                }
                if (cont>0.4 && cont<=0.6){
                comp=3;
                }
                if(cont>0.6 && cont<=0.8){
                comp=4;
                }
                if(cont>0.8){
                comp=5;
                }
                /*Imprime nome do jogador*/
                for(n=0;n<ni;n++){
                    if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                    printf("%c",nome[n]);
                    }
                }
                if(jogada==1){
                printf(" jogou pedra\n");
                }
                if(jogada==2){
                printf(" jogou papel\n");
                }
                if(jogada==3){
                printf(" jogou tesoura\n");
                }
                if(jogada==4){
                printf(" jogou lizard\n");
                }
                if(jogada==5){
                printf(" jogou spock\n");
                }
                if(comp==1){
                printf("O Super computador jogou pedra\n");
                }
                if(comp==2){
                printf("O Super computador jogou papel\n");
                }
                if(comp==3){
                printf("O Super computador jogou tesoura\n");
                }
                if(comp==4){
                printf("O Super computador jogou lizard\n");
                }
                if(comp==5){
                printf("O Super computador jogou spock\n");
                }
                /*Comparadores*/
                if ((comp==1 && jogada==1) || (comp==2 && jogada==2) ||
                (comp==3 && jogada==3) || (comp==4 && jogada==4) ||
                (comp==5 && jogada==5)){
                printf("\nEMPATOU!\n");
                emp++;
                aux2=0;
                }
                if ((comp==1 && jogada==4) || (comp==4 && jogada==1)){
                printf("Pedra destrói lizard!\n\n");
                    if(comp==1){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==1 && jogada==3) || (comp==3 && jogada==1)){
                printf("Pedra destrói tesoura!\n\n");
                    if(comp==1){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==2 && jogada==1) || (comp==1 && jogada==2)){
                printf("Papel cobre pedra!\n\n");
                    if(comp==2){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==2 && jogada==5) || (comp==5 && jogada==2)){
                printf("Papel desaprova Spock!\n\n");
                    if(comp==2){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==3 && jogada==4) || (comp==4 && jogada==3)){
                printf("Tesoura decapta lizard!\n\n");
                    if(comp==3){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==3 && jogada==2) || (comp==2 && jogada==3)){
                printf("Tesoura corta papel!\n\n");
                    if(comp==3){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==4 && jogada==5) || (comp==5 && jogada==4)){
                printf("Lizard envenena Spock!\n\n");
                    if(comp==4){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==4 && jogada==2) || (comp==2 && jogada==4)){
                printf("Lizard come papel\n\n");
                    if(comp==4){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==5 && jogada==3) || (comp==3 && jogada==5)){
                printf("Spock destrói tesoura!\n\n");
                    if(comp==5){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                if ((comp==5 && jogada==1) || (comp==1 && jogada==5)){
                printf("Spock vaporiza pedra!\n\n");
                    if(comp==1){
                    aux2=1;
                    derr++;
                    }
                    else{
                    aux2=2;
                    vit++;
                    }
                }
                /*aux2 serve para imprimir a situação da rodada*/
                if(aux2==1){
                printf("O Super Computador venceu!\n");
                }
                if(aux2==2){
                    for(n=0;n<ni;n++){
                        if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                        printf("%c",nome[n]);
                        }
                    }
                printf(" venceu!\n");
                }
            win=(float)(vit)/(vit+emp+derr)*100;
            draw=(float)(emp)/(vit+emp+derr)*100;
            lose=(float)(derr)/(vit+emp+derr)*100;
            jog++;
            /*Estatistica por turno*/
            printf("**********************\n");
            printf("%.1f %% ",win);
                for(n=0;n<ni;n++){
                    if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                    printf("%c",nome[n]);
                    }
                }
            printf("\n");
            printf("%.1f %% EMPATES\n",draw);
            printf("%.1f %% COMPUTADOR\nJOGADAS:%d\n",lose,jog);
            printf("**********************\n");
            x0=xi;/*Parametro da jogada aleatória*/
            }/*if jogada !=0*/
        }/*while jogada !=0*/
    }/*if modo 555*/
    if (modo==777){
    /*MODO GODLIKE, o modo impossivel. Neste modo não existe lógica para 
    o super computador, ele simplesmente te vence. SEMPRE.*/
    printf("*******************CHEATCODE ACTIVATED***********************\n");
    printf("*************************************************************\n");
    printf("********************** MODO GODLIKE *************************\n");
   printf("*************************************************************\n\n");
    printf("GANHE SE PUDER HAHAHAHAHAHAHAHAHAHAHAH!\n");
    jogada=1;
        while(jogada!=0){
        printf("1=Pedra, 2=Papel, 3=Tesoura\nDigite 0 para acabar o jogo\n");
        scanf("%d",&jogada);
        jogador(jogada);
            if(jogada!=0){
                if(jogada==1){
                comp=2;
                }
                if(jogada==2){
                comp=3;
                }
                if(jogada==3){
                comp=1;
                }
            /*Jogada do computador*/
                if(comp==2){                                          
                printf("O Super computador jogou papel!\n");
                }
                if(comp==3){
                printf("O Super computador jogou tesoura!\n");
                }
                if(comp==1){
                printf("O Super computador jogou pedra!\n");
                }
                printf("O Super Computador venceu\n");
                derr++;	
                win=(float)(vit)/(vit+emp+derr)*100;
                draw=(float)(emp)/(vit+emp+derr)*100;
                lose=(float)(derr)/(vit+emp+derr)*100;
                jog++;
                /*Estatistica por turno*/
                printf("**********************\n");
                printf("%.1f %% ",win);
                    for(n=0;n<ni;n++){
                        if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                        printf("%c",nome[n]);
                        }
                    }
                printf("\n");
                printf("%.1f %% EMPATES\n",draw);
                printf("%.1f %% COMPUTADOR\nJOGADAS:%d\n",lose,jog);
                printf("**********************\n");
        
            }/*if jogada!=0*/
        }/*while jogada!=0*/
    }/*if modo 777*/

/*ESTATISTICAS FINAIS*/
    if(vit!=0 || derr!=0 || emp!=0)
/*Evita mostrar tabela se o jogador voltar do modo sem jogar*/{
    printf("******************  Estatísticas  **********************\n");
    printf("********************************************************\n");
    printf("*** VITÓRIAS ");
        for(n=0;n<ni;n++){
            if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
            printf("%c",nome[n]);
            }
        }
    printf("  %d",vit);  
    printf("                   %.1f %%  *****\n",win);
    printf("*** VITÓRIAS COMPUTADOR:  %d",derr);
    printf("              %.1f %%  *****\n",lose);
    printf("*** EMPATES  %d                           %.1f %%  *****\n",emp,draw);
    printf("*** JOGADAS  %d                    ********************\n",jog);
    printf("*********************************************************\n");
        if (vit>derr){
            for(n=0;n<ni;n++){
                if (nome[n]!=' ' && nome[n]!='.' && nome[n]!='\n'){
                printf("%c",nome[n]);
                }
            }
        printf(" VENCEU O JOGO!\n\n");
        printf("NÃO ACREDITO QUE POSSA EXISTIR UM RESULTADO COMO ESTE!\n");
        printf("NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!NÃO!\n");
        printf("IMPOSSÍVEL!\n");
        printf("Nobre jogador, você provou seu valor e derrotou o ");
        printf("Super computador!\n\n");
            if (modo==1){
            printf("Como recompensa pelo seus nobres atos, você destravou");
            printf(" um novo modo de jogo.\nDigite '555' ");
            printf("ao selecionar o modo de jogo para ativá-lo!\n\n");
            }
            if (modo==2 || modo==555){
            printf("Como recompensa pelo seus nobres atos, você destravou");
            printf(" um novo modo de jogo.\nDigite '777' ");
            printf("ao selecionar o modo de jogo para ativá-lo!\n\n");
            }
        }/*if vit>derr*/
        if (derr>vit){
        printf("O Super Computador VENCEU!\n\n");
        printf("Eu venci, novamente. Meros humanos não são desafios");
        printf(" para meu grande intelecto.\n");
        printf("Da próxima vez, DESISTA ANTES DE COMEÇAR\n");
        printf("HAHAHAHAHAHAHAHAHAHAHAHAHAHAHAHA!\n\n");
        }/*if derr>vit*/
        if(vit==derr){
        printf("EMPATOU!!!\n\n");
        printf("EMPATAMOS!?!?!?, COMO ISSO É POSSIVEL?\n");
        printf("TINHA CERTEZA ABSOLULTA QUE EMPATE ERA UMA LENDA!\n\n");
        }
    }/*if vit emp derr*/
}/*int main*/
return 0;
}
























