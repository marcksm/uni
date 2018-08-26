#include<stdio.h>
#define MAX 10000
#define DIC 350000
int mdcc(int k, int a){  
/*Algoritmo de Euclides.
fonte: aula MAC105 fundamentos de matematica para computação*/
    int r;  
while (a!=0){  
r=a;  
a=k%a;  
k=r;  
}  
return k;  
}

void texttocode(int a,int ciphercode[MAX],char ciphertext[MAX] ){
    int i,n;
for(i=0;i<a;i++){
/*Esse conjunto de operações realiza a interpretação dos caracteres
em numeros de 0 a 27, transformando o ciphertext em ciphercode.
A argumentação do n é baseada na tabela ASCII, que inicia a numeração dos
caracteres maiusculos após o '@'. http://www.ascii-code.com/*/
    for(n=1;n<=27;n++){
        if (ciphertext[i]=='_'){
        ciphercode[i]=0;
        }
        if (ciphertext[i]=='.'){
        ciphercode[i]=27;
        }
        if (ciphertext[i]=='@'+n){
        ciphercode[i]=n;
        }
    }
}
}
void candidato_decriptografia_em_codigo(int a,int k, int ciphercode[MAX], 
int plaincode[MAX]){
    int i=0,etapa1=0,etapa2=0,etapa3=0;
    int x,sair=0;
for(i=0;i<a;i++){
/*Inicio da função de descriptografia, é realizada em etapas,
etapa1, etapa2,etapa3.
ciphercode[i]=(plaincode[(k*i)mod a]-i) mod 28
etapa1 representa o calculo do [(k*i)mod a]
etapa2 representa o calculo do valor (plaincode[(k*i)mod a]-i)
etapa3 representa o valor de ciphercode[i]
O objetivo desta função é encontrar o valor de plaincode e a
posição onde esse valor é armazenado. Para isso a expressão
é modificada para encontrar esses valores, é realizado testando
varios valores até que a expressão seja verdadeira.*/
etapa3=ciphercode[i];
etapa1=((k*i)%a);
    while (etapa1<0){
    /*Parametro que evita a inserção de numeros negativos,
    caso tenha é somado o valor de etapa1 até que fique
    positivo */
    etapa1=(etapa1+a);
    }
    for(x=0;x<=300 && sair==0;x++){
    /*Este operador realiza testes na variavel x(representa o
    [(k*i)mod a] ou etapa1) para verificar quais são os possiveis
    valores desse parametro, se o resultado das operações com 
    esse parametro for igual ao ciphercode[i], ele é valido e
    seus valores confirmados.Logo concluimos o valor de plaincode
    e o valor de etapa1 para que o ciphecode[i] seja verdadeiro.*/
    etapa2=(x-i);
        while(etapa2%28<0){
        /*Parametro que evita a inserção de numeros negativos,
        caso tenha é somado 28 até que fique positivo */
        etapa2=etapa2+28;
        }
        if (etapa3==(etapa2%28)){
        /*Condição que confirma o valor de x utilizado e 
        armazena o valor no vetor plaincode na posição etapa1
        como na expressão:
        ciphercode[i]=(plaincode[(k*i)mod a]-i) mod 28
        */
        plaincode[etapa1]=x;
        sair=1;
        }
    }
sair=0;
}
}
void candidato_decriptografia_em_letras(int a, int plaincode[MAX],
char decryptchar[MAX]){
    int i,n;    
/*Nesta função ocorre a transformação do vetor com a mensagem em código, para
mensagem em letras, para que então ocorra uma busca no dicionário*/
for(i=0;i<a;i++){
/*Esse conjunto de operações realiza a interpretação dos caracteres
em numeros de 0 a 27, transformando o ciphertext em ciphercode.
A argumentação do n é baseada na tabela ASCII, que inicia a numeração dos
caracteres maiusculos após o '@'. http://www.ascii-code.com/*/
    for(n=1;n<=27;n++){
        if (plaincode[i]==n){
        decryptchar[i]=('@'+n);
        }
        if (plaincode[i]==27){
        decryptchar[i]='.';
        }
        if(plaincode[i]==0){
        decryptchar[i]='_';
        }
    }
  }
}
int dicionario_no_vetor(char v[DIC]){
/*Função que armazena os caracteres do dicionario no vetor v[DIC]*/
    FILE * entrada;
    int i, leitura=0;
    char caractere;
    entrada = fopen("dicionario.txt", "r");
    for(i=0;i<300000;i++){
    leitura = fscanf(entrada, "%c", &caractere);
        if(caractere!='-'){
         /*Hífen é ignorado durante a leitura*/
         v[i]=caractere;
         }
        else{
        i--;
        }
    }
return leitura;
}
int corretor_frases(int a, char decryptchar[MAX]){
/*Essa função corrige entradas com sequencias de ___ ou de ..
reescrevendo a mensagem apartir do ponto em que ocorre a 
primeira sequencia. Retornando o tamanho alterado da mensagem. 
Se a frase não conter nenhuma sequencia de __ ou de .. esta
função é ignorada.*/
    int h=0,i=0;
for(i=0;i<=a;i++){
    while((decryptchar[i]=='.' && decryptchar[i+1]=='.')||
    (decryptchar[i]=='_' && decryptchar[i+1]=='_')||
    (decryptchar[i]=='_' && decryptchar[i-1]=='_')){
        for(h=i;h<=a;h++){
        decryptchar[h]=decryptchar[h+1];
        }
    a--;
    }
    
}
return a;
}
int segmentacao_frases(int a, int segmento[MAX],int tamanho[MAX],
char decryptchar[MAX]){
/*Função que divide a frase em várias palavras, armazenando o tamanho de cada
na váriavel tamanho[l] e retornando o numero de palavras na frase.
As palavras são segmentadas baseadas nos . e _ que aparecem na mensagem*/
    int i,l=0,palavra=0;
for(i=0;i<=a;i++){
/*Reset dos vetores*/
segmento[i]=0;
tamanho[i]=0;
}
for(i=0;i<=a;i++){
    if ((decryptchar[tamanho[l]-1]=='.')||
    (decryptchar[i]=='_' && decryptchar[i+1]!='_')|| 
    (decryptchar[i]=='.' && decryptchar[i+1]!='_') || 
    (decryptchar[i]==decryptchar[i+1]&&
    decryptchar[i]==decryptchar[i+2])){
    palavra++;
    segmento[l]=i;
    tamanho[l]=(segmento[l]-segmento[l-1]);
    l++;
    }
}
return palavra;
}
int busca_no_dicionario(int palavra, char decryptchar[MAX],int tamanho[MAX],
char frase[MAX],char v[DIC]){
/*Função que busca no dicionario as palavras segmentadas.*/
    int l=0,g=0,p=0,seq=0,j=0,e=0,i=0,f=0,b=0,d=0;
/*A variavél j, serve para evitar problemas com o a posição 0 do vetor, pois
após a primeira palavra, j recebe 1, para que a comparação das palavras fique
correta.*/
for(l=0;l<=palavra;l++){
/*Buscará no dicionario a quantidade de palavras que foram computadas.*/
    for(f=0;f<350000;f++){
    /*Esse for realiza o teste dos caracteres no dicionario*/
      if(decryptchar[g]=='_'||decryptchar[g]=='.'){
      /*Essa condição estabiliza a posição da palavra.
       colocando o g no inicio de uma palavra caso esteja em _ ou .*/
      g++;
      }
    p=0;
      if((decryptchar[g+tamanho[l]-j-1]=='.'
      && decryptchar[g+tamanho[l]-j]=='_')
      ||(decryptchar[g+tamanho[l]]=='.'
      && palavra==1)){
      /*Condição para introdução do ponto na frase.
      p=1 modifica a forma de analisar o tamanho das palavras,
      ignorando o tamanho com '.' no final. 
      Depois o '.' é acrescentado manualmente no vetor da frase.*/
      p=1;
      }
      if(v[f]==decryptchar[g] && (v[f+tamanho[l]-j-p]=='\n')){
        /*Condição para encontrar a palavra no dicionario.
        caso a letra analisada no vetor dicionario seja igual
        a letra analisada na variavel decryptchar[g](onde g é
        a posição acumulada das palavras g=g+tamamho[l]) e 
        somando o tamanho da potencial palavra em decryptchar
        no vetor dicionario, se este for igual a '\n', significa
        que esta palavra do dicionario tem o mesmo tamanho da
        palavra em decryptchar e inicia com a mesma letra.
        Então é rodado um novo teste para verificar se as
        letras na sua composição são iguais.
        Ex: Suponha palavra OLA, decryptchar[g], com g=0,
        decryptchar[0]='O', e tamanho[l]=3.
        No dicionario será procurada uma palavra que inicie com 'O'
        tenha tamanho 3 e sua 4 letra sera '\n'(quebra de linha). */
            for(i=g,d=0;i<(tamanho[l]+g)-j-p;i++,d++){
                /*Ao encontrar uma palavra elegivel, será realizada
                testes de seq, para verificar se cada letra dentro da
                palavra de fato contém na potencial palavra do dicionario.
                Caso tenha, será acrescido a variavél seq.*/
                    if(v[f+d]==decryptchar[i]){
                    seq++;
                    }
            }
            if(seq==(tamanho[l])-j-p){
            /*Se seq for igual ao tamanho[l] da palavra em questão
            então encontramos uma palavra no dicionario!
            Basta acrescenta-la em vetor! */
               for(e=0,i=g;i<(tamanho[l]-j+g-p);i++,e++){
               frase[b]=v[f+e];
               b++;
               }
            /*Como a função ignora os _ e . durante a  segmentação das
            palavras, é adicionado um . ou _ a cada palavra analisada.*/
               if(p==1){
                /*Condição para acrescentar . na frase*/
               frase[b]='.';
               b++;
               }
           frase[b]='_';
           b++;
           p=0;
           f=350001/*Para sair da for, após encontrar a palavra*/;    
           }
      /*Reset de variaveis*/
      p=0;
      seq=0;
      } /*if v[f]...*/
    }/*for f*/
    g=g+tamanho[l];/*É a variavel acumulada do tamanho da frase. 
    A cada palavra lida, é acrescida o tamanho, para ter um parametro
    de localização no vetor decryptchar*/
    j=1;
}/*for palavra*/
return b;
}
  
int printar_decryptchar_verdadeiro(FILE * saida,int a,int b,int k,int out,
char decryptchar[MAX]){    
    /*Esta função imprime a frase na tela e no DECRYPT.OUT*/
    if(b>=a-1){
/*Esta condição serve para verificar se a frase armazenada que é candidata
a frase verdadeira, tem o tamanho maior ou igual ao tamanho
da mensagem original menos 1 
Se tiver, significa que todas as palavras foram encontradas no dicionario
e o vetor decryptchar tem a frase verdadeira, então imprimo decryptchar[b]
com b=0 até b<a.
Se esta condição não for correspondida, a frase não continha frases elegiveis
no dicionario, e portanto não será impressa.
A variavel out serve para imprimir somente uma vez no DECRYPT.OUT*/
        for(b=0;b<a;b++){
        printf("%c",decryptchar[b]);
            if(out==0){
            fprintf(saida,"%c",decryptchar[b]);
            }
        }
    printf("K=%d\n",k);
    out=1;
    }/*if b>=a-1*/
return out;
}
int main(){
    FILE * entrada; /* representa o arquivo de entrada */
    FILE * saida;     /* representa o arquivo de entrada */
    int leitura,mdcagora=0,b=0,out=0;
    char caractere, frase[MAX];
    int ciphercode[MAX],plaincode[MAX],segmento[MAX],tamanho[MAX];
    char ciphertext[MAX],decryptchar[MAX],v[DIC];
    int aux=1,k=0,i=0,a=0,palavra=0;
    entrada = fopen("DECRYPT.IN", "r");
    saida = fopen("DECRYPT.OUT", "w");
    

    


/*Inicio de descriptografia*/
/*Declaração parametro de entrada que lê a frase criptografada em DECRYPT.IN*/
entrada = fopen("DECRYPT.IN", "r");
/*Instrução que le o arquivo DECRYPT.IN e armazena em um vetor.
O vetor ciphertext receberá os valores de DECRYPT.IN*/
while (leitura!= EOF || caractere!='\n'){
    leitura = fscanf(entrada, "%c", &caractere);
    if(caractere!='\n' || caractere!=' '){
    /*CONDIÇÃO PARA EVITAR A CONTAGEM DE ESPAÇOS OU \n
    Notei que durante os teste com os DECRYPT.IN que você enviou, se eu 
    testasse diretamente não funcionava, mas se eu abrisse o arquivo e 
    salvasse(simplesmente CRTL+S),o programa rodava e DECRIPTOGRAFAVA. 
    Suspeito que seja algo com espaços ou \n no final do arquivo, mas mesmo
    colocando essa condição ainda é necessário criar o meu próprio DECRYPT.IN
    para que o programa rode.*/
    ciphertext[i]=caractere;
    i++;
    }/*Variavel i é acrescida a cada caractere adicionado.*/
}
a=i-2;
/*Variavél a é o tamanho da mensagem.Recebe o valor i-2, para 
ajuste correto do tamanho da mensagem do vetor na variavél. Esse ajuste é
em função de existencia da posição 0 no vetor.*/

texttocode(a,ciphercode,ciphertext);
/*Função que transforma ciphertext em ciphercode*/
for(k=0;k<=300;k++){
mdcagora=mdcc(k,a);
/*Funcao que calcula o mdc de acordo com o k, e o tamanho da mensagem*/
    if (mdcagora==1){
        /*Condição de inicio do programa, se o mdc atual for 1, é iniciada a
        tentativa de descriptografia*/
        candidato_decriptografia_em_codigo(a,k,ciphercode,plaincode);
        /*Função que busca através da formula:
        ciphercode[i]=(plaincode[(k*i)mod a]-i) mod 28
        um candidato a frase descriptada*/
        candidato_decriptografia_em_letras(a,plaincode,decryptchar);
        /*Função que transforma o candidato a descriptografia de código
        para alfabeto _ e .*/
        dicionario_no_vetor(v);
        /*Função que armazena o dicionario no vetor v*/        
        /*Reset de variáveis*/
        b=0;
        palavra=0;
        /*Reset de variáveis*/
        aux=a;
        /*aux armazena o tamanho original da mensagem para que esta informação
        não seja perdida após iniciar o corretor de frases.Para que assim em 
        um novo teste(com outro k) o tamanho da frase tenha o mesmo parametro 
        original*/
        a=corretor_frases(a,decryptchar);
        /*Função que corrige entrada, caso a frase contenha uma sequencia 
        de ____ ou sequencia de ... Reduzindo seu tamanho e deixando apenas
         1 _ ou 1 . entre palavras.
        Exemplo: OLA_____AGORA....MUITO..ABACAXI__ACREDITAR. 
        será transformada para OLA_AGORA.MUITO.ABACAXI_ACREDITAR. Essa 
        estrategia facilita a busca no dicionario e retorna uma frase ideal*/
        
        palavra=segmentacao_frases(a,segmento,tamanho,decryptchar);
        /*Função que segmenta a frase, separando em palavras e armazenando seu
        tamanho*/
        b=busca_no_dicionario(palavra,decryptchar,tamanho,frase,v);
        /*Função que busca no dicionario as palavras segmentadas e incrementa
        na frase final.*/
        out=printar_decryptchar_verdadeiro(saida,a,b,k,out,decryptchar);
        /*Função que imprime e grava no DECRYPT.OUT a frase decriptografada
        verdadeira.*/
        a=aux;
        /*A variavel a volta a receber seu valor original. Só é utilizado
        em casos onde a função corretor_frases(a,decryptchar); é 
        executada.*/
    }/*mdcagora==1*/
}/*k*/
fclose(entrada);
fclose(saida);
return 0;
}/*main*/
